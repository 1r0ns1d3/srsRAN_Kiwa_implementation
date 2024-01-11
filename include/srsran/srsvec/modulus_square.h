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

/// \brief Calculates the element-wise modulus square of a sequence of complex values.
/// \param[out] result      Output non-negative real values.
/// \param[in]  input       Input complex values.
/// \remark An assertion is triggered if \c input and \c result do not have the same number of elements.
void modulus_square(span<float> result, span<const cf_t> input);

} // namespace srsvec
} // namespace srsran
