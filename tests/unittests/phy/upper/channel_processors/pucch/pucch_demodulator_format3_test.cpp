/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "pucch_demodulator_format3_test_data.h"
#include "srsran/adt/to_array.h"
#include "srsran/phy/support/support_factories.h"
#include "srsran/phy/upper/channel_processors/channel_processor_factories.h"
#include "srsran/phy/upper/channel_processors/pucch/factories.h"
#include "srsran/phy/upper/channel_processors/pucch/pucch_demodulator.h"
#include "srsran/phy/upper/equalization/equalization_factories.h"
#include "srsran/phy/upper/pucch_formats3_4_helpers.h"
#include "srsran/ran/pucch/pucch_constants.h"
#include "srsran/srsvec/conversion.h"
#include "fmt/ostream.h"
#include <gtest/gtest.h>

using namespace srsran;

using PucchDemodulatorParams = test_case_t;

namespace srsran {

// Maximum allowed error.
constexpr log_likelihood_ratio::value_type LLR_MAX_ERROR = 2;

std::ostream& operator<<(std::ostream& os, test_case_t test_case)
{
  fmt::print(os,
             "ports=[{}] first_prb={} second_hop_prb={} nof_prb={} start_symbol_index={} nof_symbols={} rnti={} "
             "n_id={} additionalDMRS={} pi2_bpsk={}",
             span<const uint8_t>(test_case.context.config.rx_ports),
             test_case.context.config.first_prb,
             test_case.context.config.second_hop_prb,
             test_case.context.config.nof_prb,
             test_case.context.config.start_symbol_index,
             test_case.context.config.nof_symbols,
             test_case.context.config.rnti,
             test_case.context.config.n_id,
             test_case.context.config.additional_dmrs,
             test_case.context.config.pi2_bpsk);
  return os;
}

std::ostream& operator<<(std::ostream& os, span<const log_likelihood_ratio> data)
{
  fmt::print(os, "[{}]", data);
  return os;
}

static bool operator==(span<const log_likelihood_ratio> lhs, span<const log_likelihood_ratio> rhs)
{
  return std::equal(
      lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](log_likelihood_ratio lhs_, log_likelihood_ratio rhs_) {
        return log_likelihood_ratio::abs(lhs_ - rhs_) <= LLR_MAX_ERROR;
      });
}

} // namespace srsran

class PucchDemodulatorFixture : public ::testing::TestWithParam<PucchDemodulatorParams>
{
protected:
  pucch_demodulator::format3_configuration config;
  std::vector<log_likelihood_ratio>        uci_expected;
  channel_estimate                         channel_est;
  resource_grid_reader_spy                 rg_spy;

  // PUCCH Demodulator.
  static std::unique_ptr<pucch_demodulator> demodulator;

  PucchDemodulatorFixture() : rg_spy(16, 14, MAX_NOF_PRBS) {}

  static void SetUpTestSuite()
  {
    if (!demodulator) {
      // Create factories required by the PUCCH demodulator factory.
      std::shared_ptr<channel_equalizer_factory> equalizer_factory = create_channel_equalizer_generic_factory();
      ASSERT_NE(equalizer_factory, nullptr) << "Cannot create equalizer factory";

      std::shared_ptr<demodulation_mapper_factory> demod_factory = create_demodulation_mapper_factory();
      ASSERT_NE(demod_factory, nullptr) << "Cannot create channel modulation factory";

      std::shared_ptr<pseudo_random_generator_factory> prg_factory = create_pseudo_random_generator_sw_factory();
      ASSERT_NE(prg_factory, nullptr) << "Cannot create pseudo-random generator factory";

      std::shared_ptr<dft_processor_factory> dft_factory = create_dft_processor_factory_fftw_slow();
      ASSERT_NE(dft_factory, nullptr) << "Cannot create DFT processor factory";

      std::shared_ptr<transform_precoder_factory> precoding_factory =
          create_dft_transform_precoder_factory(dft_factory, pucch_constants::FORMAT3_MAX_NPRB + 1);
      ASSERT_NE(precoding_factory, nullptr) << "Cannot create transform precoder factory";

      // Create PUCCH demodulator factory.
      std::shared_ptr<pucch_demodulator_factory> pucch_demod_factory =
          create_pucch_demodulator_factory_sw(equalizer_factory, demod_factory, prg_factory, precoding_factory);
      ASSERT_NE(pucch_demod_factory, nullptr) << "Cannot create PUCCH demodulator factory.";

      // Create PUCCH demodulator.
      demodulator = pucch_demod_factory->create();
      ASSERT_NE(demodulator, nullptr) << "Cannot create PUCCH demodulator.";
    }
  }

  static void TearDownTestSuite() { demodulator.reset(); }

  void SetUp() override
  {
    const test_case_t& test_case = GetParam();

    // Assert PUCCH demodulator.
    ASSERT_NE(demodulator, nullptr) << "Cannot create PUCCH demodulator.";

    // Prepare PUCCH demodulator configuration.
    config = test_case.context.config;

    // Prepare expected UCI codeword.
    uci_expected = test_case.uci_codeword.read();

    // Determine resource grid dimensions.
    unsigned nof_prb      = test_case.context.grid_nof_prb;
    unsigned nof_symbols  = test_case.context.grid_nof_symbols;
    unsigned nof_rx_ports = config.rx_ports.size();

    // Prepare the resource grid.
    symbol_slot_mask dmrs_symb_mask = get_pucch_formats3_4_dmrs_symbol_mask(
        config.nof_symbols, config.second_hop_prb.has_value(), config.additional_dmrs);
    unsigned nof_test_symbols = test_case.context.config.rx_ports.size() *
                                (config.nof_symbols - dmrs_symb_mask.count()) * test_case.context.config.nof_prb * NRE;

    std::vector<resource_grid_reader_spy::expected_entry_t> grid_entries = test_case.symbols.read();
    ASSERT_EQ(grid_entries.size(), nof_test_symbols)
        << "The number of grid entries and the number of PUCCH REs do not match";

    rg_spy.write(grid_entries);

    // Prepare channel estimates.
    channel_estimate::channel_estimate_dimensions ce_dims;
    ce_dims.nof_prb       = nof_prb;
    ce_dims.nof_symbols   = nof_symbols;
    ce_dims.nof_rx_ports  = nof_rx_ports;
    ce_dims.nof_tx_layers = 1;

    channel_est.resize(ce_dims);

    // Set estimated channel.
    std::vector<cf_t> estimates = test_case.estimates.read();
    srsvec::convert(channel_est.get_path_ch_estimate(0, 0), estimates);

    // Set noise variance.
    channel_est.set_noise_variance(test_case.context.noise_var, 0);
  }
};

std::unique_ptr<pucch_demodulator> PucchDemodulatorFixture::demodulator = nullptr;

TEST_P(PucchDemodulatorFixture, PucchDemodulatorVectorTest)
{
  std::vector<log_likelihood_ratio> uci_data(uci_expected.size());

  // Perform demodulation.
  demodulator->demodulate(uci_data, rg_spy, channel_est, config);

  // Assert UCI codeword matches.
  ASSERT_EQ(span<const log_likelihood_ratio>(uci_expected), span<const log_likelihood_ratio>(uci_data));
}

// Creates test suite that combines all possible parameters.
INSTANTIATE_TEST_SUITE_P(PucchDemodulatorVectorTest,
                         PucchDemodulatorFixture,
                         ::testing::ValuesIn(pucch_demodulator_format3_test_data));
