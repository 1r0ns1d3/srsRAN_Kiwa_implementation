/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/ran/pdcch/pdcch_type0_css_coreset_config.h"
#include "srsran/adt/span.h"
#include "srsran/ran/bs_channel_bandwidth.h"

using namespace srsran;

pdcch_type0_css_coreset_description srsran::pdcch_type0_css_coreset_get(min_channel_bandwidth minimum_bandwidth_MHz,
                                                                        subcarrier_spacing    ssb_scs,
                                                                        subcarrier_spacing    pdcch_scs,
                                                                        uint8_t               coreset_zero_index,
                                                                        uint8_t               subcarrier_offset,
                                                                        bool                  is_for_shared_spectrum)
{
  // TS38.213 Table 13-1. {SS/PBCH block, PDCCH} SCS is {15, 15} kHz and minimum channel bandwidth 5 MHz or 10 MHz.
  static const std::array<pdcch_type0_css_coreset_description, 15> TABLE_13_1 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 12},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 16},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 12},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 16},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 12},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 16},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 38},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 38},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 3, 38},
  }};
  // TS38.213 Table 13-1A (Only in Rel.17). {SS/PBCH block, PDCCH} SCS is {15, 15} kHz for frequency bands operated with
  // shared spectrum channel access.
  static const std::array<pdcch_type0_css_coreset_description, 8> TABLE_13_1_A = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 10},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 12},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 14},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 16},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 10},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 12},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 14},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 16},
  }};
  // TS38.213 Table 13-2. {SS/PBCH block, PDCCH} SCS is {15, 30} kHz and minimum channel bandwidth 5 MHz or 10 MHz.
  static const std::array<pdcch_type0_css_coreset_description, 14> TABLE_13_2 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 5},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 6},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 7},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 8},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 5},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 6},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 7},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 8},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 18},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 20},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 18},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 20},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 18},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 20},
  }};
  // TS38.213 Table 13-3. {SS/PBCH block, PDCCH} SCS is {30, 15} kHz and minimum channel bandwidth 5 MHz or 10 MHz.
  static const std::array<pdcch_type0_css_coreset_description, 9> TABLE_13_3 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 6},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 6},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 6},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 28},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 28},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 3, 28},
  }};
  // TS38.213 Table 13-4. {SS/PBCH block, PDCCH} SCS is {30, 30} kHz and minimum channel bandwidth 5 MHz or 10 MHz.
  static const std::array<pdcch_type0_css_coreset_description, 16> TABLE_13_4 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 1},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 3},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 1},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 3},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 12},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 14},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 16},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 12},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 14},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 16},
  }};
  // TS38.213 Table 13-4A (Only in Rel.17). {SS/PBCH block, PDCCH} SCS is {30, 30} kHz for frequency bands operated with
  // shared spectrum channel access.
  static const std::array<pdcch_type0_css_coreset_description, 8> TABLE_13_4_A = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 1},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 3},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 1},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 2},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 3},
  }};
  // TS38.213 Table 13-5. {SS/PBCH block, PDCCH} SCS is {30, 15} kHz and minimum channel bandwidth 40 MHz.
  static const std::array<pdcch_type0_css_coreset_description, 9> TABLE_13_5 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 56},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 56},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 3, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 3, 56},
  }};
  // TS38.213 Table 13-6. {SS/PBCH block, PDCCH} SCS is {30, 30} kHz and minimum channel bandwidth 40 MHz.
  static const std::array<pdcch_type0_css_coreset_description, 10> TABLE_13_6 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 3, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 28},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 28},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 28},
  }};
  // TS38.213 Table 13-7. {SS/PBCH block, PDCCH} SCS is {120, 60} kHz
  static const std::array<pdcch_type0_css_coreset_description, 12> TABLE_13_7 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 8},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 8},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 3, 8},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 28},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 28},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 48, 1, -41},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 48, 1, 49},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 96, 1, -41},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 96, 1, 97},
  }};
  // TS38.213 Table 13-8. {SS/PBCH block, PDCCH} SCS is {120, 120} kHz
  static const std::array<pdcch_type0_css_coreset_description, 8> TABLE_13_8 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 24, 2, 4},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 14},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 14},
      {ssb_coreset0_mplex_pattern::mplx_pattern3, 24, 2, -20},
      {ssb_coreset0_mplex_pattern::mplx_pattern3, 24, 2, 24},
      {ssb_coreset0_mplex_pattern::mplx_pattern3, 48, 2, -20},
      {ssb_coreset0_mplex_pattern::mplx_pattern3, 48, 2, 48},
  }};
  // TS38.213 Table 13-9. {SS/PBCH block, PDCCH} SCS is {240, 60} kHz
  static const std::array<pdcch_type0_css_coreset_description, 4> TABLE_13_9 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 1, 16},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 96, 2, 16},
  }};
  // TS38.213 Table 13-10. {SS/PBCH block, PDCCH} SCS is {240, 120} kHz
  static const std::array<pdcch_type0_css_coreset_description, 8> TABLE_13_10 = {{
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 1, 8},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 0},
      {ssb_coreset0_mplex_pattern::mplx_pattern1, 48, 2, 8},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 24, 1, -41},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 24, 1, 25},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 48, 1, -41},
      {ssb_coreset0_mplex_pattern::mplx_pattern2, 48, 1, 49},
  }};

  span<const pdcch_type0_css_coreset_description> table = {};
  if (ssb_scs == subcarrier_spacing::kHz15 && pdcch_scs == subcarrier_spacing::kHz15 && is_for_shared_spectrum) {
    table = TABLE_13_1_A;
  } else if (ssb_scs == subcarrier_spacing::kHz15 && pdcch_scs == subcarrier_spacing::kHz15 &&
             (minimum_bandwidth_MHz == min_channel_bandwidth::MHz5 ||
              minimum_bandwidth_MHz == min_channel_bandwidth::MHz10)) {
    table = TABLE_13_1;
  } else if (ssb_scs == subcarrier_spacing::kHz15 && pdcch_scs == subcarrier_spacing::kHz30 &&
             (minimum_bandwidth_MHz == min_channel_bandwidth::MHz5 ||
              minimum_bandwidth_MHz == min_channel_bandwidth::MHz10)) {
    table = TABLE_13_2;
  } else if (ssb_scs == subcarrier_spacing::kHz30 && pdcch_scs == subcarrier_spacing::kHz15 &&
             (minimum_bandwidth_MHz == min_channel_bandwidth::MHz5 ||
              minimum_bandwidth_MHz == min_channel_bandwidth::MHz10)) {
    table = TABLE_13_3;
  } else if (ssb_scs == subcarrier_spacing::kHz30 && pdcch_scs == subcarrier_spacing::kHz30 && is_for_shared_spectrum) {
    table = TABLE_13_4_A;
  } else if (ssb_scs == subcarrier_spacing::kHz30 && pdcch_scs == subcarrier_spacing::kHz30 &&
             (minimum_bandwidth_MHz == min_channel_bandwidth::MHz5 ||
              minimum_bandwidth_MHz == min_channel_bandwidth::MHz10)) {
    table = TABLE_13_4;
  } else if (ssb_scs == subcarrier_spacing::kHz30 && pdcch_scs == subcarrier_spacing::kHz15 &&
             minimum_bandwidth_MHz == min_channel_bandwidth::MHz40) {
    table = TABLE_13_5;
  } else if (ssb_scs == subcarrier_spacing::kHz30 && pdcch_scs == subcarrier_spacing::kHz30 &&
             minimum_bandwidth_MHz == min_channel_bandwidth::MHz40) {
    table = TABLE_13_6;
  } else if (ssb_scs == subcarrier_spacing::kHz120 && pdcch_scs == subcarrier_spacing::kHz60) {
    table = TABLE_13_7;
  } else if (ssb_scs == subcarrier_spacing::kHz120 && pdcch_scs == subcarrier_spacing::kHz120) {
    table = TABLE_13_8;
  } else if (ssb_scs == subcarrier_spacing::kHz240 && pdcch_scs == subcarrier_spacing::kHz60) {
    table = TABLE_13_9;
  } else if (ssb_scs == subcarrier_spacing::kHz240 && pdcch_scs == subcarrier_spacing::kHz120) {
    table = TABLE_13_10;
  }

  if (coreset_zero_index < table.size()) {
    pdcch_type0_css_coreset_description result = table[coreset_zero_index];

    if (result.offset < 0 && subcarrier_offset != 0) {
      --result.offset;
    }

    return result;
  }

  return PDCCH_TYPE0_CSS_CORESET_RESERVED;
}