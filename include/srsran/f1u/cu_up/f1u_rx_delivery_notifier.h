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

#include <cstdint>

namespace srsran {
namespace srs_cu_up {

/// \brief This interface represents the notification exit point of the receiving side of a F1-U bearer of the CU-UP
/// through which the lower layer (e.g. RLC in the DU) notifies the PDCP Tx entity of transmit/delivery of PDCP PDUs.
class f1u_rx_delivery_notifier
{
public:
  virtual ~f1u_rx_delivery_notifier() = default;

  virtual void on_transmit_notification(uint32_t highest_pdcp_sn) = 0;
  virtual void on_delivery_notification(uint32_t highest_pdcp_sn) = 0;
};

} // namespace srs_cu_up
} // namespace srsran
