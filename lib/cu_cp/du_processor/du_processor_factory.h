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

#include "../ue_manager/ue_manager_impl.h"
#include "du_processor.h"
#include "du_processor_config.h"
#include "srsran/f1ap/common/f1ap_common.h"
#include "srsran/rrc/rrc_ue.h"
#include "srsran/support/executors/task_executor.h"
#include <memory>

namespace srsran {
namespace srs_cu_cp {

class common_task_scheduler;

/// Creates an instance of an DU processor interface
std::unique_ptr<du_processor> create_du_processor(du_processor_config_t               du_processor_config_,
                                                  du_processor_cu_cp_notifier&        cu_cp_notifier_,
                                                  f1ap_message_notifier&              f1ap_pdu_notifier_,
                                                  rrc_ue_nas_notifier&                rrc_ue_nas_pdu_notifier_,
                                                  rrc_ue_control_notifier&            rrc_ue_ngap_ctrl_notifier_,
                                                  rrc_du_measurement_config_notifier& rrc_du_cu_cp_notifier,
                                                  common_task_scheduler&              common_task_sched_,
                                                  ue_manager&                         ue_mng_);

} // namespace srs_cu_cp
} // namespace srsran
