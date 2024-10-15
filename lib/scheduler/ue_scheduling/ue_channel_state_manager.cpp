/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ue_channel_state_manager.h"
#include "srsran/srslog/srslog.h"
#include <algorithm>

using namespace srsran;

ue_channel_state_manager::ue_channel_state_manager(const scheduler_ue_expert_config& expert_cfg,
                                                   unsigned                          nof_dl_ports_) :
  nof_dl_ports(nof_dl_ports_),
  pusch_snr_db(expert_cfg.initial_ul_sinr),
  wideband_cqi(expert_cfg.initial_cqi),
  logger(srslog::fetch_basic_logger("SCHED"))
{
  // Set initial precoding value when no CSI has yet been received.
  if (nof_dl_ports == 2) {
    recommended_prg_info.resize(2, pdsch_precoding_info::prg_info{pdsch_precoding_info::prg_info::two_antenna_port{0}});
  } else if (nof_dl_ports == 4) {
    recommended_prg_info.resize(
        4,
        pdsch_precoding_info::prg_info{
            pdsch_precoding_info::prg_info::typeI_single_panel_4ports_mode1{0, std::nullopt, 0}});
  }

  // Initialize PUSCH PRB grid.
  std::fill(pusch_nof_prbs_grid.begin(), pusch_nof_prbs_grid.end(), pusch_prbs_entry{slot_point{}, 0});
}

bool ue_channel_state_manager::handle_csi_report(const csi_report_data& csi_report)
{
  latest_csi_report = csi_report;

  // Set wideband CQI.
  if (csi_report.first_tb_wideband_cqi.has_value()) {
    wideband_cqi = csi_report.first_tb_wideband_cqi.value();
  }

  // Update recommended number of layers based on RI.
  if (csi_report.ri.has_value()) {
    if (csi_report.ri.value() > nof_dl_ports) {
      return false;
    }
    recommended_dl_layers = csi_report.ri.value().to_uint();
  }

  if (csi_report.pmi.has_value()) {
    if (nof_dl_ports <= 1) {
      return false;
    }
    const unsigned table_idx        = nof_layers_to_index(recommended_dl_layers);
    recommended_prg_info[table_idx] = csi_report.pmi.value();
  }

  return true;
}

void ue_channel_state_manager::update_srs_channel_matrix(const srsran::srs_channel_matrix& channel_matrix,
                                                         tx_scheme_codebook_subset         cb_subset)
{
  float norm                  = channel_matrix.frobenius_norm();
  last_pusch_tpmi_select_info = get_tpmi_select_info(channel_matrix, norm * norm, cb_subset);
}

SRSRAN_WEAK_SYMB unsigned ue_channel_state_manager::get_nof_ul_layers() const
{
  return 1;
}

SRSRAN_WEAK_SYMB void ue_channel_state_manager::handle_phr(const cell_ph_report& phr)
{
  latest_phr.emplace(ue_phr_report{phr, std::nullopt});
}

SRSRAN_WEAK_SYMB unsigned ue_channel_state_manager::get_recommended_pusch_tpmi(unsigned nof_layers) const
{
  if (last_pusch_tpmi_select_info.has_value() &&
      (nof_layers <= last_pusch_tpmi_select_info.value().get_max_nof_layers())) {
    return last_pusch_tpmi_select_info.value().get_tpmi_select(nof_layers).tpmi;
  }
  return 0;
}

void ue_channel_state_manager::save_pusch_nof_prbs(slot_point slot_rx, unsigned nof_prbs)
{
  pusch_nof_prbs_grid[slot_rx.to_uint() % pusch_nof_prbs_grid.size()] = {slot_rx, nof_prbs};
}

SRSRAN_WEAK_SYMB unsigned ue_channel_state_manager::adapt_pusch_prbs_to_phr(unsigned nof_prbs) const
{
  // Dummy function. This feature is only available in the SRSRAN 5G Enterprise version.
  return nof_prbs;
}
