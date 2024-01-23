/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/ran/resource_allocation/ofdm_symbol_range.h"
#include "srsran/ran/slot_point.h"

namespace srsran {
struct resource_grid_context;
class resource_grid_reader;

namespace ofh {

/// Open Fronthaul User-Plane downlink data flow resource grid context.
struct data_flow_uplane_resource_grid_context {
  /// Provides the slot context within the system frame.
  slot_point slot;
  /// Provides the sector identifier.
  unsigned sector;
  /// Provides the port identifier.
  unsigned port;
  /// eAxC.
  unsigned eaxc;
  /// Symbol range.
  ofdm_symbol_range symbol_range;
};

/// Open Fronthaul User-Plane downlink data flow.
class data_flow_uplane_downlink_data
{
public:
  /// Default destructor.
  virtual ~data_flow_uplane_downlink_data() = default;

  /// Enqueues the User-Plane downlink data messages with the given context and resource grid.
  virtual void enqueue_section_type_1_message(const data_flow_uplane_resource_grid_context& context,
                                              const resource_grid_reader&                   grid) = 0;
};

} // namespace ofh
} // namespace srsran
