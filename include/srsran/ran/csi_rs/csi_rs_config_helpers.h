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

#include "srsran/ran/csi_rs/csi_rs_types.h"
#include "srsran/ran/csi_rs/frequency_allocation_type.h"

namespace srsran {

namespace csi_rs {

/// \brief Returns the row index corresponding to Table 7.4.1.5.3-1, TS 38.211 given the CSI-RS configuration.
/// \param[in] nof_ports Number of ports, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] density Density, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] cdm_type CDM-type, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] fd_alloc Freq. Domain Allocation, as per \c frequencyDomainAllocation in \c CSI-RS-ResourceMapping,
///            TS 38.331.
/// \return The row index of Table 7.4.1.5.3-1, TS 38.211 corresponding to the inputs. If the given input configuration
///         does not match any of the rows in the table, the function triggers an assert and returns an invalid value
///         (i.e., 0).
uint8_t get_csi_rs_resource_mapping_row_number(uint8_t                          nof_ports,
                                               csi_rs_freq_density_type         density,
                                               csi_rs_cdm_type                  cdm_type,
                                               const freq_allocation_mask_type& fd_alloc);

} // namespace csi_rs

} // namespace srsran
