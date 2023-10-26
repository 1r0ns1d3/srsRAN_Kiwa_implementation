/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "../pucch_scheduling/pucch_allocator.h"

#pragma once

namespace srsran {

/// Contains the results of the UCI allocation.
struct uci_allocation {
  /// Delay in slots of the UE's PUCCH HARQ-ACK report with respect to the PDSCH.
  unsigned k1;
  /// Index of the HARQ-bit in the PUCCH/PUSCH HARQ report.
  uint8_t harq_bit_idx{0};
  /// If UCI is allocated on the PUCCH, contains the PUCCH resource indicator; else, this is to be ignored.
  optional<unsigned> pucch_res_indicator;
};

/// \brief UCI allocator interface.
/// Depending on whether there is an existing PUSCH grant, it allocates the UCI either on the PUSCH or PUCCH.
class uci_allocator
{
public:
  virtual ~uci_allocator() = default;

  /// \brief Signal a new slot indication to be setup in the cell grid.
  virtual void slot_indication(slot_point sl_tx) = 0;

  /// Allocate the common PUCCH resource for HARQ-ACK for a given UE.
  /// \param[out,in] res_alloc struct with scheduling results.
  /// \param[in] crnti RNTI of the UE.
  /// \param[in] ue_cell_cfg user configuration. For the fallback mode case, this configuration is used to determine
  /// whether the slot coincides with a CSI report opportunity; in which case, the allocation of the UCI on common PUCCH
  /// resources will be skipped.
  /// \param[in] k0 k0 value, or delay (in slots) of PDSCH slot vs the corresponding PDCCH slot.
  /// \param[in] k1_list List of k1 candidates configured for UE.
  /// \param[in] fallback_dci_info pointer to the information with DL DCI, used for scheduling the UCI on common PUCCH
  /// resources. If this is \c nullptr, it triggers the UCI scheduling using common PUCCH resources; else, if it is
  /// \c nullptr, UCI will be scheduled either on dedicated PUCCH resources or on PUSCH.
  virtual optional<uci_allocation> alloc_uci_harq_ue(cell_resource_allocator&     res_alloc,
                                                     rnti_t                       crnti,
                                                     const ue_cell_configuration& ue_cell_cfg,
                                                     unsigned                     k0,
                                                     span<const uint8_t>          k1_list,
                                                     const pdcch_dl_information*  fallback_dci_info = nullptr) = 0;

  /// Multiplexes the UCI on PUSCH, by removing the UCI on the PUCCH (if present) and adding it to the PUSCH.
  /// \param[out,in] pusch_grant struct with PUSCH PDU where UCI need to be allocated.
  /// \param[out,in] slot_alloc struct with scheduling results.
  /// \param[in] ue_cell_cfg user configuration.
  /// \param[in] crnti C-RNTI of the UE.
  virtual void multiplex_uci_on_pusch(ul_sched_info&                pusch_grant,
                                      cell_slot_resource_allocator& slot_alloc,
                                      const ue_cell_configuration&  ue_cell_cfg,
                                      rnti_t                        crnti) = 0;

  /// Allocates the SR opportunities for a given UE.
  /// \param[out,in] slot_alloc struct with scheduling results.
  /// \param[in] crnti C-RNTI of the UE.
  /// \param[in] ue_cell_cfg user configuration.
  /// \param[in] is_fallback_mode Indicates whether the UE is in fallback mode.
  virtual void uci_allocate_sr_opportunity(cell_slot_resource_allocator& slot_alloc,
                                           rnti_t                        crnti,
                                           const ue_cell_configuration&  ue_cell_cfg) = 0;

  /// Allocates the CSI opportunities for a given UE.
  /// \param[out,in] slot_alloc struct with scheduling results.
  /// \param[in] crnti C-RNTI of the UE.
  /// \param[in] ue_cell_cfg user configuration.
  /// \param[in] is_fallback_mode Indicates whether the UE is in fallback mode.
  virtual void uci_allocate_csi_opportunity(cell_slot_resource_allocator& slot_alloc,
                                            rnti_t                        crnti,
                                            const ue_cell_configuration&  ue_cell_cfg) = 0;

  /// Get the number of PDSCHs currently scheduled for a given UE UCI.
  /// \param[in] slot_alloc struct with scheduling results.
  /// \param[in] crnti C-RNTI of the UE.
  /// \return Returns number of PDSCHs scheduled if UCI allocation if found, 0 otherwise.
  virtual uint8_t get_scheduled_pdsch_counter_in_ue_uci(cell_slot_resource_allocator& slot_alloc, rnti_t crnti) = 0;
};

} // namespace srsran
