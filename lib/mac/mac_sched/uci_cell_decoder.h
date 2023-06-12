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

#include "../mac_dl/rlf_detector.h"
#include "rnti_manager.h"
#include "srsran/mac/mac_cell_control_information_handler.h"
#include "srsran/ran/csi_report/csi_report_configuration.h"
#include "srsran/scheduler/scheduler_configurator.h"
#include "srsran/scheduler/scheduler_feedback_handler.h"
#include "srsran/scheduler/scheduler_slot_handler.h"

namespace srsran {

class uci_cell_decoder
{
  static constexpr size_t MAX_GRID_SIZE = 80;

public:
  uci_cell_decoder(const sched_cell_configuration_request_message& cell_cfg,
                   const du_rnti_table&                            rnti_table,
                   rlf_detector&                                   rlf_dt);

  /// \brief Store information relative to expected UCIs to be decoded.
  void store_uci(slot_point uci_sl, span<const pucch_info> scheduled_pucchs);

  /// \brief Decode received MAC UCI indication and convert it to scheduler UCI indication.
  uci_indication decode_uci(const mac_uci_indication_message& msg);

private:
  struct uci_context {
    rnti_t                   rnti = INVALID_RNTI;
    csi_report_configuration csi_rep_cfg;
  };

  static size_t to_grid_index(slot_point slot) { return slot.to_uint() % MAX_GRID_SIZE; }

  const du_rnti_table&  rnti_table;
  du_cell_index_t       cell_index;
  rlf_detector&         rlf_handler;
  srslog::basic_logger& logger;

  std::array<static_vector<uci_context, MAX_PUCCH_PDUS_PER_SLOT>, MAX_GRID_SIZE> expected_uci_report_grid;
};

} // namespace srsran