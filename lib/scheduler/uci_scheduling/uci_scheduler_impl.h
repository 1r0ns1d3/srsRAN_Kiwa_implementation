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

#include "../cell/resource_grid_util.h"
#include "../ue_scheduling/ue_repository.h"
#include "uci_scheduler.h"

namespace srsran {

class cell_configuration;
class uci_allocator;
struct cell_resource_allocator;
struct cell_slot_resource_allocator;

class uci_scheduler_impl final : public uci_scheduler
{
public:
  explicit uci_scheduler_impl(const cell_configuration& cell_cfg_, uci_allocator& uci_alloc_, ue_repository& ues_);

  ~uci_scheduler_impl() override;

  void run_slot(cell_resource_allocator& res_alloc, slot_point sl_tx) override;

private:
  // Helper that schedules the SR and CSI for a given user at a given slot.
  void schedule_uci(cell_slot_resource_allocator&           slot_alloc,
                    rnti_t                                  crnti,
                    const ue_cell&                          user,
                    optional<std::pair<unsigned, unsigned>> csi_period_and_offset);

  // Size of the ring buffer of \c cell_slot_resource_allocator. This size sets a limit on how far in advance a SR and
  // CSI grants can be allocated. See remark of \c get_allocator_ring_size_ge_min(unsigned minimum_value).
  static const size_t RING_ALLOCATOR_SIZE = get_allocator_ring_size_gt_min(
      std::max(SCHEDULER_MAX_K0 + SCHEDULER_MAX_K1, SCHEDULER_MAX_K2 + MAX_MSG3_DELTA + NTN_CELL_SPECIFIC_KOFFSET_MAX));

  // Cell configuration.
  const cell_configuration& cell_cfg;
  // Reference to PUCCH resource allocator object.
  uci_allocator& uci_alloc;
  ue_repository& ues;

  srslog::basic_logger& logger;
};

} // namespace srsran
