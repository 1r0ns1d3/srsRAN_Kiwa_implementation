/*
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "scheduler_policy.h"
#include "srsran/scheduler/config/scheduler_expert_config.h"

namespace srsran {

class scheduler_time_rr : public scheduler_policy
{
public:
  scheduler_time_rr(const scheduler_ue_expert_config& expert_cfg_, du_cell_index_t cell_index);

  void add_ue(du_ue_index_t ue_index) override {}

  void rem_ue(du_ue_index_t ue_index) override {}

  void compute_ue_dl_priorities(slot_point               pdcch_slot,
                                slot_point               pdsch_slot,
                                span<ue_newtx_candidate> ue_candidates) override;

  void compute_ue_ul_priorities(slot_point               pdcch_slot,
                                slot_point               pusch_slot,
                                span<ue_newtx_candidate> ue_candidates) override;

  void save_dl_newtx_grants(span<const dl_msg_alloc> dl_grants) override;

  void save_ul_newtx_grants(span<const ul_sched_info> ul_grants) override;

private:
  const scheduler_ue_expert_config expert_cfg;
  const du_cell_index_t            cell_index;

  du_ue_index_t next_dl_ue_index = MAX_NOF_DU_UES, next_ul_ue_index = MAX_NOF_DU_UES;
};

} // namespace srsran
