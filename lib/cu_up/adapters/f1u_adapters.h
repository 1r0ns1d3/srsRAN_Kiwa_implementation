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

#include "srsran/f1u/cu_up/f1u_rx_delivery_notifier.h"
#include "srsran/f1u/cu_up/f1u_rx_sdu_notifier.h"
#include "srsran/pdcp/pdcp_rx.h"
#include "srsran/pdcp/pdcp_tx.h"
#include "srsran/srslog/srslog.h"

namespace srsran {
namespace srs_cu_up {

/// Adapter between F1-U and PDCP
class f1u_pdcp_adapter final : public f1u_rx_sdu_notifier, public f1u_rx_delivery_notifier
{
public:
  void connect_pdcp(pdcp_rx_lower_interface& pdcp_rx_handler_, pdcp_tx_lower_interface& pdcp_tx_handler_)
  {
    pdcp_rx_handler = &pdcp_rx_handler_;
    pdcp_tx_handler = &pdcp_tx_handler_;
  }

  void on_new_sdu(byte_buffer_slice_chain sdu) override
  {
    if (pdcp_rx_handler == nullptr) {
      srslog::fetch_basic_logger("F1-U").warning("Unconnected PDCP handler. Dropping F1-U SDU");
    } else {
      pdcp_rx_handler->handle_pdu(std::move(sdu));
    }
  }

  void on_transmit_notification(uint32_t highest_pdcp_sn) override
  {
    pdcp_tx_handler->handle_transmit_notification(highest_pdcp_sn);
  }
  void on_delivery_notification(uint32_t highest_pdcp_sn) override
  {
    pdcp_tx_handler->handle_delivery_notification(highest_pdcp_sn);
  }

private:
  pdcp_rx_lower_interface* pdcp_rx_handler = nullptr;
  pdcp_tx_lower_interface* pdcp_tx_handler = nullptr;
};

} // namespace srs_cu_up
} // namespace srsran
