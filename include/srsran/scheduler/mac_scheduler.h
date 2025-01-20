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

#include "srsran/scheduler/scheduler_configurator.h"
#include "srsran/scheduler/scheduler_dl_buffer_state_indication_handler.h"
#include "srsran/scheduler/scheduler_feedback_handler.h"
#include "srsran/scheduler/scheduler_paging_handler.h"
#include "srsran/scheduler/scheduler_slot_handler.h"
#include "srsran/scheduler/scheduler_sys_info_handler.h"

namespace srsran {

class mac_scheduler : public scheduler_configurator,
                      public scheduler_ue_configurator,
                      public scheduler_feedback_handler,
                      public scheduler_slot_handler,
                      public scheduler_dl_buffer_state_indication_handler,
                      public scheduler_paging_handler,
                      public scheduler_sys_info_handler
{
public:
  virtual ~mac_scheduler() = default;
};

} // namespace srsran
