/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "bearer_context_modification_procedure.h"
#include "../e1ap_cu_cp_asn1_helpers.h"
#include "cu_cp/ue_context/e1ap_bearer_transaction_manager.h"

using namespace srsran;
using namespace srsran::srs_cu_cp;
using namespace asn1::e1ap;

bearer_context_modification_procedure::bearer_context_modification_procedure(const e1ap_message&              request_,
                                                                             e1ap_bearer_transaction_manager& ev_mng_,
                                                                             e1ap_message_notifier& e1ap_notif_,
                                                                             e1ap_ue_logger&        logger_) :
  request(request_), ev_mng(ev_mng_), e1ap_notifier(e1ap_notif_), logger(logger_)
{
}

void bearer_context_modification_procedure::operator()(
    coro_context<async_task<e1ap_bearer_context_modification_response>>& ctx)
{
  CORO_BEGIN(ctx);

  logger.log_debug("\"{}\" initialized", name());

  // Subscribe to respective publisher to receive BEARER CONTEXT MODIFICATION RESPONSE/FAILURE message.
  transaction_sink.subscribe_to(ev_mng.context_modification_outcome);

  // Send command to CU-UP.
  send_bearer_context_modification_request();

  // Await response.
  CORO_AWAIT(transaction_sink);

  // Handle response from CU-UP and return UE index
  CORO_RETURN(create_bearer_context_modification_result());
}

void bearer_context_modification_procedure::send_bearer_context_modification_request()
{
  if (logger.get_basic_logger().debug.enabled()) {
    asn1::json_writer js;
    request.pdu.to_json(js);
    logger.log_debug("Containerized BearerContextModificationRequest: {}", js.to_string());
  }

  // send UE context modification request message
  e1ap_notifier.on_new_message(request);
}

e1ap_bearer_context_modification_response
bearer_context_modification_procedure::create_bearer_context_modification_result()
{
  e1ap_bearer_context_modification_response res{};

  if (transaction_sink.successful()) {
    const asn1::e1ap::bearer_context_mod_resp_s& resp = transaction_sink.response();
    logger.log_debug("Received BearerContextModificationResponse");
    if (logger.get_basic_logger().debug.enabled()) {
      asn1::json_writer js;
      resp.to_json(js);
      logger.log_debug("Containerized BearerContextModificationResponse: {}", js.to_string());
    }
    fill_e1ap_bearer_context_modification_response(res, resp);

    logger.log_debug("\"{}\" finalized", name());
  } else if (transaction_sink.failed()) {
    const asn1::e1ap::bearer_context_mod_fail_s& fail = transaction_sink.failure();
    logger.log_debug("Received BearerContextModificationFailure cause={}", get_cause_str(fail->cause));
    if (logger.get_basic_logger().debug.enabled()) {
      asn1::json_writer js;
      fail.to_json(js);
      logger.log_debug("Containerized BearerContextModificationFailure: {}", js.to_string());
    }
    fill_e1ap_bearer_context_modification_response(res, fail);

    logger.log_error("\"{}\" failed", name());
  } else {
    logger.log_warning("BearerContextModificationResponse timeout");
    res.success = false;

    logger.log_error("\"{}\" failed", name());
  }
  return res;
}