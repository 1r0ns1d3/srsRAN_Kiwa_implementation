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

#include "srsran/adt/byte_buffer.h"
#include "srsran/ran/cu_types.h"

struct sockaddr_storage;

/*
 * This file will hold the interfaces and notifiers for the GTP-U tunnel.
 * They follow the following nomenclature:
 *
 *   gtpu_tunnel_{tx/rx}_{lower/upper}_layer_{interface/notifier}
 *
 * 1. TX/RX indicates whether the interface is intended for the
 *    TX or RX side of the tunnel. TX/RX terminology is used from the
 *    perspective of the GTP-U, i.e. are we receiving or sending packets to
 *    the socket gateway.
 * 2. Lower/Upper indicates whether the interface/notifier interacts
 *    with the upper or lower layers.
 * 3. Interface/Notifier: whether this is an interface the GTP-U tunnel will
 *    inherit or a notifier that the GTP-U will keep as a member.
 *
 */

namespace srsran {

/****************************************
 * Interfaces/notifiers for the gateway
 ****************************************/
/// This interface represents the data entry point of the transmitting side of a GTP-U entity.
/// The layers-layers will use this call to pass GTP-U SDUs into the TX entity.
class gtpu_tunnel_tx_lower_layer_interface
{
public:
  gtpu_tunnel_tx_lower_layer_interface()                                                        = default;
  virtual ~gtpu_tunnel_tx_lower_layer_interface()                                               = default;
  gtpu_tunnel_tx_lower_layer_interface(const gtpu_tunnel_tx_lower_layer_interface&)             = delete;
  gtpu_tunnel_tx_lower_layer_interface& operator=(const gtpu_tunnel_tx_lower_layer_interface&)  = delete;
  gtpu_tunnel_tx_lower_layer_interface(const gtpu_tunnel_tx_lower_layer_interface&&)            = delete;
  gtpu_tunnel_tx_lower_layer_interface& operator=(const gtpu_tunnel_tx_lower_layer_interface&&) = delete;

  /// \brief Interface for the lower layers to pass SDUs into the GTP-U
  /// \param sdu SDU to be handled
  /// \param qfi QoS flow associated with the SDU
  virtual void handle_sdu(byte_buffer sdu, qos_flow_id_t qfi) = 0;
};

/// This interface represents the data exit point of the transmitting side of a GTP-U entity.
/// The GTP-U will use this notifier to pass GTP-U PDUs into the socket gateway.
class gtpu_tunnel_tx_upper_layer_notifier
{
public:
  gtpu_tunnel_tx_upper_layer_notifier()                                                       = default;
  virtual ~gtpu_tunnel_tx_upper_layer_notifier()                                              = default;
  gtpu_tunnel_tx_upper_layer_notifier(const gtpu_tunnel_tx_upper_layer_notifier&)             = delete;
  gtpu_tunnel_tx_upper_layer_notifier& operator=(const gtpu_tunnel_tx_upper_layer_notifier&)  = delete;
  gtpu_tunnel_tx_upper_layer_notifier(const gtpu_tunnel_tx_upper_layer_notifier&&)            = delete;
  gtpu_tunnel_tx_upper_layer_notifier& operator=(const gtpu_tunnel_tx_upper_layer_notifier&&) = delete;

  /// \brief Interface for the GTP-U to pass PDUs to the IO gateway
  /// \param sdu PDU to be transmitted.
  virtual void on_new_pdu(byte_buffer buf, const sockaddr_storage& addr) = 0;
};

} // namespace srsran
