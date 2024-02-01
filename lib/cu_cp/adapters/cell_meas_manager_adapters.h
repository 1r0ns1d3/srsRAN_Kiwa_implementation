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

#include "../mobility_manager/mobility_manager.h"
#include "srsran/cu_cp/cell_meas_manager.h"

namespace srsran {
namespace srs_cu_cp {

/// Adapter between cell measurement and mobility manager to trigger handover.
class cell_meas_mobility_manager_adapter : public cell_meas_mobility_manager_notifier
{
public:
  cell_meas_mobility_manager_adapter() = default;

  void connect_mobility_manager(mobility_manager_measurement_handler& handler_) { handler = &handler_; }

  void on_neighbor_better_than_spcell(ue_index_t ue_index, pci_t neighbor_pci) override
  {
    srsran_assert(handler != nullptr, "Mobility manager handler must not be nullptr");
    handler->handle_neighbor_better_than_spcell(ue_index, neighbor_pci);
  }

private:
  mobility_manager_measurement_handler* handler = nullptr;
};

} // namespace srs_cu_cp
} // namespace srsran
