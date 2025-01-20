/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/ran/sch/sch_mcs.h"
#include <optional>

namespace srsran {

struct pusch_config_params;
struct pdsch_config_params;
class ue_cell_configuration;

/// Container for MCS and TBS results.
struct sch_mcs_tbs {
  /// MCS to use for the UE's PDSCH and PUSCH.
  sch_mcs_index mcs;
  /// TBS to be allocated on the UE's PDSCH and PUSCH.
  unsigned tbs;
};

/// \brief Computes the PDSCH MCS and TBS such that the effective code rate does not exceed 0.95.
///
/// \param[in] pdsch_params PDSCH parameters needed to compute the MCS and TBS.
/// \param[in] max_mcs Initial value to be applied for the MCS; the final MCS might be lowered if the effective
/// code rate is above 0.95.
/// \param[in] nof_prbs Maximum number of PRBs available for the PUSCH transmission.
/// \param[in] contains_dc Set to true if the transmission overlaps with the position of the DC.
/// \return The MCS and TBS, if for these values the effective code rate does not exceed 0.95; else, it returns an empty
/// optional object.
std::optional<sch_mcs_tbs>
compute_dl_mcs_tbs(const pdsch_config_params& pdsch_params, sch_mcs_index max_mcs, unsigned nof_prbs, bool contains_dc);

/// \brief Computes the PUSCH MCS and TBS such that the effective code rate does not exceed 0.95.
///
/// \param[in] pusch_params PUSCH parameters needed to compute the MCS and TBS.
/// \param[in] ue_cell_cfg UE cell configuration.
/// \param[in] max_mcs Initial value to be applied for the MCS; the final MCS might be lowered if the effective
/// code rate is above 0.95.
/// \param[in] nof_prbs Maximum number of PRBs available for the PUSCH transmission.
/// \param[in] contains_dc Set to true if the transmission overlaps with the position of the DC.
/// \return The MCS and TBS, if for these values the effective code rate does not exceed 0.95; else, it returns an empty
/// optional object.
std::optional<sch_mcs_tbs> compute_ul_mcs_tbs(const pusch_config_params&   pusch_params,
                                              const ue_cell_configuration* ue_cell_cfg,
                                              sch_mcs_index                max_mcs,
                                              unsigned                     nof_prbs,
                                              bool                         contains_dc);

} // namespace srsran
