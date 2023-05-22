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

#include "srsran/adt/complex.h"
#include "srsran/srsvec/types.h"

namespace srsran {
namespace srsvec {

/// Converts from complex float to int16 applying the given scaling
///
/// \param [in] x is the input data
/// \param [in] scale input data scaling prior conversion
/// \param [out] z resultant data
void convert(span<const cf_t> x, float scale, span<int16_t> z);

/// Converts a sequence of numbers from complex float to int16 applying the given scaling and rounding the result to the
/// nearest integer.
///
/// \param[in]  x     Input data.
/// \param[in]  scale Scaling factor.
/// \param[out] z     Output data.
void convert_round(span<const cf_t> x, float scale, span<int16_t> z);

/// Converts and swaps real and imaginary from complex float to int16 applying the given scaling
///
/// \param [in] x is the input data
/// \param [in] scale input data scaling prior conversion
/// \param [out] z resultant data
void convert_swap(span<const cf_t> x, float scale, span<int16_t> z);

/// Converts from int16 to complex float applying the given scaling
///
/// \param [in] x is the input data
/// \param [in] scale input data scaling after conversion
/// \param [out] z resultant data
void convert(span<const int16_t> x, float scale, span<cf_t> z);

/// Converts and swaps real and imaginary from int16 to complex float applying the given scaling
///
/// \param [in] x is the input data
/// \param [in] scale input data scaling after conversion
/// \param [out] z resultant data
void convert_swap(span<const int16_t> x, float scale, span<cf_t> z);

/// Converts from float to int16 applying the given scaling
///
/// \param [in] x is the input data
/// \param [in] scale input data scaling prior conversion
/// \param [out] z resultant data
void convert(span<const float> x, float scale, span<int16_t> z);

/// Converts a sequence of numbers from float to int16 applying the given scaling and rounding the result to the nearest
/// integer.
///
/// \param[in] x     Input data.
/// \param[in] scale Scaling factor.
/// \param[out] z    Output data.
void convert_round(span<const float> x, float scale, span<int16_t> z);

/// Converts from int16 to float applying the given scaling
///
/// \param [in] x is the input data
/// \param [in] scale input data scaling after conversion
/// \param [out] z resultant data
void convert(span<const int16_t> x, float scale, span<float> z);

} // namespace srsvec
} // namespace srsran
