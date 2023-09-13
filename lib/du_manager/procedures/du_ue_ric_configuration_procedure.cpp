/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "du_ue_ric_configuration_procedure.h"
#include "srsran/support/async/execute_on.h"

using namespace srsran;
using namespace srs_du;

du_ue_ric_configuration_procedure::du_ue_ric_configuration_procedure(const ric_control_config& request_,
                                                                     du_ue_manager_repository& ue_mng_,
                                                                     const du_manager_params&  du_params_) :
  request(request_), ue_mng(ue_mng_), du_params(du_params_)
{
}

void du_ue_ric_configuration_procedure::operator()(coro_context<async_task<ric_control_config>>& ctx)
{
  CORO_BEGIN(ctx);

  // Change execution context to DU manager.
  execute_on(du_params.services.du_mng_exec);

  // Run config task inside the UE task loop and await for its completion.
  CORO_AWAIT(dispatch_ue_config_task());

  // TODO: Potentially change back to caller execution context.

  CORO_RETURN(ue_config_completed.get());
}

manual_event<ric_control_config>& du_ue_ric_configuration_procedure::dispatch_ue_config_task()
{
  // Find UE context based on F1AP UE ID.
  ue = ue_mng.find_f1ap_ue_id(static_cast<gnb_du_ue_f1ap_id_t>(request.ue_id));
  if (ue == nullptr) {
    ric_control_config fail{};
    ue_config_completed.set(fail);
    return ue_config_completed;
  }

  // Dispatch UE configuration to UE task loop inside the UE manager.
  ue_mng.schedule_async_task(ue->ue_index, launch_async([this](coro_context<async_task<void>>& ctx) {
                               CORO_BEGIN(ctx);

                               // Await for UE configuration completion.
                               CORO_AWAIT_VALUE(const mac_ue_reconfiguration_response result, handle_mac_config());

                               // Signal completion of UE configuration to external coroutine.
                               ue_config_completed.set(result.result ? request : ric_control_config{});

                               CORO_RETURN();
                             }));

  return ue_config_completed;
}

async_task<mac_ue_reconfiguration_response> du_ue_ric_configuration_procedure::handle_mac_config()
{
  mac_ue_reconfiguration_request mac_request;

  mac_request.ue_index    = ue->ue_index;
  mac_request.crnti       = ue->rnti;
  mac_request.pcell_index = to_du_cell_index(0);

  // Configure UE resource allocation parameters.
  mac_request.sched_cfg.res_alloc_cfg.emplace();
  auto& res_alloc_cfg = mac_request.sched_cfg.res_alloc_cfg.value();

  res_alloc_cfg.pdsch_grant_size_limits = {request.min_prb_alloc.has_value() ? request.min_prb_alloc.value() : 0,
                                           request.max_prb_alloc.has_value() ? request.max_prb_alloc.value()
                                                                             : MAX_NOF_PRBS};
  res_alloc_cfg.max_pdsch_harq_retxs = request.num_harq_retransmissions.has_value()
                                           ? request.num_harq_retransmissions.value()
                                           : du_params.mac.sched_cfg.ue.max_nof_harq_retxs;
  res_alloc_cfg.max_pusch_harq_retxs = res_alloc_cfg.max_pdsch_harq_retxs;

  return du_params.mac.ue_cfg.handle_ue_reconfiguration_request(mac_request);
}
