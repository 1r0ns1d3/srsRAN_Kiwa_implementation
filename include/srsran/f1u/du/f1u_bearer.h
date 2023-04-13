/*
 *
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "f1u_rx_pdu_handler.h"
#include "f1u_tx_delivery_handler.h"
#include "f1u_tx_sdu_handler.h"

namespace srsran {
namespace srs_du {

constexpr uint32_t f1u_ul_notif_time_ms = 10;

class f1u_bearer
{
public:
  virtual ~f1u_bearer() = default;

  virtual f1u_rx_pdu_handler&      get_rx_pdu_handler()      = 0;
  virtual f1u_tx_delivery_handler& get_tx_delivery_handler() = 0;
  virtual f1u_tx_sdu_handler&      get_tx_sdu_handler()      = 0;
};

} // namespace srs_du
} // namespace srsran
