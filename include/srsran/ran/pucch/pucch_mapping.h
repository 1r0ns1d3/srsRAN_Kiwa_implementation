/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/phy/constants.h"

#pragma once

namespace srsran {

/// \brief Configuration of group and sequence hopping as described in TS38.331 PUCCH-ConfigCommon IE.
enum class pucch_group_hopping {
  /// Implies neither group or sequence hopping is enabled.
  NEITHER,
  /// Enables group hopping and disables sequence hopping.
  ENABLE,
  /// Disables group hopping and enables sequence hopping.
  DISABLE
};

/// \brief PUCCH Formats as described in TS38.213 Section 9.2.
enum class pucch_format : uint8_t { FORMAT_0, FORMAT_1, FORMAT_2, FORMAT_3, FORMAT_4, NOF_FORMATS };

inline uint8_t pucch_format_to_uint(pucch_format format)
{
  return static_cast<uint8_t>(format);
}

/// Defines whether the PUCCH within the current slot belongs to a PUCCH repetition. For more details, refer to
/// TS38.213, Section 9.2.6.
enum class pucch_repetition_tx_slot { no_multi_slot, starts, continues, ends };

/// \brief Defines a couple of PUCCH resource IDs, the cell's and UE's resource PUCCH resource ID, respectively.
struct pucch_res_id_t {
  /// This is the PUCCH cell resource ID and is used by the DU and by the scheduler to identify the PUCCH resource.
  unsigned cell_res_id;
  /// Corresponds to \c pucch-ResourceId, as part of \c PUCCH-Resource, in \c PUCCH-Config, TS 38.331.
  /// Used by the DU only to populate the ASN1 message, while it's not used by the scheduler.
  unsigned ue_res_id;

  bool operator==(const pucch_res_id_t& rhs) const
  {
    return cell_res_id == rhs.cell_res_id && ue_res_id == rhs.ue_res_id;
  }
  bool operator!=(const pucch_res_id_t& rhs) const { return !(rhs == *this); }
};

} // namespace srsran
