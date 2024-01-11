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

#include "srsran/ran/cu_types.h"
#include "srsran/sdap/sdap.h"
#include "srsran/support/timers.h"
#include <memory>

/// This factory header file depends on the SDAP interfaces (see above include list). It is kept separate as clients of
/// the SDAP interfaces dont need to call factory methods.

namespace srsran {

namespace srs_cu_up {

struct sdap_entity_creation_message {
  uint32_t              ue_index;
  pdu_session_id_t      pdu_session_id;
  unique_timer&         ue_inactivity_timer;
  sdap_rx_sdu_notifier* rx_sdu_notifier;
};

/// Creates an instance of a SDAP interface.
std::unique_ptr<sdap_entity> create_sdap(sdap_entity_creation_message& msg);

} // namespace srs_cu_up

} // namespace srsran
