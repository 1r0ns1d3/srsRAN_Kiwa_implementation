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

#include "ul_bsr.h"
#include "srsran/srslog/srslog.h"

using namespace srsran;

/// TS 38.321, Table 6.1.3.1-1 Buffer size levels (in bytes) for 5-bit Buffer Size field, all values <= except marked
constexpr auto buffer_size_levels_5bit = to_array<uint32_t>(
    {/* == */ 0, 10,    14,    20,    28,    38,    53,    74,     102,    142,           198,
     276,        384,   535,   745,   1038,  1446,  2014,  2806,   3909,   5446,          7587,
     10570,      14726, 20516, 28581, 39818, 55474, 77284, 107669, 150000, /* > */ 150000});

/// TS 38.321, Table 6.1.3.1-2: Buffer size levels (in bytes) for 8-bit Buffer Size field, all values <= except marked
constexpr auto buffer_size_levels_8bit =
    to_array<uint32_t>({/* == */ 0, 10,       11,       12,       13,
                        14,         15,       16,       17,       18,
                        19,         20,       22,       23,       25,
                        26,         28,       30,       32,       34,
                        36,         38,       40,       43,       46,
                        49,         52,       55,       59,       62,
                        66,         71,       75,       80,       85,
                        91,         97,       103,      110,      117,
                        124,        132,      141,      150,      160,
                        170,        181,      193,      205,      218,
                        233,        248,      264,      281,      299,
                        318,        339,      361,      384,      409,
                        436,        464,      494,      526,      560,
                        597,        635,      677,      720,      767,
                        817,        870,      926,      987,      1051,
                        1119,       1191,     1269,     1351,     1439,
                        1532,       1631,     1737,     1850,     1970,
                        2098,       2234,     2379,     2533,     2698,
                        2873,       3059,     3258,     3469,     3694,
                        3934,       4189,     4461,     4751,     5059,
                        5387,       5737,     6109,     6506,     6928,
                        7378,       7857,     8367,     8910,     9488,
                        10104,      10760,    11458,    12202,    12994,
                        13838,      14736,    15692,    16711,    17795,
                        18951,      20181,    21491,    22885,    24371,
                        25953,      27638,    29431,    31342,    33376,
                        35543,      37850,    40307,    42923,    45709,
                        48676,      51836,    55200,    58784,    62599,
                        66663,      70990,    75598,    80505,    85730,
                        91295,      97221,    103532,   110252,   117409,
                        125030,     133146,   141789,   150992,   160793,
                        171231,     182345,   194182,   206786,   220209,
                        234503,     249725,   265935,   283197,   301579,
                        321155,     342002,   364202,   387842,   413018,
                        439827,     468377,   498780,   531156,   565634,
                        602350,     641449,   683087,   727427,   774645,
                        824928,     878475,   935498,   996222,   1060888,
                        1129752,    1203085,  1281179,  1364342,  1452903,
                        1547213,    1647644,  1754595,  1868488,  1989774,
                        2118933,    2256475,  2402946,  2558924,  2725027,
                        2901912,    3090279,  3290873,  3504487,  3731968,
                        3974215,    4232186,  4506902,  4799451,  5110989,
                        5442750,    5796046,  6172275,  6572925,  6999582,
                        7453933,    7937777,  8453028,  9001725,  9586039,
                        10208280,   10870913, 11576557, 12328006, 13128233,
                        13980403,   14887889, 15854280, 16883401, 17979324,
                        19146385,   20389201, 21712690, 23122088, 24622972,
                        26221280,   27923336, 29735875, 31666069, 33721553,
                        35910462,   38241455, 40723756, 43367187, 46182206,
                        49179951,   52372284, 55771835, 59392055, 63247269,
                        67352729,   71724679, 76380419, 81338368, /* > */ 81338368});

expected<long_bsr_report> srsran::decode_lbsr(bsr_format format, byte_buffer_view payload)
{
  long_bsr_report lbsr = {};

  // Represents a Long BSR report with buffer size set to 0 for all LCGs.
  static const long_bsr_report empty_lbsr_report = {.list =
                                                        {
                                                            {uint_to_lcg_id(0), 0},
                                                            {uint_to_lcg_id(1), 0},
                                                            {uint_to_lcg_id(2), 0},
                                                            {uint_to_lcg_id(3), 0},
                                                            {uint_to_lcg_id(4), 0},
                                                            {uint_to_lcg_id(5), 0},
                                                            {uint_to_lcg_id(6), 0},
                                                            {uint_to_lcg_id(7), 0},
                                                        }

  };

  byte_buffer_reader reader = payload;

  // read LCG bitmap
  const uint8_t bitmap = *reader;
  ++reader;

  // early stop if LBSR is empty
  if (bitmap == 0) {
    // See TS 38.321, clause 5.4.5. Padding BSR: "UL resources are allocated and number of padding bits is equal to or
    // larger than the size of the Buffer Status Report MAC CE plus its subheader".
    // For Padding BSR, "if the number of padding bits is equal to or larger than the size of the Long BSR plus its
    // subheader, report Long BSR for all LCGs which have data available for transmission".

    // NOTE: This is a loophole in specification where UL resources allocated are big enough that the number of padding
    // bits is larger than size of Long BSR plus its subheader and there is no data available for transmission.

    // [Implementation-defined] If all LCG(i) bits are zero, we assume buffer status to be zero since some basebands
    // send LBSR with all zero to indicate buffer status of zero.
    return empty_lbsr_report;
  }

  for (uint8_t i = 0; i != MAX_NOF_LCGS; i++) {
    // If LCGi bit is enabled, it means the next 8-bit BSR value corresponds to it
    if ((bitmap & (0x1U << i)) != 0) {
      lcg_bsr_report bsr = {};
      bsr.lcg_id         = uint_to_lcg_id(i);
      if (reader.length() > 0) {
        bsr.buffer_size = *reader;
        ++reader;

        if (bsr.buffer_size == 255) {
          srslog::fetch_basic_logger("MAC").warning("lcg={}: Discarding BSR. Cause: BSR=255 is invalid.", i);
          return make_unexpected(default_error_t{});
        }
      } else if (format == bsr_format::LONG_TRUNC_BSR) {
        // In the case of Long truncated BSR, some LCG buffer sizes may not be present. Assume BSR > 0 in that case.
        // Assume that the LCG has 64 bytes pending (implementation-defined).
        bsr.buffer_size = 64;
      } else {
        srslog::fetch_basic_logger("MAC").error("Error parsing LongBSR CE: sdu_length={} but there are {} active bsr\n",
                                                payload.length(),
                                                lbsr.list.size());
        return make_unexpected(default_error_t{});
      }
      lbsr.list.push_back(bsr);
    } else if (format == bsr_format::LONG_TRUNC_BSR) {
      // As per TS 38.321, clause 6.1.3, "For the Long BSR format, this field indicates the presence of the Buffer Size
      // field for the logical channel group i. The LCGi field set to "1" indicates that the Buffer Size field for the
      // logical channel group i is reported. The LCGi field set to "0" indicates that the Buffer Size field for the
      // logical channel group i is not reported.
      // For the Long Truncated BSR format, this field indicates whether logical channel group i has data available.The
      // LCGi field set to "1" indicates that logical channel group i has data available. The LCGi field set to "0"
      // indicates that logical channel group i does not have data available".
      lbsr.list.push_back({uint_to_lcg_id(i), 0});
    }
  }

  return lbsr;
}

/// Converts the buffer size field of a BSR (5 or 8-bit Buffer Size field) into Bytes.
/// \param buff_size_index The buffer size field contained in the MAC PDU.
/// \param format The BSR format that determines the buffer size field length.
/// \return The actual buffer size level in Bytes.
uint32_t srsran::buff_size_field_to_bytes(size_t buff_size_index, bsr_format format)
{
  // [Implementation-defined] Difference between the 2nd largest and the largest UL buffer size in bytes.
  // The resulting value of largest UL buffer (700kB) is approx. the amount of UL data that can be transmitted during 1
  // frame, assuming (i) 1 UE; (ii) 2 layers-UL MIMO; (iii) 2D1S7U TDD pattern. This value is enough to guarantee that
  // the scheduler UL pending data never reach 0 in between 2 consecutive BSRs, which we observed to be reported every
  // frame during UL-UDP full buffer (this value depends on the configuration).
  static constexpr uint32_t max_offset = 550000;

  // Early exit
  if (buff_size_index == 0) {
    return 0;
  }

  switch (format) {
    case bsr_format::SHORT_BSR:
    case bsr_format::SHORT_TRUNC_BSR: {
      const size_t   idx    = std::min(buff_size_index, buffer_size_levels_5bit.size() - 1);
      const uint32_t offset = buff_size_index >= buffer_size_levels_5bit.size() - 1 ? max_offset : 0;
      return buffer_size_levels_5bit[idx] + offset;
    } break;
    case bsr_format::LONG_BSR:
    case bsr_format::LONG_TRUNC_BSR: {
      const size_t   idx    = std::min(buff_size_index, buffer_size_levels_8bit.size() - 1);
      const uint32_t offset = buff_size_index >= buffer_size_levels_8bit.size() - 1 ? max_offset : 0;
      return buffer_size_levels_8bit[idx] + offset;
    } break;
    default:
      break;
  }
  return 0;
}
