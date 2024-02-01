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

#include "../du_processor_test_messages.h"
#include "../test_helpers.h"
#include "du_processor_test_helpers.h"
#include "lib/cu_cp/du_processor/du_processor_factory.h"
#include "lib/cu_cp/du_processor/du_processor_impl_interface.h"
#include "lib/cu_cp/ue_manager/ue_manager_impl.h"
#include "lib/f1ap/common/asn1_helpers.h"
#include "tests/unittests/f1ap/common/test_helpers.h"
#include "tests/unittests/f1ap/cu_cp/f1ap_cu_test_helpers.h"
#include "tests/unittests/rrc/test_helpers.h"
#include "srsran/cu_cp/cu_cp_types.h"
#include "srsran/rrc/rrc.h"
#include "srsran/support/executors/manual_task_worker.h"
#include "srsran/support/test_utils.h"
#include <gtest/gtest.h>

namespace srsran {
namespace srs_cu_cp {

/// Fixture class for DU processor creation
class du_processor_test : public ::testing::Test
{
protected:
  du_processor_test();
  ~du_processor_test() override;

  void attach_ue();

  void receive_rrc_reconfig_complete();

  srslog::basic_logger& test_logger  = srslog::fetch_basic_logger("TEST");
  srslog::basic_logger& cu_cp_logger = srslog::fetch_basic_logger("CU-CP");

  timer_manager                                         timers;
  ue_configuration                                      ue_config;
  up_resource_manager_cfg                               up_config;
  ue_manager                                            ue_mng{ue_config, up_config};
  dummy_cell_meas_manager                               cell_meas_mng;
  dummy_ngap_ue_context_removal_handler                 ngap_ue_removal_handler;
  std::unique_ptr<dummy_du_processor_cu_cp_notifier>    cu_cp_notifier;
  dummy_du_connection_notifier                          du_conn_notifier;
  dummy_f1ap_pdu_notifier                               f1ap_pdu_notifier;
  dummy_f1ap_du_management_notifier                     f1ap_du_mgmt_notifier;
  dummy_du_processor_e1ap_control_notifier              e1ap_ctrl_notifier;
  dummy_du_processor_ngap_control_notifier              ngap_ctrl_notifier;
  dummy_f1ap_ue_removal_notifier                        f1ap_cu_cp_notifier;
  dummy_rrc_ue_ngap_adapter                             rrc_ue_ngap_notifier;
  dummy_rrc_ue_cu_cp_adapter                            rrc_ue_cu_cp_notifier;
  std::unique_ptr<dummy_du_processor_ue_task_scheduler> ue_task_sched;
  manual_task_worker                                    ctrl_worker{128};
  std::unique_ptr<du_processor_impl_interface>          du_processor_obj;

  async_task<cu_cp_ue_context_release_complete>                   t;
  optional<lazy_task_launcher<cu_cp_ue_context_release_complete>> t_launcher;
};

} // namespace srs_cu_cp
} // namespace srsran
