/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "buffered_slot_gateway_task_dispatcher.h"
#include "srsran/fapi/messages.h"
#include "srsran/srslog/srslog.h"
#include "srsran/support/executors/task_executor.h"

using namespace srsran;
using namespace fapi;

buffered_slot_gateway_task_dispatcher::buffered_slot_gateway_task_dispatcher(unsigned           l2_nof_slots_ahead,
                                                                             subcarrier_spacing scs_,
                                                                             fapi::slot_message_gateway& gateway,
                                                                             task_executor&              executor_) :
  scs(scs_),
  logger(srslog::fetch_basic_logger("FAPI")),
  executor(executor_),
  buffered_gateway(l2_nof_slots_ahead, scs_, gateway)
{
}

void buffered_slot_gateway_task_dispatcher::dl_tti_request(const dl_tti_request_message& msg)
{
  if (!executor.defer([this, msg]() { buffered_gateway.handle_dl_tti_request(msg); })) {
    logger.warning("Failed to cache DL_TTI.request message for slot '{}'", slot_point(scs, msg.sfn, msg.slot));
  }
}

void buffered_slot_gateway_task_dispatcher::ul_tti_request(const ul_tti_request_message& msg)
{
  if (!executor.defer([this, msg]() { buffered_gateway.handle_ul_tti_request(msg); })) {
    logger.warning("Failed to cache UL_TTI.request message for slot '{}'", slot_point(scs, msg.sfn, msg.slot));
  }
}

void buffered_slot_gateway_task_dispatcher::ul_dci_request(const ul_dci_request_message& msg)
{
  if (!executor.defer([this, msg]() { buffered_gateway.handle_ul_dci_request(msg); })) {
    logger.warning("Failed to cache UL_DCI.request message for slot '{}'", slot_point(scs, msg.sfn, msg.slot));
  }
}

void buffered_slot_gateway_task_dispatcher::tx_data_request(const tx_data_request_message& msg)
{
  if (!executor.defer([this, msg]() { buffered_gateway.handle_tx_data_request(msg); })) {
    logger.warning("Failed to cache TX_Data.request message for slot '{}'", slot_point(scs, msg.sfn, msg.slot));
  }
}

void buffered_slot_gateway_task_dispatcher::on_slot_indication(const slot_indication_message& msg)
{
  slot_point slot = slot_point(scs, msg.sfn, msg.slot);
  buffered_gateway.update_current_slot(slot);

  if (!executor.defer([this, slot]() { buffered_gateway.forward_cached_messages(slot); })) {
    logger.warning("Failed to dispatch cached messages for slot '{}'", slot);
  }
}
