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

#include "srsran/gtpu/gtpu_tunnel_rx.h"
#include "srsran/gtpu/gtpu_tunnel_tx.h"

namespace srsran {

/// Class used to interface with an GTP-U tunnel.
/// It will contain getters for the TX and RX entities interfaces.
/// TX and RX is considered from the perspective of the GTP-U.
class gtpu_tunnel_ngu
{
public:
  gtpu_tunnel_ngu()                                   = default;
  virtual ~gtpu_tunnel_ngu()                          = default;
  gtpu_tunnel_ngu(const gtpu_tunnel_ngu&)             = delete;
  gtpu_tunnel_ngu& operator=(const gtpu_tunnel_ngu&)  = delete;
  gtpu_tunnel_ngu(const gtpu_tunnel_ngu&&)            = delete;
  gtpu_tunnel_ngu& operator=(const gtpu_tunnel_ngu&&) = delete;

  virtual gtpu_tunnel_rx_upper_layer_interface* get_rx_upper_layer_interface() = 0;
  virtual gtpu_tunnel_tx_lower_layer_interface* get_tx_lower_layer_interface() = 0;
};

} // namespace srsran
