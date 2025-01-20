/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "f1ap_du_test_messages.h"
#include "srsran/asn1/f1ap/common.h"
#include "srsran/asn1/f1ap/f1ap_pdu_contents.h"
#include "srsran/f1ap/f1ap_message.h"

using namespace srsran;
using namespace asn1::f1ap;

f1ap_message srsran::generate_f1_setup_response_message(unsigned transaction_id)
{
  f1ap_message f1_setup_response = {};

  f1_setup_response.pdu.set_successful_outcome();
  f1_setup_response.pdu.successful_outcome().load_info_obj(ASN1_F1AP_ID_F1_SETUP);

  auto& setup_res                = f1_setup_response.pdu.successful_outcome().value.f1_setup_resp();
  setup_res->transaction_id      = transaction_id;
  setup_res->gnb_cu_name_present = true;
  setup_res->gnb_cu_name.from_string("srsCU");
  setup_res->gnb_cu_rrc_version.latest_rrc_version.from_number(2);

  return f1_setup_response;
}

f1ap_message srsran::generate_f1_setup_failure_message(unsigned transaction_id, asn1::f1ap::time_to_wait_e time_to_wait)
{
  f1ap_message f1_setup_failure = {};

  f1_setup_failure.pdu.set_unsuccessful_outcome();
  f1_setup_failure.pdu.unsuccessful_outcome().load_info_obj(ASN1_F1AP_ID_F1_SETUP);

  auto& setup_fail           = f1_setup_failure.pdu.unsuccessful_outcome().value.f1_setup_fail();
  setup_fail->transaction_id = transaction_id;
  setup_fail->cause.set_radio_network();
  setup_fail->cause.radio_network() =
      asn1::f1ap::cause_radio_network_opts::options::unknown_or_already_allocated_gnb_cu_ue_f1ap_id;
  setup_fail->time_to_wait_present     = false;
  setup_fail->crit_diagnostics_present = false;
  // add critical diagnostics

  if (time_to_wait.value != asn1::f1ap::time_to_wait_opts::nulltype) {
    setup_fail->time_to_wait_present = true;
    setup_fail->time_to_wait.value   = time_to_wait;
  }

  return f1_setup_failure;
}

f1ap_message srsran::generate_f1ap_dl_rrc_message_transfer(srb_id_t srb_id, const byte_buffer& rrc_container)
{
  f1ap_message msg;

  msg.pdu.set_init_msg().load_info_obj(ASN1_F1AP_ID_DL_RRC_MSG_TRANSFER);
  auto& dl_msg              = msg.pdu.init_msg().value.dl_rrc_msg_transfer();
  dl_msg->gnb_cu_ue_f1ap_id = 0;
  dl_msg->gnb_du_ue_f1ap_id = 0;
  dl_msg->srb_id            = srb_id_to_uint(srb_id);
  dl_msg->rrc_container     = rrc_container.deep_copy().value();

  return msg;
}
