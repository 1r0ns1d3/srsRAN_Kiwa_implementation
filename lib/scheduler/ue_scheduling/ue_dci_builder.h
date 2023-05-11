/*
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "harq_process.h"
#include "ue_configuration.h"
#include "srsran/ran/pdcch/search_space.h"
#include "srsran/ran/resource_allocation/resource_allocation_frequency.h"
#include "srsran/scheduler/config/bwp_configuration.h"
#include "srsran/scheduler/scheduler_dci.h"

namespace srsran {

/// Get redundancy version.
inline unsigned get_redundancy_version(unsigned nof_retxs)
{
  static constexpr std::array<unsigned, 4> rv_idx = {0, 2, 3, 1};
  return rv_idx[nof_retxs % rv_idx.size()];
}

/// Builds DCI f1_0 for TC-RNTI, used for instance in Msg4.
void build_dci_f1_0_tc_rnti(dci_dl_info&               dci,
                            const bwp_downlink_common& init_dl_bwp,
                            prb_interval               prbs,
                            unsigned                   time_resource,
                            unsigned                   k1,
                            unsigned                   pucch_res_indicator,
                            sch_mcs_index              mcs_index,
                            const dl_harq_process&     h_dl);

/// Builds DCI f1_0 for C-RNTI.
void build_dci_f1_0_c_rnti(dci_dl_info&                       dci,
                           const bwp_downlink_common&         init_dl_bwp,
                           const bwp_downlink_common&         active_dl_bwp,
                           const bwp_downlink_dedicated*      active_dl_bwp_ded,
                           search_space_configuration::type_t ss_type,
                           prb_interval                       prbs,
                           unsigned                           time_resource,
                           unsigned                           k1,
                           unsigned                           pucch_res_indicator,
                           unsigned                           dai,
                           sch_mcs_index                      mcs_index,
                           const dl_harq_process&             h_dl);

/// Builds DCI f1_1 for C-RNTI.
void build_dci_f1_1_c_rnti(dci_dl_info&                 dci,
                           const ue_cell_configuration& ue_cell_cfg,
                           bool                         is_ue_configured_multiple_serving_cells,
                           bwp_id_t                     active_bwp_id,
                           search_space_id              ss_id,
                           prb_interval                 prbs,
                           unsigned                     time_resource,
                           unsigned                     k1,
                           unsigned                     pucch_res_indicator,
                           unsigned                     dai,
                           sch_mcs_index                tb1_mcs_index,
                           const dl_harq_process&       h_dl);

/// Builds DCI f0_0 for TC-RNTI, used in Msg3 retxs.
void build_dci_f0_0_tc_rnti(dci_ul_info&               dci,
                            const bwp_downlink_common& init_dl_bwp,
                            const bwp_configuration&   ul_bwp,
                            const prb_interval&        prbs,
                            unsigned                   time_resource,
                            sch_mcs_index              mcs_index,
                            const ul_harq_process&     h_ul);

/// Builds DCI f0_0 for C-RNTI.
void build_dci_f0_0_c_rnti(dci_ul_info&                       dci,
                           const bwp_downlink_common&         init_dl_bwp,
                           const bwp_downlink_common&         active_dl_bwp,
                           const bwp_downlink_dedicated*      active_dl_bwp_ded,
                           const bwp_configuration&           init_ul_bwp,
                           const bwp_configuration&           active_ul_bwp,
                           search_space_configuration::type_t ss_type,
                           const prb_interval&                prbs,
                           unsigned                           time_resource,
                           sch_mcs_index                      mcs_index,
                           const ul_harq_process&             h_ul);

/// Builds DCI f0_1 for C-RNTI.
void build_dci_f0_1_c_rnti(dci_ul_info&                 dci,
                           const ue_cell_configuration& ue_cell_cfg,
                           bwp_id_t                     active_bwp_id,
                           search_space_id              ss_id,
                           const prb_interval&          prbs,
                           unsigned                     time_resource,
                           sch_mcs_index                mcs_index,
                           const ul_harq_process&       h_ul);

} // namespace srsran
