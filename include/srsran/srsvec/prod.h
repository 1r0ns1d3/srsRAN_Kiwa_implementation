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

#include "srsran/srsvec/types.h"

namespace srsran {
namespace srsvec {

void prod(span<const cf_t> x, span<const cf_t> y, span<cf_t> z);
void prod(span<const cf_t> x, span<const float> y, span<cf_t> z);
void prod(span<const float> x, span<const cf_t> y, span<cf_t> z);
void prod(span<const float> x, span<const float> y, span<float> z);

void prod_conj(span<const cf_t> x, span<const cf_t> y, span<cf_t> z);

} // namespace srsvec
} // namespace srsran
