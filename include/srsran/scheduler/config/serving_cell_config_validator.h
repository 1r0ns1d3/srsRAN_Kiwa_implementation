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

#include "serving_cell_config.h"
#include "srsran/ran/tdd/tdd_ul_dl_config.h"
#include "srsran/support/config/validator_result.h"

namespace srsran {
namespace config_validators {

/// \brief Validates PDCCH Config in \c sched_ue_creation_request_message used to create a UE.
/// \param[in] ue_cell_cfg UE serving cell configuration to be validated.
/// \param[in] dl_cfg_common Cell DL common configuration.
/// \return In case an invalid parameter is detected, returns a string containing an error message.
validator_result validate_pdcch_cfg(const serving_cell_config& ue_cell_cfg, const dl_config_common& dl_cfg_common);

/// \brief Validates PDSCH Config in \c sched_ue_creation_request_message used to create a UE.
/// \param[in] ue_cell_cfg UE serving cell configuration to be validated.
/// \return In case an invalid parameter is detected, returns a string containing an error message.
validator_result validate_pdsch_cfg(const serving_cell_config& ue_cell_cfg);

/// \brief Validates PUCCH Config in \c sched_ue_creation_request_message used to create a UE.
/// \param[in] ue_cell_cfg UE serving cell configuration to be validated.
/// \param[in] nof_dl_antennas Number of antennas used for DL tx.
/// \return In case an invalid parameter is detected, returns a string containing an error message.
error_type<std::string> validate_pucch_cfg(const serving_cell_config& ue_cell_cfg, unsigned nof_dl_antennas);

/// \brief Validates CSI-MeasConfig in \c serving_cell_config passed to a UE.
/// \param[in] ue_cell_cfg UE serving cell configuration to be validated.
/// \param[in] tdd_cfg_common TDD configuration, if any.
/// \return In case an invalid parameter is detected, returns a string containing an error message.
validator_result validate_csi_meas_cfg(const serving_cell_config&               ue_cell_cfg,
                                       const optional<tdd_ul_dl_config_common>& tdd_cfg_common);

} // namespace config_validators
} // namespace srsran