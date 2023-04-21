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

#include "srsran/cu_cp/cu_up_processor.h"
#include "srsran/e1ap/cu_cp/e1ap_cu_cp.h"
#include "srsran/srslog/srslog.h"

namespace srsran {
namespace srs_cu_cp {

/// Adapter between E1AP and CU-UP processor
class e1ap_cu_up_processor_adapter : public e1ap_cu_up_processor_notifier
{
public:
  void connect_cu_up_processor(cu_up_processor_e1ap_interface& cu_up_processor_e1ap_)
  {
    cu_up_e1ap_handler = &cu_up_processor_e1ap_;
  }

  void on_cu_up_e1_setup_request_received(const cu_up_e1_setup_request& msg) override
  {
    srsran_assert(cu_up_e1ap_handler != nullptr, "E1AP handler must not be nullptr");
    cu_up_e1ap_handler->handle_cu_up_e1_setup_request(msg);
  }

private:
  cu_up_processor_e1ap_interface* cu_up_e1ap_handler = nullptr;
};

/// Adapter between E1AP and CU-CP
class e1ap_cu_cp_adapter : public e1ap_cu_cp_notifier
{
public:
  void connect_cu_cp(cu_cp_e1ap_handler& cu_cp_handler_) { cu_cp_handler = &cu_cp_handler_; }

  void on_bearer_context_inactivity_notification_received(const cu_cp_inactivity_notification& msg) override
  {
    srsran_assert(cu_cp_handler != nullptr, "E1AP handler must not be nullptr");
    cu_cp_handler->handle_bearer_context_inactivity_notification(msg);
  }

private:
  cu_cp_e1ap_handler* cu_cp_handler = nullptr;
};

} // namespace srs_cu_cp
} // namespace srsran
