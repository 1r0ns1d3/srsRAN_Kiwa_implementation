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

#include "../cu_cp_impl_interface.h"
#include "../task_schedulers/ue_task_scheduler.h"
#include "../ue_manager_impl.h"
#include "srsran/support/async/async_task.h"
#include "srsran/support/async/eager_async_task.h"

namespace srsran {
namespace srs_cu_cp {

/// \brief Removes a UE from the CU-CP
class ue_removal_routine
{
public:
  ue_removal_routine(ue_index_t                      ue_index_,
                     cu_cp_rrc_ue_removal_notifier&  rrc_du_notifier_,
                     cu_cp_e1ap_ue_removal_notifier& e1ap_notifier_,
                     cu_cp_f1ap_ue_removal_notifier& f1ap_notifier_,
                     cu_cp_ngap_control_notifier&    ngap_notifier_,
                     ue_manager&                     ue_mng_,
                     ue_task_scheduler&              task_scheduler_,
                     srslog::basic_logger&           logger_);

  void operator()(coro_context<async_task<void>>& ctx);

  static const char* name() { return "UE Removal Routine"; }

private:
  const ue_index_t                ue_index;
  cu_cp_rrc_ue_removal_notifier&  rrc_du_notifier; // to trigger removal of the UE at the RRC
  cu_cp_e1ap_ue_removal_notifier& e1ap_notifier;   // to trigger removal of the UE at the E1AP
  cu_cp_f1ap_ue_removal_notifier& f1ap_notifier;   // to trigger removal of the UE at the F1AP
  cu_cp_ngap_control_notifier&    ngap_notifier;   // to trigger removal of the UE at the NGAP
  ue_manager&                     ue_mng;          // to remove UE context from DU processor
  ue_task_scheduler&              task_scheduler;  // to remove pending UE tasks
  srslog::basic_logger&           logger;
};

} // namespace srs_cu_cp
} // namespace srsran
