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

#include "gtpu_echo_rx_impl.h"
#include "gtpu_echo_tx_impl.h"
#include "srsran/gtpu/gtpu_echo.h"
#include "srsran/gtpu/gtpu_tunnel_tx.h"
#include "srsran/pcap/pcap.h"

namespace srsran {

/// Implementation of the GTP-U path management entity, i.e. echo request/response, supported extension headers notif.
class gtpu_echo_impl : public gtpu_echo
{
public:
  gtpu_echo_impl(dlt_pcap& gtpu_pcap, gtpu_tunnel_tx_upper_layer_notifier& tx_upper) :
    logger(srslog::fetch_basic_logger("GTPU"))
  {
    tx = std::make_unique<gtpu_echo_tx>(gtpu_pcap, tx_upper);
    rx = std::make_unique<gtpu_echo_rx>(*tx.get());
  }
  ~gtpu_echo_impl() override = default;

  gtpu_tunnel_rx_upper_layer_interface* get_rx_upper_layer_interface() final { return rx.get(); }

private:
  srslog::basic_logger& logger;

  std::unique_ptr<gtpu_echo_tx> tx = {};
  std::unique_ptr<gtpu_echo_rx> rx = {};
};
} // namespace srsran
