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

#include "srsran/phy/upper/channel_modulation/modulation_mapper.h"
#include "srsran/support/math_utils.h"
#include <map>

namespace srsran {

/// Modulation mapper based on look-up tables.
class modulation_mapper_lut_impl : public modulation_mapper
{
public:
  // See interface for the documentation.
  void modulate(span<cf_t> symbols, const bit_buffer& input, modulation_scheme scheme) override;

  // See interface for the documentation.
  float modulate(span<ci8_t> symbols, const bit_buffer& input, modulation_scheme scheme) override;
};

} // namespace srsran
