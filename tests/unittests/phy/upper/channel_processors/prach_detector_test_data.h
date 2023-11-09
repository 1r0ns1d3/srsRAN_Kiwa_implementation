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

// This file was generated using the following MATLAB class on 09-11-2023 (seed 0):
//   + "srsPRACHDetectorUnittest.m"

#include "../../support/prach_buffer_test_doubles.h"
#include "srsran/phy/upper/channel_processors/prach_detector.h"
#include "srsran/support/file_vector.h"

namespace srsran {

using sequence_data_type =
    file_tensor<static_cast<unsigned>(prach_buffer_tensor::dims::count), cf_t, prach_buffer_tensor::dims>;

struct context_t {
  prach_detector::configuration config;
  phy_time_unit                 true_delay;
  prach_detection_result        result;
};

struct test_case_t {
  context_t          context;
  sequence_data_type symbols;
};

static const std::vector<test_case_t> prach_detector_test_data = {
    // clang-format off
  {{{834, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(1.3393e-06), {3.0457, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{57, phy_time_unit::from_seconds(1.5625e-06), 16.4352}}}}, {"test_data/prach_detector_test_input0.dat", {839, 1, 1, 1, 1}}},
  {{{334, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(4.80243e-06), {1.7138, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{52, phy_time_unit::from_seconds(4.6875e-06), 142.8708}}}}, {"test_data/prach_detector_test_input1.dat", {839, 1, 1, 1, 2}}},
  {{{783, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(7.78555e-07), {1.0401, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{22, phy_time_unit::from_seconds(7.8125e-07), 489.3583}}}}, {"test_data/prach_detector_test_input2.dat", {839, 1, 1, 1, 4}}},
  {{{566, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(3.5603e-06), {2.8733, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{15, phy_time_unit::from_seconds(3.90439e-06), 1.3899}}}}, {"test_data/prach_detector_test_input3.dat", {839, 1, 1, 1, 1}}},
  {{{95, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(5.59521e-06), {1.6922, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{7, phy_time_unit::from_seconds(5.51996e-06), 2210.7131}}}}, {"test_data/prach_detector_test_input4.dat", {839, 1, 1, 1, 2}}},
  {{{391, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(3.26669e-06), {0.89078, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{9, phy_time_unit::from_seconds(2.96763e-06), 9.6279}}}}, {"test_data/prach_detector_test_input5.dat", {839, 1, 1, 1, 4}}},
  {{{393, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(4.48846e-06), {3.1347, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{7, phy_time_unit::from_seconds(4.6875e-06), 47.6805}}}}, {"test_data/prach_detector_test_input6.dat", {839, 2, 1, 1, 1}}},
  {{{791, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(4.67271e-06), {1.8114, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{4, phy_time_unit::from_seconds(4.6875e-06), 327.1021}}}}, {"test_data/prach_detector_test_input7.dat", {839, 2, 1, 1, 2}}},
  {{{974, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(1.85079e-06), {0.94753, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{52, phy_time_unit::from_seconds(1.5625e-06), 269.8108}}}}, {"test_data/prach_detector_test_input8.dat", {839, 2, 1, 1, 4}}},
  {{{532, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(4.06865e-06), {3.0271, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{21, phy_time_unit::from_seconds(4.05989e-06), 716.2814}}}}, {"test_data/prach_detector_test_input9.dat", {839, 2, 1, 1, 1}}},
  {{{907, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(4.61801e-06), {1.7595, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{35, phy_time_unit::from_seconds(4.94357e-06), 2.6948}}}}, {"test_data/prach_detector_test_input10.dat", {839, 2, 1, 1, 2}}},
  {{{20, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(6.18073e-06), {1.0438, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{20, phy_time_unit::from_seconds(5.72668e-06), 4.177}}}}, {"test_data/prach_detector_test_input11.dat", {839, 2, 1, 1, 4}}},
  {{{311, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(1.32369e-06), {2.9134, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{15, phy_time_unit::from_seconds(1.5625e-06), 28.9283}}}}, {"test_data/prach_detector_test_input12.dat", {839, 4, 1, 1, 1}}},
  {{{987, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(5.24041e-06), {1.7393, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{1, phy_time_unit::from_seconds(5.46875e-06), 57.4003}}}}, {"test_data/prach_detector_test_input13.dat", {839, 4, 1, 1, 2}}},
  {{{580, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(1.32347e-06), {0.9652, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{52, phy_time_unit::from_seconds(1.5625e-06), 96.2699}}}}, {"test_data/prach_detector_test_input14.dat", {839, 4, 1, 1, 4}}},
  {{{990, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(1.80206e-06), {3.0482, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{46, phy_time_unit::from_seconds(1.45262e-06), 2.2128}}}}, {"test_data/prach_detector_test_input15.dat", {839, 4, 1, 1, 1}}},
  {{{45, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(4.3313e-06), {1.7766, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{43, phy_time_unit::from_seconds(4.10924e-06), 14.5683}}}}, {"test_data/prach_detector_test_input16.dat", {839, 4, 1, 1, 2}}},
  {{{335, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(2.14265e-06), {0.9954, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{34, phy_time_unit::from_seconds(1.92286e-06), 37.2443}}}}, {"test_data/prach_detector_test_input17.dat", {839, 4, 1, 1, 4}}},
  {{{269, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 1}, phy_time_unit::from_seconds(2.26122e-07), {3.0273, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{10, phy_time_unit::from_seconds(1.95312e-07), 87.3121}}}}, {"test_data/prach_detector_test_input18.dat", {839, 4, 1, 1, 1}}},
  {{{678, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 2}, phy_time_unit::from_seconds(1.3373e-06), {1.8312, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{27, phy_time_unit::from_seconds(1.36719e-06), 27.2666}}}}, {"test_data/prach_detector_test_input19.dat", {839, 4, 1, 1, 2}}},
  {{{267, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 4}, phy_time_unit::from_seconds(2.47093e-07), {0.95659, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{30, phy_time_unit::from_seconds(1.95312e-07), 458.7982}}}}, {"test_data/prach_detector_test_input20.dat", {839, 4, 1, 1, 4}}},
  {{{483, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 1}, phy_time_unit::from_seconds(2.25689e-07), {2.9928, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{6, phy_time_unit::from_seconds(2.34189e-07), 112.0901}}}}, {"test_data/prach_detector_test_input21.dat", {839, 4, 1, 1, 1}}},
  {{{231, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 2}, phy_time_unit::from_seconds(2.10239e-07), {1.692, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{23, phy_time_unit::from_seconds(1.81578e-07), 3948.1598}}}}, {"test_data/prach_detector_test_input22.dat", {839, 4, 1, 1, 2}}},
  {{{726, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 4}, phy_time_unit::from_seconds(4.0373e-07), {0.94302, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{41, phy_time_unit::from_seconds(2.98207e-07), 14.8967}}}}, {"test_data/prach_detector_test_input23.dat", {839, 4, 1, 1, 4}}},
  {{{228, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 1}, phy_time_unit::from_seconds(4.7059e-07), {2.9535, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{37, phy_time_unit::from_seconds(5.20833e-07), 11.2805}}}}, {"test_data/prach_detector_test_input24.dat", {139, 2, 1, 1, 1}}},
  {{{831, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 2}, phy_time_unit::from_seconds(7.6313e-08), {1.5666, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{46, phy_time_unit::from_seconds(0), 24.8573}}}}, {"test_data/prach_detector_test_input25.dat", {139, 2, 1, 1, 2}}},
  {{{401, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 4}, phy_time_unit::from_seconds(3.23354e-07), {1.0689, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{46, phy_time_unit::from_seconds(2.60417e-07), 277.4997}}}}, {"test_data/prach_detector_test_input26.dat", {139, 2, 1, 1, 4}}},
  {{{524, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 11, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 1}, phy_time_unit::from_seconds(3.86371e-07), {3.2353, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{52, phy_time_unit::from_seconds(3.747e-07), 13.0962}}}}, {"test_data/prach_detector_test_input27.dat", {139, 2, 1, 1, 1}}},
  {{{189, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 11, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 2}, phy_time_unit::from_seconds(1.32722e-07), {1.7662, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{50, phy_time_unit::from_seconds(1.8735e-07), 29.4785}}}}, {"test_data/prach_detector_test_input28.dat", {139, 2, 1, 1, 2}}},
  {{{400, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 11, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 4}, phy_time_unit::from_seconds(1.72021e-07), {0.95346, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{62, phy_time_unit::from_seconds(1.8735e-07), 81.5616}}}}, {"test_data/prach_detector_test_input29.dat", {139, 2, 1, 1, 4}}},
  {{{239, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 1}, phy_time_unit::from_seconds(4.67894e-07), {2.8937, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{10, phy_time_unit::from_seconds(5.20833e-07), 42.4742}}}}, {"test_data/prach_detector_test_input30.dat", {139, 12, 1, 1, 1}}},
  {{{356, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 2}, phy_time_unit::from_seconds(4.2583e-07), {1.7831, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{2, phy_time_unit::from_seconds(5.20833e-07), 26.1607}}}}, {"test_data/prach_detector_test_input31.dat", {139, 12, 1, 1, 2}}},
  {{{595, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 4}, phy_time_unit::from_seconds(4.85045e-07), {0.94761, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{62, phy_time_unit::from_seconds(5.20833e-07), 183.9362}}}}, {"test_data/prach_detector_test_input32.dat", {139, 12, 1, 1, 4}}},
  {{{896, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 11, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 1}, phy_time_unit::from_seconds(2.80792e-07), {3.1749, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{17, phy_time_unit::from_seconds(2.07959e-07), 40.2873}}}}, {"test_data/prach_detector_test_input33.dat", {139, 12, 1, 1, 1}}},
  {{{160, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 11, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 2}, phy_time_unit::from_seconds(3.76684e-07), {1.7804, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{18, phy_time_unit::from_seconds(2.60417e-07), 55.9275}}}}, {"test_data/prach_detector_test_input34.dat", {139, 12, 1, 1, 2}}},
  {{{201, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 11, 0, 64, to_ra_subcarrier_spacing("15.000000kHz"), 4}, phy_time_unit::from_seconds(3.72804e-07), {0.89666, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{52, phy_time_unit::from_seconds(3.747e-07), 167.153}}}}, {"test_data/prach_detector_test_input35.dat", {139, 12, 1, 1, 4}}},
  {{{311, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(4.91103e-06), {2.954, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{27, phy_time_unit::from_seconds(4.6875e-06), 19.4872}}}}, {"test_data/prach_detector_test_input36.dat", {839, 1, 1, 1, 1}}},
  {{{674, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(1.09155e-06), {1.8685, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{36, phy_time_unit::from_seconds(7.8125e-07), 28.5282}}}}, {"test_data/prach_detector_test_input37.dat", {839, 1, 1, 1, 2}}},
  {{{848, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(1.59729e-06), {0.92615, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{44, phy_time_unit::from_seconds(1.5625e-06), 618.0755}}}}, {"test_data/prach_detector_test_input38.dat", {839, 1, 1, 1, 4}}},
  {{{442, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(5.56976e-06), {2.9366, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{19, phy_time_unit::from_seconds(5.83097e-06), 3.2245}}}}, {"test_data/prach_detector_test_input39.dat", {839, 1, 1, 1, 1}}},
  {{{440, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(2.34588e-06), {1.7461, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{32, phy_time_unit::from_seconds(2.13144e-06), 10.9334}}}}, {"test_data/prach_detector_test_input40.dat", {839, 1, 1, 1, 2}}},
  {{{976, to_prach_format_type("0"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(4.19843e-06), {1.0114, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{22, phy_time_unit::from_seconds(3.9556e-06), 17.4823}}}}, {"test_data/prach_detector_test_input41.dat", {839, 1, 1, 1, 4}}},
  {{{385, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(1.78247e-06), {3.0976, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{52, phy_time_unit::from_seconds(1.5625e-06), 68.6962}}}}, {"test_data/prach_detector_test_input42.dat", {839, 2, 1, 1, 1}}},
  {{{195, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(5.80727e-06), {1.7551, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{53, phy_time_unit::from_seconds(5.46875e-06), 89.774}}}}, {"test_data/prach_detector_test_input43.dat", {839, 2, 1, 1, 2}}},
  {{{249, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(8.059e-07), {0.97047, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{59, phy_time_unit::from_seconds(7.8125e-07), 1097.4813}}}}, {"test_data/prach_detector_test_input44.dat", {839, 2, 1, 1, 4}}},
  {{{432, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(4.92108e-06), {3.1084, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{61, phy_time_unit::from_seconds(4.57576e-06), 1.7486}}}}, {"test_data/prach_detector_test_input45.dat", {839, 2, 1, 1, 1}}},
  {{{481, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(1.22736e-06), {1.7283, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{55, phy_time_unit::from_seconds(1.29525e-06), 99.4677}}}}, {"test_data/prach_detector_test_input46.dat", {839, 2, 1, 1, 2}}},
  {{{505, to_prach_format_type("1"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(9.6783e-07), {0.90095, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{36, phy_time_unit::from_seconds(9.3303e-07), 325.4728}}}}, {"test_data/prach_detector_test_input47.dat", {839, 2, 1, 1, 4}}},
  {{{90, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(2.14159e-06), {2.9593, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{53, phy_time_unit::from_seconds(2.34375e-06), 40.7685}}}}, {"test_data/prach_detector_test_input48.dat", {839, 4, 1, 1, 1}}},
  {{{37, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(1.41626e-06), {1.7503, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{54, phy_time_unit::from_seconds(1.5625e-06), 145.8211}}}}, {"test_data/prach_detector_test_input49.dat", {839, 4, 1, 1, 2}}},
  {{{27, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(3.17864e-06), {0.99185, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{58, phy_time_unit::from_seconds(3.125e-06), 2746.0559}}}}, {"test_data/prach_detector_test_input50.dat", {839, 4, 1, 1, 4}}},
  {{{740, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 1}, phy_time_unit::from_seconds(1.05566e-06), {3.0645, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{17, phy_time_unit::from_seconds(1.35206e-06), 2.3461}}}}, {"test_data/prach_detector_test_input51.dat", {839, 4, 1, 1, 1}}},
  {{{482, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 2}, phy_time_unit::from_seconds(1.99355e-06), {1.7296, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{44, phy_time_unit::from_seconds(1.6612e-06), 4.0316}}}}, {"test_data/prach_detector_test_input52.dat", {839, 4, 1, 1, 2}}},
  {{{58, to_prach_format_type("2"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("1.250000kHz"), 4}, phy_time_unit::from_seconds(9.59126e-07), {0.96055, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{30, phy_time_unit::from_seconds(7.77525e-07), 34.7426}}}}, {"test_data/prach_detector_test_input53.dat", {839, 4, 1, 1, 4}}},
  {{{557, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 1}, phy_time_unit::from_seconds(1.22246e-06), {2.8947, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{1, phy_time_unit::from_seconds(1.17187e-06), 50.0256}}}}, {"test_data/prach_detector_test_input54.dat", {839, 4, 1, 1, 1}}},
  {{{288, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 2}, phy_time_unit::from_seconds(8.20894e-07), {1.7084, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{15, phy_time_unit::from_seconds(7.8125e-07), 79.2291}}}}, {"test_data/prach_detector_test_input55.dat", {839, 4, 1, 1, 2}}},
  {{{137, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 4}, phy_time_unit::from_seconds(7.03698e-07), {0.90301, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{39, phy_time_unit::from_seconds(7.8125e-07), 11.7427}}}}, {"test_data/prach_detector_test_input56.dat", {839, 4, 1, 1, 4}}},
  {{{188, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 1}, phy_time_unit::from_seconds(1.22059e-06), {2.9436, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{15, phy_time_unit::from_seconds(1.17141e-06), 147.0242}}}}, {"test_data/prach_detector_test_input57.dat", {839, 4, 1, 1, 1}}},
  {{{788, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 2}, phy_time_unit::from_seconds(1.0324e-06), {1.7953, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{35, phy_time_unit::from_seconds(1.04058e-06), 211.642}}}}, {"test_data/prach_detector_test_input58.dat", {839, 4, 1, 1, 2}}},
  {{{37, to_prach_format_type("3"), restricted_set_config::UNRESTRICTED, 1, 0, 64, to_ra_subcarrier_spacing("5.000000kHz"), 4}, phy_time_unit::from_seconds(1.4355e-06), {0.96045, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{7, phy_time_unit::from_seconds(1.37999e-06), 62.3377}}}}, {"test_data/prach_detector_test_input59.dat", {839, 4, 1, 1, 4}}},
  {{{807, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 1}, phy_time_unit::from_seconds(2.42585e-07), {2.9819, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{9, phy_time_unit::from_seconds(2.60417e-07), 12.7403}}}}, {"test_data/prach_detector_test_input60.dat", {139, 2, 1, 1, 1}}},
  {{{394, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 2}, phy_time_unit::from_seconds(1.39275e-07), {1.7082, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{53, phy_time_unit::from_seconds(1.30208e-07), 51.4245}}}}, {"test_data/prach_detector_test_input61.dat", {139, 2, 1, 1, 2}}},
  {{{8, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 4}, phy_time_unit::from_seconds(1.30652e-07), {0.99926, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{17, phy_time_unit::from_seconds(1.30208e-07), 242.0786}}}}, {"test_data/prach_detector_test_input62.dat", {139, 2, 1, 1, 4}}},
  {{{850, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 14, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 1}, phy_time_unit::from_seconds(6.29431e-08), {3.2777, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{43, phy_time_unit::from_seconds(9.36751e-08), 3.8543}}}}, {"test_data/prach_detector_test_input63.dat", {139, 2, 1, 1, 1}}},
  {{{936, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 14, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 2}, phy_time_unit::from_seconds(2.01744e-07), {1.6994, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{6, phy_time_unit::from_seconds(1.30208e-07), 9.2102}}}}, {"test_data/prach_detector_test_input64.dat", {139, 2, 1, 1, 2}}},
  {{{983, to_prach_format_type("A1"), restricted_set_config::UNRESTRICTED, 14, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 4}, phy_time_unit::from_seconds(1.61024e-07), {0.94435, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{27, phy_time_unit::from_seconds(1.30208e-07), 278.4946}}}}, {"test_data/prach_detector_test_input65.dat", {139, 2, 1, 1, 4}}},
  {{{772, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 1}, phy_time_unit::from_seconds(3.51621e-08), {3.0906, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{7, phy_time_unit::from_seconds(0), 42.8417}}}}, {"test_data/prach_detector_test_input66.dat", {139, 12, 1, 1, 1}}},
  {{{355, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 2}, phy_time_unit::from_seconds(2.19284e-07), {1.7311, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{0, phy_time_unit::from_seconds(2.60417e-07), 26.9174}}}}, {"test_data/prach_detector_test_input67.dat", {139, 12, 1, 1, 2}}},
  {{{929, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 0, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 4}, phy_time_unit::from_seconds(2.59074e-07), {0.93263, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{63, phy_time_unit::from_seconds(2.60417e-07), 182.0978}}}}, {"test_data/prach_detector_test_input68.dat", {139, 12, 1, 1, 4}}},
  {{{549, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 14, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 1}, phy_time_unit::from_seconds(9.3693e-08), {2.9279, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{17, phy_time_unit::from_seconds(5.71418e-08), 145.8479}}}}, {"test_data/prach_detector_test_input69.dat", {139, 12, 1, 1, 1}}},
  {{{736, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 14, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 2}, phy_time_unit::from_seconds(4.84376e-08), {1.8268, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{7, phy_time_unit::from_seconds(9.36751e-08), 24.2136}}}}, {"test_data/prach_detector_test_input70.dat", {139, 12, 1, 1, 2}}},
  {{{561, to_prach_format_type("B4"), restricted_set_config::UNRESTRICTED, 14, 0, 64, to_ra_subcarrier_spacing("30.000000kHz"), 4}, phy_time_unit::from_seconds(1.39581e-07), {1.0216, phy_time_unit::from_seconds(0.0), phy_time_unit::from_seconds(0.0), {{54, phy_time_unit::from_seconds(1.30208e-07), 38294.0311}}}}, {"test_data/prach_detector_test_input71.dat", {139, 12, 1, 1, 4}}},
    // clang-format on
};

} // namespace srsran
