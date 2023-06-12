/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/phy/support/re_buffer.h"
#include "srsran/phy/upper/channel_processors/pdsch_modulator.h"
#include "srsran/phy/upper/sequence_generators/pseudo_random_generator.h"
#include "srsran/ran/cyclic_prefix.h"

namespace srsran {

/// Describes a generic implementation of a PDSCH modulator, defined by TS 38.211 section 7.3.1
class pdsch_modulator_impl : public pdsch_modulator
{
private:
  std::unique_ptr<modulation_mapper>       modulator;
  std::unique_ptr<pseudo_random_generator> scrambler;

  /// \brief Scrambles a codeword. Implements TS 38.211 section 7.3.1.1 Scrambling.
  ///
  /// \param[in] b Inputs bits to scramble.
  /// \param[in] q Codeword index {0,1}.
  /// \param[in] config Provides the scrambler configuration.
  /// \return Output bits after scrambling.
  const bit_buffer& scramble(const bit_buffer& b, unsigned q, const config_t& config);

  /// \brief Modulates a codeword. Implements TS 38.211 section 7.3.1.2 Modulation.
  ///
  /// \param[out] d_pdsch Output symbols.
  /// \param[in] b_hat Inputs bits to perform the modulation mapping.
  /// \param[in] modulation Indicates the modulation scheme (QPSK, 16QAM, ...).
  /// \param[in] scaling Indicates the signal scaling if the value is valid (not 0, NAN nor INF).
  void modulate(span<cf_t> d_pdsch, const bit_buffer& b_hat, modulation_scheme modulation, float scaling);

  /// \brief Maps resource elements into the resource grid.
  ///
  /// Implements TS 38.211 sections 7.3.1.4 Antenna port mapping, 7.3.1.5 Layer mapping, 7.3.1.5 Mapping to virtual
  /// resource blocks and 7.3.1.6 Mapping from virtual to physical resource blocks.
  ///
  /// \param[out] mapper Resource grid mapping interface.
  /// \param[in] data_re PDSCH resource elements that have been already mapped to layers.
  /// \param[in] config PDSCH modulator configuration parameters.
  /// \note The number of layers and codewords is deduced from the parameters.
  static void map(resource_grid_mapper& mapper, const re_buffer_reader& data_re, const config_t& config);

  /// Temporary buffer for scrambled sequence.
  static_bit_buffer<MAX_CODEWORD_SIZE> temp_b_hat;
  /// Temporary buffer for the PDSCH modulated symbols.
  std::array<cf_t, MAX_CODEWORD_SIZE> temp_pdsch_symbols;
  /// Temporary buffer for the PDSCH layer-mapped RE.
  static_re_buffer<precoding_constants::MAX_NOF_LAYERS, MAX_RB * NRE * MAX_NSYMB_PER_SLOT> temp_re;

public:
  /// \brief Generic PDSCH modulator instance constructor.
  pdsch_modulator_impl(std::unique_ptr<modulation_mapper>       modulator_,
                       std::unique_ptr<pseudo_random_generator> scrambler_) :
    modulator(std::move(modulator_)), scrambler(std::move(scrambler_))
  {
    srsran_assert(modulator, "Invalid modulator");
    srsran_assert(scrambler, "Invalid scrambler");
  }

  // See interface for the documentation.
  void
  modulate(resource_grid_mapper& mapper, srsran::span<const bit_buffer> codewords, const config_t& config) override;
};

} // namespace srsran
