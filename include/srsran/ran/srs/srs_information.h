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

#include "srs_resource_configuration.h"
namespace srsran {

/// \brief Collects Sounding Reference Signal information.
///
/// Contains the derived parameters that are used for the SRS sequence generation and mapping, as per TS38.211 Sections
/// 6.4.1.4.2 and 6.4.1.4.3.
///
/// The parameters describe the sequence and its allocation for a certain transmission port and OFDM symbol.
struct srs_information {
  /// Sequence length, parameter \f$M_{sc,b}^{SRS}\f$.
  unsigned sequence_length;
  /// Sequence group, parameter \f$u\f$.
  unsigned sequence_group;
  /// Sequence number, parameter \f$v\f$.
  unsigned sequence_number;
  /// Sequence cyclic shift, parameter \f$\alpha\f$.
  float alpha;
  /// First subcarrier used for mapping the sequence within the BWP, parameter \f$k_{0}^{(p_i)}\f$.
  unsigned mapping_initial_subcarrier;
  /// Comb size, parameter \f$K_{TC}\f$.
  unsigned comb_size;
};

/// \brief Get Sounding Reference Signal information.
/// \param resource       SRS resource configuration.
/// \param i_antenna_port Transmit antenna 0-based port index.
/// \param i_symbol       OFDM symbol index within the slot.
/// \return The SRS information.
/// \remark An assertion is triggered if one or more resource parameters are invalid or not supported.
srs_information
get_srs_information(const srs_resource_configuration& resource, unsigned i_antenna_port, unsigned i_symbol);

} // namespace srsran
