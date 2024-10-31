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

#include "srsran/ran/du_types.h"
#include "srsran/ran/logical_channel/lcid.h"

namespace srsran {

/// DL Buffer state for a given RLC bearer.
struct mac_dl_buffer_state_indication_message {
  du_ue_index_t ue_index;
  lcid_t        lcid;
  unsigned      bs;
};

class mac_ue_control_information_handler
{
public:
  virtual ~mac_ue_control_information_handler() = default;

  /// Forwards a new DL buffer state for a given UE and logical channel to the MAC.
  /// \param dl_bs Updated DL buffer state information for a logical channel.
  virtual void handle_dl_buffer_state_update(const mac_dl_buffer_state_indication_message& dl_bs) = 0;
};

} // namespace srsran