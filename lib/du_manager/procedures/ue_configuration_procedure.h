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

#include "../du_ue/du_ue_manager_repository.h"
#include "procedure_logger.h"
#include "srsran/du_manager/du_manager_params.h"

namespace srsran {
namespace srs_du {

class ue_configuration_procedure
{
public:
  ue_configuration_procedure(const f1ap_ue_context_update_request& request_,
                             du_ue_manager_repository&             ue_mng_,
                             const du_manager_params&              du_params_);

  void operator()(coro_context<async_task<f1ap_ue_context_update_response>>& ctx);

  const char* name() const { return "UE Configuration"; }

private:
  /// \brief Update DU UE bearers. This stage includes the creation/modification/removal of SRBs/DRBs, creation of RLC
  /// and F1-U bearers.
  void update_ue_context();
  void clear_old_ue_context();

  /// \brief Update MAC MUX and DEMUX tables of the respective UE, given the newly added/modified/removed bearers.
  async_task<mac_ue_reconfiguration_response> update_mac_mux_and_demux();

  f1ap_ue_context_update_response make_ue_config_response();
  f1ap_ue_context_update_response make_ue_config_failure();

  const f1ap_ue_context_update_request request;
  du_ue_manager_repository&            ue_mng;
  const du_manager_params&             du_params;

  srslog::basic_logger& logger = srslog::fetch_basic_logger("DU-MNG");
  du_ue*                ue     = nullptr;
  ue_procedure_logger   proc_logger;

  cell_group_config prev_cell_group;

  std::vector<std::unique_ptr<du_ue_drb>> drbs_to_rem;
};

} // namespace srs_du
} // namespace srsran
