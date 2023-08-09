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

#include "srsran/ofh/serdes/ofh_message_properties.h"
#include "srsran/ran/ofdm_symbol_range.h"
#include "srsran/ran/prach/prach_subcarrier_spacing.h"
#include "srsran/ran/slot_point.h"

namespace srsran {
namespace ofh {

/// Parameters used to build Open Fronthaul PRACH Control-Plane message of section type 3.
struct data_flow_cplane_scheduling_prach_context {
  /// Slot point.
  slot_point slot;
  /// eAxC.
  unsigned eaxc;
  /// Filter type.
  filter_index_type filter_type;
  /// This parameter is the last symbol that starts right at or before the PRACH preamble (after cyclic prefix).
  unsigned start_symbol;
  /// Number of PRACH repetitions, used to initialize numSymbol parameter.
  unsigned nof_repetitions;
  /// PUSCH subcarrier spacing.
  subcarrier_spacing scs;
  /// PRACH subcarrier spacing.
  prach_subcarrier_spacing prach_scs;
  /// First subcarrier index used by PRACH message.
  unsigned prach_start_re;
  /// Number of PRBs used by PRACH.
  unsigned prach_nof_rb;
  /// Time offset to the start of PRACH.
  unsigned time_offset;
};

/// Open Fronthaul Control-Plane type 1 context parameters.
struct data_flow_cplane_type_1_context {
  /// Slot point.
  slot_point slot;
  /// eAxC.
  unsigned eaxc;
  /// Filter type.
  filter_index_type filter_type;
  /// Direction.
  data_direction direction;
  /// Symbol range.
  ofdm_symbol_range symbol_range;
};

/// Open Fronthaul data flow for Control-Plane scheduling and beamforming commands.
class data_flow_cplane_scheduling_commands
{
public:
  /// Default destructor.
  virtual ~data_flow_cplane_scheduling_commands() = default;

  /// Enqueues Open Fronthaul section type 1 message with the given slot and eAxC.
  virtual void enqueue_section_type_1_message(const data_flow_cplane_type_1_context& context) = 0;

  /// Enqueues Open Fronthaul section type 3 PRACH message with the given parameters.
  virtual void enqueue_section_type_3_prach_message(const data_flow_cplane_scheduling_prach_context& context) = 0;
};

} // namespace ofh
} // namespace srsran
