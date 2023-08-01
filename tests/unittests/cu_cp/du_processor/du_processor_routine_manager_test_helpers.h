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

#include "../du_processor_test_messages.h"
#include "../test_helpers.h"
#include "lib/cu_cp/routine_managers/du_processor_routine_manager.h"
#include "lib/cu_cp/ue_manager_impl.h"
#include "lib/cu_cp/up_resource_manager/up_resource_manager_impl.h"
#include "tests/unittests/rrc/rrc_ue_test_messages.h"
#include "srsran/support/test_utils.h"
#include <gtest/gtest.h>

namespace srsran {
namespace srs_cu_cp {

/// Fixture class for DU processor creation
class du_processor_routine_manager_test : public ::testing::Test
{
protected:
  du_processor_routine_manager_test();
  ~du_processor_routine_manager_test() override;

  void init_security_config();

  srslog::basic_logger& test_logger  = srslog::fetch_basic_logger("TEST");
  srslog::basic_logger& cu_cp_logger = srslog::fetch_basic_logger("CU-CP");

  ue_configuration                ue_config{std::chrono::seconds{10}};
  srsran::security::sec_as_config security_cfg;
  up_resource_manager_cfg         drb_cfg;

  dummy_du_processor_e1ap_control_notifier              e1ap_ctrl_notifier;
  dummy_du_processor_f1ap_ue_context_notifier           f1ap_ue_ctxt_notifier;
  dummy_du_processor_rrc_du_ue_notifier                 rrc_du_notifier;
  dummy_du_processor_ngap_control_notifier              ngap_control_notifier;
  std::unique_ptr<dummy_du_processor_ue_task_scheduler> ue_task_sched;
  ue_manager                                            ue_mng{ue_config, drb_cfg};
  manual_task_worker                                    ctrl_worker{128};
  timer_manager                                         timers;
  dummy_du_processor_rrc_ue_control_message_notifier    rrc_ue_ctrl_notifier;
  std::unique_ptr<up_resource_manager_impl>             rrc_ue_up_resource_manager;
  std::unique_ptr<du_processor_routine_manager>         routine_mng;
};

} // namespace srs_cu_cp
} // namespace srsran
