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

#include "../task_schedulers/cu_up_task_scheduler.h"
#include "srsran/cu_cp/cu_cp.h"
#include "srsran/cu_cp/cu_up_processor.h"

namespace srsran {
namespace srs_cu_cp {

/// Adapter between CU-UP Processor and CU-CP, to handle CU-UP specific procedure outcomes (e.g. CU-CP E1 Setup Failure)
class cu_up_processor_cu_cp_adapter : public cu_up_processor_cu_up_management_notifier
{
public:
  void connect_cu_cp(cu_cp_cu_up_handler& cu_cp_handler_) { cu_cp_handler = &cu_cp_handler_; }

  void on_new_cu_up_connection() override
  {
    srsran_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    cu_cp_handler->handle_new_cu_up_connection();
  }

  void on_cu_up_remove_request_received(const cu_up_index_t cu_up_index) override
  {
    srsran_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    cu_cp_handler->handle_cu_up_remove_request(cu_up_index);
  }

private:
  cu_cp_cu_up_handler* cu_cp_handler = nullptr;
};

/// Adapter between CU-UP Processor and E1AP, to initialize connection procedures
class cu_up_processor_e1ap_adapter : public cu_up_processor_e1ap_control_notifier
{
public:
  void connect_e1ap(e1ap_connection_manager& e1ap_conn_mng_) { e1ap_conn_mng = &e1ap_conn_mng_; }

  async_task<cu_cp_e1_setup_response> on_cu_cp_e1_setup_request(const cu_cp_e1_setup_request& request) override
  {
    srsran_assert(e1ap_conn_mng != nullptr, "E1AP handler must not be nullptr");
    return e1ap_conn_mng->handle_cu_cp_e1_setup_request(request);
  }

private:
  e1ap_connection_manager* e1ap_conn_mng = nullptr;
};

} // namespace srs_cu_cp
} // namespace srsran
