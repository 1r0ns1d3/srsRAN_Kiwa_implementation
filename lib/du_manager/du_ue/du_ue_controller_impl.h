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

#include "du_ue_manager_repository.h"

namespace srsran {
namespace srs_du {

class du_ue_controller_impl final : public du_ue
{
public:
  du_ue_controller_impl(const du_ue_context&         context_,
                        du_ue_manager_repository&    ue_db_,
                        const du_manager_params&     cfg_,
                        ue_ran_resource_configurator ue_ran_res_);
  ~du_ue_controller_impl() override;

  async_task<void> disconnect_notifiers() override;

  void schedule_async_task(async_task<void> task) override { ue_db.schedule_async_task(ue_index, std::move(task)); }

  void handle_rlf_detection(rlf_cause cause) override;

  void handle_crnti_ce_detection() override;

  void handle_scheduling_activation(bool active) override {}

  mac_ue_radio_link_notifier&          get_mac_rlf_notifier() override { return *mac_rlf_notifier; }
  rlc_tx_upper_layer_control_notifier& get_rlc_rlf_notifier() override { return *rlc_rlf_notifier; }

private:
  class rlf_state_machine;

  du_ue_manager_repository& ue_db;

  const du_manager_params& cfg;

  std::unique_ptr<rlf_state_machine>                   rlf_handler;
  std::unique_ptr<mac_ue_radio_link_notifier>          mac_rlf_notifier;
  std::unique_ptr<rlc_tx_upper_layer_control_notifier> rlc_rlf_notifier;
};

} // namespace srs_du
} // namespace srsran