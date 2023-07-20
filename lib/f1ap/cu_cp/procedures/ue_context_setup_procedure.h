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

#include "../f1ap_cu_impl.h"
#include "common/f1ap_asn1_utils.h"
#include "cu_cp/ue_context/f1ap_cu_ue_transaction_manager.h"
#include "srsran/asn1/f1ap/f1ap.h"
#include "srsran/f1ap/cu_cp/f1ap_cu.h"
#include "srsran/support/async/async_task.h"

namespace srsran {
namespace srs_cu_cp {

class ue_context_setup_procedure
{
public:
  ue_context_setup_procedure(const f1ap_ue_context_setup_request& request_,
                             f1ap_ue_context&                     ue_ctxt_,
                             f1ap_message_notifier&               f1ap_notif_,
                             srslog::basic_logger&                logger_);

  void operator()(coro_context<async_task<f1ap_ue_context_setup_response>>& ctx);

  static const char* name() { return "UE Context Setup Procedure"; }

private:
  /// Send F1 UE Context Setup Request to DU.
  void send_ue_context_setup_request();

  /// Creates procedure result to send back to procedure caller.
  f1ap_ue_context_setup_response create_ue_context_setup_result();

  const f1ap_ue_context_setup_request request;
  f1ap_ue_context&                    ue_ctxt;
  f1ap_message_notifier&              f1ap_notifier;
  srslog::basic_logger&               logger;

  protocol_transaction_outcome_observer<asn1::f1ap::ue_context_setup_resp_s, asn1::f1ap::ue_context_setup_fail_s>
      transaction_sink;
};

} // namespace srs_cu_cp
} // namespace srsran