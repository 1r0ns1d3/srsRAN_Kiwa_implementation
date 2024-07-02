/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
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

#pragma once

// This file was generated using the following MATLAB class on 27-06-2024 (seed 0):
//   + "srsPUSCHDemodulatorUnittest.m"

#include "../../../support/resource_grid_test_doubles.h"
#include "srsran/phy/upper/channel_processors/pusch/pusch_demodulator.h"
#include "srsran/support/file_tensor.h"

namespace srsran {

enum class ch_dims : unsigned { subcarrier = 0, symbol = 1, rx_port = 2, tx_layer = 3, nof_dims = 4 };

struct context_t {
  float                            noise_var;
  float                            sinr_dB;
  pusch_demodulator::configuration config;
};

struct test_case_t {
  context_t                                                            context;
  file_vector<resource_grid_reader_spy::expected_entry_t>              symbols;
  file_tensor<static_cast<unsigned>(ch_dims::nof_dims), cf_t, ch_dims> estimates;
  file_vector<uint8_t>                                                 scrambling_seq;
  file_vector<log_likelihood_ratio>                                    codeword;
};

static const std::vector<test_case_t> pusch_demodulator_test_data = {
    // clang-format off
  {{0.0016124, 30.3963, {41442, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, modulation_scheme::PI_2_BPSK, 2, 7, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 821, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols0.dat"}, {"test_data/pusch_demodulator_test_input_estimates0.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq0.dat"}, {"test_data/pusch_demodulator_test_output0.dat"}},
  {{0.0014186, 28.6761, {43699, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 1, 13, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, dmrs_type::TYPE1, 1, 995, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols2.dat"}, {"test_data/pusch_demodulator_test_input_estimates2.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq2.dat"}, {"test_data/pusch_demodulator_test_output2.dat"}},
  {{0.00073408, 29.564, {59376, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 1, 8, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 510, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols4.dat"}, {"test_data/pusch_demodulator_test_input_estimates4.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq4.dat"}, {"test_data/pusch_demodulator_test_output4.dat"}},
  {{0.018395, 18.4471, {14385, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 1, 12, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 684, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols6.dat"}, {"test_data/pusch_demodulator_test_input_estimates6.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq6.dat"}, {"test_data/pusch_demodulator_test_output6.dat"}},
  {{0.0022435, 25.5939, {5510, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 0, 8, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 238, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols8.dat"}, {"test_data/pusch_demodulator_test_input_estimates8.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq8.dat"}, {"test_data/pusch_demodulator_test_output8.dat"}},
  {{0.10174, 11.8499, {11247, {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 1, 9, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 24, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols10.dat"}, {"test_data/pusch_demodulator_test_input_estimates10.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq10.dat"}, {"test_data/pusch_demodulator_test_output10.dat"}},
  {{0.0014186, 29.2471, {13308, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 1, 8, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 441, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols12.dat"}, {"test_data/pusch_demodulator_test_input_estimates12.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq12.dat"}, {"test_data/pusch_demodulator_test_output12.dat"}},
  {{0.029224, 13.5496, {60495, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, modulation_scheme::QPSK, 1, 8, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 638, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols14.dat"}, {"test_data/pusch_demodulator_test_input_estimates14.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq14.dat"}, {"test_data/pusch_demodulator_test_output14.dat"}},
  {{0.00073234, 32.0545, {8543, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 0, 8, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 431, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols16.dat"}, {"test_data/pusch_demodulator_test_input_estimates16.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq16.dat"}, {"test_data/pusch_demodulator_test_output16.dat"}},
  {{0.035557, 14.1995, {36974, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, modulation_scheme::QPSK, 0, 11, {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 75, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols18.dat"}, {"test_data/pusch_demodulator_test_input_estimates18.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq18.dat"}, {"test_data/pusch_demodulator_test_output18.dat"}},
  {{0.064192, 14.2557, {27364, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 1, 13, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, dmrs_type::TYPE1, 1, 638, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols20.dat"}, {"test_data/pusch_demodulator_test_input_estimates20.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq20.dat"}, {"test_data/pusch_demodulator_test_output20.dat"}},
  {{0.022483, 16.6985, {43398, {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 1, 12, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, dmrs_type::TYPE1, 2, 86, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols22.dat"}, {"test_data/pusch_demodulator_test_input_estimates22.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq22.dat"}, {"test_data/pusch_demodulator_test_output22.dat"}},
  {{0.011634, 13.654, {5149, {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 0, 14, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 592, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols24.dat"}, {"test_data/pusch_demodulator_test_input_estimates24.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq24.dat"}, {"test_data/pusch_demodulator_test_output24.dat"}},
  {{0.00058172, 33.3567, {7243, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 1, 13, {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, dmrs_type::TYPE1, 2, 58, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols26.dat"}, {"test_data/pusch_demodulator_test_input_estimates26.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq26.dat"}, {"test_data/pusch_demodulator_test_output26.dat"}},
  {{0.0056354, 21.8862, {16991, {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 1, 13, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 726, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols28.dat"}, {"test_data/pusch_demodulator_test_input_estimates28.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq28.dat"}, {"test_data/pusch_demodulator_test_output28.dat"}},
  {{0.0064192, 23.9812, {56623, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, modulation_scheme::QAM64, 0, 7, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 642, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols30.dat"}, {"test_data/pusch_demodulator_test_input_estimates30.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq30.dat"}, {"test_data/pusch_demodulator_test_output30.dat"}},
  {{0.0022483, 27.3943, {2220, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 2, 8, {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 64, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols32.dat"}, {"test_data/pusch_demodulator_test_input_estimates32.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq32.dat"}, {"test_data/pusch_demodulator_test_output32.dat"}},
  {{0.036791, 10.9553, {14331, {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 2, 10, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 261, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols34.dat"}, {"test_data/pusch_demodulator_test_input_estimates34.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq34.dat"}, {"test_data/pusch_demodulator_test_output34.dat"}},
  {{0.0011607, 29.9179, {46813, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, modulation_scheme::QAM64, 1, 11, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 556, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols36.dat"}, {"test_data/pusch_demodulator_test_input_estimates36.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq36.dat"}, {"test_data/pusch_demodulator_test_output36.dat"}},
  {{0.011244, 19.0355, {4963, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 0, 12, {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 493, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols38.dat"}, {"test_data/pusch_demodulator_test_input_estimates38.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq38.dat"}, {"test_data/pusch_demodulator_test_output38.dat"}},
  {{0.080813, 12.6709, {61941, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 1, 7, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 425, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols40.dat"}, {"test_data/pusch_demodulator_test_input_estimates40.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq40.dat"}, {"test_data/pusch_demodulator_test_output40.dat"}},
  {{0.011268, 20.1044, {5690, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 2, 9, {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 689, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols42.dat"}, {"test_data/pusch_demodulator_test_input_estimates42.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq42.dat"}, {"test_data/pusch_demodulator_test_output42.dat"}},
  {{0.0046318, 20.4928, {7084, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 1, 10, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 727, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols44.dat"}, {"test_data/pusch_demodulator_test_input_estimates44.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq44.dat"}, {"test_data/pusch_demodulator_test_output44.dat"}},
  {{0.0036704, 25.3347, {11215, {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 1, 10, {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE1, 1, 446, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols46.dat"}, {"test_data/pusch_demodulator_test_input_estimates46.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq46.dat"}, {"test_data/pusch_demodulator_test_output46.dat"}},
  {{0.0044763, 23.2376, {25869, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 1, 8, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE1, 2, 70, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols48.dat"}, {"test_data/pusch_demodulator_test_input_estimates48.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq48.dat"}, {"test_data/pusch_demodulator_test_output48.dat"}},
  {{0.025555, 18.0999, {11969, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, modulation_scheme::PI_2_BPSK, 2, 11, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 3, 604, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols50.dat"}, {"test_data/pusch_demodulator_test_input_estimates50.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq50.dat"}, {"test_data/pusch_demodulator_test_output50.dat"}},
  {{0.044859, 14.4257, {22934, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 0, 12, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 3, 830, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols52.dat"}, {"test_data/pusch_demodulator_test_input_estimates52.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq52.dat"}, {"test_data/pusch_demodulator_test_output52.dat"}},
  {{0.023214, 15.0447, {50487, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 1, 7, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 2, 824, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols54.dat"}, {"test_data/pusch_demodulator_test_input_estimates54.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq54.dat"}, {"test_data/pusch_demodulator_test_output54.dat"}},
  {{0.0023159, 27.2753, {22017, {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 1, 8, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 2, 239, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols56.dat"}, {"test_data/pusch_demodulator_test_input_estimates56.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq56.dat"}, {"test_data/pusch_demodulator_test_output56.dat"}},
  {{0.028244, 15.2944, {48073, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, modulation_scheme::PI_2_BPSK, 1, 9, {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE2, 1, 788, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols58.dat"}, {"test_data/pusch_demodulator_test_input_estimates58.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq58.dat"}, {"test_data/pusch_demodulator_test_output58.dat"}},
  {{0.025555, 17.8496, {14840, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 1, 12, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 1, 960, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols60.dat"}, {"test_data/pusch_demodulator_test_input_estimates60.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq60.dat"}, {"test_data/pusch_demodulator_test_output60.dat"}},
  {{0.0056474, 22.7951, {20601, {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 1, 13, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 2, 146, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols62.dat"}, {"test_data/pusch_demodulator_test_input_estimates62.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq62.dat"}, {"test_data/pusch_demodulator_test_output62.dat"}},
  {{0.014647, 14.337, {25000, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 2, 10, {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE2, 3, 499, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols64.dat"}, {"test_data/pusch_demodulator_test_input_estimates64.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq64.dat"}, {"test_data/pusch_demodulator_test_output64.dat"}},
  {{0.0073234, 22.1002, {35076, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 2, 10, {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE2, 3, 249, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols66.dat"}, {"test_data/pusch_demodulator_test_input_estimates66.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq66.dat"}, {"test_data/pusch_demodulator_test_output66.dat"}},
  {{0.014155, 17.6081, {4117, {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QPSK, 0, 14, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 1, 248, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols68.dat"}, {"test_data/pusch_demodulator_test_input_estimates68.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq68.dat"}, {"test_data/pusch_demodulator_test_output68.dat"}},
  {{0.016124, 20.2665, {17118, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 2, 7, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 2, 457, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols70.dat"}, {"test_data/pusch_demodulator_test_input_estimates70.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq70.dat"}, {"test_data/pusch_demodulator_test_output70.dat"}},
  {{0.017859, 18.005, {60097, {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 0, 9, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 3, 477, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols72.dat"}, {"test_data/pusch_demodulator_test_input_estimates72.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq72.dat"}, {"test_data/pusch_demodulator_test_output72.dat"}},
  {{0.0029224, 23.3405, {14064, {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 0, 10, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 2, 514, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols74.dat"}, {"test_data/pusch_demodulator_test_input_estimates74.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq74.dat"}, {"test_data/pusch_demodulator_test_output74.dat"}},
  {{0.0058172, 22.7771, {28692, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, modulation_scheme::QAM16, 0, 8, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 3, 207, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols76.dat"}, {"test_data/pusch_demodulator_test_input_estimates76.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq76.dat"}, {"test_data/pusch_demodulator_test_output76.dat"}},
  {{0.0011244, 28.9833, {24074, {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM16, 1, 13, {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 1, 538, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols78.dat"}, {"test_data/pusch_demodulator_test_input_estimates78.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq78.dat"}, {"test_data/pusch_demodulator_test_output78.dat"}},
  {{0.0020299, 29.1925, {15934, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 1, 10, {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE2, 1, 986, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols80.dat"}, {"test_data/pusch_demodulator_test_input_estimates80.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq80.dat"}, {"test_data/pusch_demodulator_test_output80.dat"}},
  {{0.00056474, 33.0377, {46564, {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 1, 12, {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 1, 564, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols82.dat"}, {"test_data/pusch_demodulator_test_input_estimates82.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq82.dat"}, {"test_data/pusch_demodulator_test_output82.dat"}},
  {{0.029224, 9.1004, {35572, {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 2, 12, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 2, 156, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols84.dat"}, {"test_data/pusch_demodulator_test_input_estimates84.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq84.dat"}, {"test_data/pusch_demodulator_test_output84.dat"}},
  {{0.0073234, 21.9987, {749, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 0, 12, {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE2, 1, 13, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols86.dat"}, {"test_data/pusch_demodulator_test_input_estimates86.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq86.dat"}, {"test_data/pusch_demodulator_test_output86.dat"}},
  {{0.00089315, 30.3226, {21309, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM64, 2, 11, {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 3, 39, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols88.dat"}, {"test_data/pusch_demodulator_test_input_estimates88.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq88.dat"}, {"test_data/pusch_demodulator_test_output88.dat"}},
  {{0.005099, 25.0125, {47542, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 0, 10, {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, dmrs_type::TYPE2, 1, 760, 1, {0}}}, {"test_data/pusch_demodulator_test_input_symbols90.dat"}, {"test_data/pusch_demodulator_test_input_estimates90.dat", {300, 14, 1, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq90.dat"}, {"test_data/pusch_demodulator_test_output90.dat"}},
  {{0.00089506, 31.2937, {59296, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 0, 12, {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 1, 898, 1, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols92.dat"}, {"test_data/pusch_demodulator_test_input_estimates92.dat", {300, 14, 2, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq92.dat"}, {"test_data/pusch_demodulator_test_output92.dat"}},
  {{0.018439, 12.0363, {44327, {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 0, 14, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 1, 635, 2, {0, 1}}}, {"test_data/pusch_demodulator_test_input_symbols94.dat"}, {"test_data/pusch_demodulator_test_input_estimates94.dat", {300, 14, 2, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq94.dat"}, {"test_data/pusch_demodulator_test_output94.dat"}},
  {{0.0011607, 30.1039, {5270, {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 1, 13, {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, dmrs_type::TYPE2, 1, 470, 1, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols96.dat"}, {"test_data/pusch_demodulator_test_input_estimates96.dat", {300, 14, 4, 1}}, {"test_data/pusch_demodulator_test_output_scrambling_seq96.dat"}, {"test_data/pusch_demodulator_test_output96.dat"}},
  {{0.017821, 16.2618, {2792, {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, modulation_scheme::QAM256, 0, 8, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, dmrs_type::TYPE2, 2, 380, 2, {0, 1, 2, 3}}}, {"test_data/pusch_demodulator_test_input_symbols98.dat"}, {"test_data/pusch_demodulator_test_input_estimates98.dat", {300, 14, 4, 2}}, {"test_data/pusch_demodulator_test_output_scrambling_seq98.dat"}, {"test_data/pusch_demodulator_test_output98.dat"}},
    // clang-format on
};

} // namespace srsran
