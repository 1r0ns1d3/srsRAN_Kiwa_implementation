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

#include "srsran/ran/cyclic_prefix.h"
#include "srsran/scheduler/config/bwp_configuration.h"
#include "srsran/scheduler/config/dmrs.h"
#include "srsran/scheduler/config/serving_cell_config.h"

namespace srsran {

/// \brief Collects the PUSCH default time-domain allocation parameters.
///
/// The parameters are provided by TS38.214 Tables 5.1.2.1.1-2, 5.1.2.1.1-3, 5.1.2.1.1-4 and 5.1.2.1.1-5.
///
/// A configuration is invalid if the duration is not zero.
struct pusch_default_time_allocation_config {
  /// PUSCH mapping.
  sch_mapping_type mapping_type;
  /// PDCCH to PUSCH delay in slots, parameter \f$K_0\f$. The range is {0, 1}.
  uint8_t k2;
  /// Start symbol index within the slot, parameter \f$S\f$. The range is {0, ..., 10}.
  uint8_t start_symbol;
  /// Transmission duration in symbols, parameter \f$L\f$. The range is {2, ..., 12}
  uint8_t duration;
};

/// Reserved default PUSCH time-domain allocation. It indicates the configuration is invalid.
static constexpr pusch_default_time_allocation_config PUSCH_DEFAULT_TIME_ALLOCATION_RESERVED = {};

/// \brief Determines the default PUSCH time-domain resource allocation A.
///
/// The time domain allocation configuration is described in TS38.214 Table 5.1.2.1.1-2 for normal cyclic prefix and
/// TS38.214 Table 5.1.2.1.1-3 for extended cyclic prefix.
///
/// \param[in] cp        Cyclic prefix.
/// \param[in] row_index Row index.
/// \param[in] scs       PUSCH subcarrier spacing.
/// \return A valid PUSCH time-domain allocation configuration is the provided parameters are valid. Otherwise,
/// PUSCH_DEFAULT_TIME_ALLOCATION_RESERVED.
pusch_default_time_allocation_config
pusch_default_time_allocation_default_A_get(cyclic_prefix cp, unsigned row_index, subcarrier_spacing scs);

/// \brief Determines the table of default PUSCH time-domain resource allocation A.
///
/// \param[in] cp  Cyclic prefix.
/// \param[in] scs PUSCH subcarrier spacing.
/// \return A list of valid PUSCH time-domain allocation configurations to choose from.
span<const pusch_time_domain_resource_allocation>
pusch_default_time_allocations_default_A_table(cyclic_prefix cp, subcarrier_spacing scs);

/// \brief Determines the time domain resource allocation table to be used for PUSCH as per TS 38.214, clause 6.1.2.1.1.
///
/// \param ss_cfg Search Space configuration.
/// \param active_bwp_ul_common Active BWP UL common configuration.
/// \param active_bwp_ul_ded Active BWP UL UE-dedicated configuration.
/// \return A list of valid PUSCH time-domain allocation configurations to choose from.
span<const pusch_time_domain_resource_allocation>
get_c_rnti_pusch_time_domain_list(const search_space_configuration& ss_cfg,
                                  const bwp_uplink_common&          active_bwp_ul_common,
                                  const bwp_uplink_dedicated*       active_bwp_ul_ded);

} // namespace srsran
