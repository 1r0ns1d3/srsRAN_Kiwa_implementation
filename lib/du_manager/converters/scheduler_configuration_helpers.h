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

#include "srsran/ran/plmn_identity.h"
#include "srsran/scheduler/scheduler_configurator.h"

namespace srsran {

struct du_cell_config;

namespace srs_du {

class du_ue;

/// Derives Scheduler Cell Configuration from DU Cell Configuration.
sched_cell_configuration_request_message make_sched_cell_config_req(du_cell_index_t          cell_index,
                                                                    const du_cell_config&    du_cfg,
                                                                    span<const units::bytes> si_payload_sizes);

// Create scheduler UE Configuration Request based on DU UE configuration context.
sched_ue_config_request create_scheduler_ue_config_request(const du_ue& u, const plmn_identity& ue_plmn_id);

} // namespace srs_du
} // namespace srsran