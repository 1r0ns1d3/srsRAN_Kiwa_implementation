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

#include "srsran/srsvec/types.h"

namespace srsran {
namespace srsvec {

void sc_prod(span<const cf_t> x, cf_t h, span<cf_t> z);
void sc_prod(span<const cbf16_t> x, cf_t h, span<cbf16_t> z);
void sc_prod(span<const cf_t> x, float h, span<cf_t> z);
void sc_prod(span<const float> x, float h, span<float> z);
void sc_prod(span<const int16_t> x, int16_t h, span<int16_t> z);

} // namespace srsvec
} // namespace srsran
