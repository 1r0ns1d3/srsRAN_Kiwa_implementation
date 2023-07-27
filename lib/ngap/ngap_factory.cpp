/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/ngap/ngap_factory.h"
#include "ngap_impl.h"

/// Notice this would be the only place were we include concrete class implementation files.

using namespace srsran;
using namespace srs_cu_cp;

std::unique_ptr<ngap_interface>
srsran::srs_cu_cp::create_ngap(ngap_configuration&                ngap_cfg_,
                               ngap_cu_cp_du_repository_notifier& cu_cp_du_repository_notifier_,
                               ngap_ue_task_scheduler&            task_sched_,
                               ngap_ue_manager&                   ue_manager_,
                               ngap_message_notifier&             ngap_notifier_,
                               task_executor&                     ctrl_exec_)
{
  auto ngap = std::make_unique<ngap_impl>(
      ngap_cfg_, cu_cp_du_repository_notifier_, task_sched_, ue_manager_, ngap_notifier_, ctrl_exec_);
  return ngap;
}
