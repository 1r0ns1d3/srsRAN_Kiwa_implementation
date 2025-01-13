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

#include "srsran/ran/resource_allocation/ofdm_symbol_range.h"

namespace srsran {

/// \brief Physical shared channels Mapping Type.
/// \remark see TS38.214 Section 5.3 for PDSCH and TS38.214 Section 6.4 for PUSCH.
enum class sch_mapping_type : uint8_t {
  /// TypeA time allocation, it can start only at symbol 2 or 3 within a slot.
  typeA,
  /// TypeB time allocation.
  typeB
};

/// \brief Collects the PDSCH default time-domain allocation parameters.
///
/// The parameters are provided by TS38.214 Tables 5.1.2.1.1-2, 5.1.2.1.1-3, 5.1.2.1.1-4 and 5.1.2.1.1-5, and in
/// TS 38.331.
/// A configuration is invalid if the duration is zero.
struct pdsch_time_domain_resource_allocation {
  /// PDCCH to PDSCH delay in slots, parameter \f$K_0\f$. Values: (0..32).
  uint8_t k0;
  /// PDSCH mapping.
  sch_mapping_type map_type;
  /// \brief Symbols used within the slot. Parameters \f$S\f$ and \f$L\f$. Values for \f$S\f$ are (0..10) and for
  /// \f$L\f$, (2..12).
  ofdm_symbol_range symbols;

  bool operator==(const pdsch_time_domain_resource_allocation& rhs) const
  {
    return k0 == rhs.k0 && map_type == rhs.map_type && symbols == rhs.symbols;
  }
  bool operator!=(const pdsch_time_domain_resource_allocation& rhs) const { return !(rhs == *this); }
};

} // namespace srsran
