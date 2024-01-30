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

#include "srsran/ngap/ngap.h"

namespace srsran {
namespace srs_cu_cp {

/// Interface to AMF node that can be accessed safely from the test main thread.
class amf_test_stub : public ngap_message_notifier
{
public:
  virtual void attach_cu_cp_pdu_handler(ngap_message_handler& cu_cp_) = 0;

  /// Pop PDU sent by CU-CP and received by AMF.
  virtual bool try_pop_rx_pdu(ngap_message& pdu) = 0;

  /// Push new Tx PDU from AMF to CU-CP.
  virtual void push_tx_pdu(const ngap_message& pdu) = 0;

  /// Enqueue an NGAP PDU that the AMF will automatically send as a response to the next CU-CP Tx PDU.
  virtual void enqueue_next_tx_pdu(const ngap_message& pdu) = 0;
};

/// Creates a dummy AMF node that does not automatically respond to NG setup requests.
std::unique_ptr<amf_test_stub> create_manual_amf_stub();

/// Creates a dummy AMF node that automatically responds to the NG setup request with success, for convenience.
std::unique_ptr<amf_test_stub> create_amf_stub();

} // namespace srs_cu_cp
} // namespace srsran