/*
 *
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "f1u_rx_pdu_handler.h"
#include "f1u_tx_sdu_handler.h"
#include "srsran/ran/up_transport_layer_info.h"

namespace srsran {
namespace srs_cu_up {

constexpr uint32_t f1u_dl_notif_time_ms = 10;

class f1u_bearer_disconnector;

class f1u_bearer
{
public:
  f1u_bearer()          = default;
  virtual ~f1u_bearer() = default;

  f1u_bearer(const f1u_bearer&)            = delete;
  f1u_bearer(f1u_bearer&&)                 = delete;
  f1u_bearer& operator=(const f1u_bearer&) = delete;
  f1u_bearer& operator=(f1u_bearer&&)      = delete;

  virtual void                stop()               = 0;
  virtual f1u_rx_pdu_handler& get_rx_pdu_handler() = 0;
  virtual f1u_tx_sdu_handler& get_tx_sdu_handler() = 0;
};

/// This class represents the interface through which a F1-U bearer disconnects from its gateway upon destruction
class f1u_bearer_disconnector
{
public:
  virtual ~f1u_bearer_disconnector() = default;

  virtual void disconnect_cu_bearer(const up_transport_layer_info& ul_up_tnl_info) = 0;
};

} // namespace srs_cu_up
} // namespace srsran
