/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/f1ap/cu_cp/f1ap_cu_factory.h"
#include "f1ap_cu_impl.h"

/// Notice this would be the only place were we include concrete class implementation files.

using namespace srsran;
using namespace srs_cu_cp;

std::unique_ptr<f1ap_cu> srsran::srs_cu_cp::create_f1ap(const f1ap_configuration&    f1ap_cfg_,
                                                        f1ap_message_notifier&       f1ap_pdu_notifier_,
                                                        f1ap_du_processor_notifier&  f1ap_du_processor_notifier_,
                                                        f1ap_du_management_notifier& f1ap_du_management_notifier_,
                                                        timer_manager&               timers_,
                                                        task_executor&               ctrl_exec_)
{
  auto f1ap_cu = std::make_unique<f1ap_cu_impl>(
      f1ap_cfg_, f1ap_pdu_notifier_, f1ap_du_processor_notifier_, f1ap_du_management_notifier_, timers_, ctrl_exec_);
  return f1ap_cu;
}
