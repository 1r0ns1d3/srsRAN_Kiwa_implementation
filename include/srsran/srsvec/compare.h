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

#include "srsran/srsvec/detail/traits.h"
#include "srsran/srsvec/types.h"

namespace srsran {
namespace srsvec {

namespace detail {
const char* find(span<const char> input, char value);
}

template <typename T1, typename T2>
bool equal(const T1& s1, const T2& s2)
{
  static_assert(detail::is_span_compatible<T1>::value, "Template type is not compatible with a span");
  static_assert(detail::is_span_compatible<T2>::value, "Template type is not compatible with a span");
  srsran_srsvec_assert_size(s1, s2);

  return std::equal(s1.begin(), s1.end(), s2.begin(), s2.end());
}

/// \brief Finds the first value in \input that is equal to \c value.
///
/// The implementation is equivalent to:
/// \code
/// const T* find(span<const T> input, T value) {
///   return std::find(input.begin(), input.end(), value);
/// }
/// \endcode
///
/// \tparam T Any data type that is one byte wide.
/// \param[in] input Input values.
/// \param[in] value Value to find.
/// \return The pointer to the first element that is equal to \c value if any, \c input.end() otherwise.
template <typename T>
const T* find(span<const T> input, T value)
{
  static_assert(sizeof(T) == 1, "The datatype must be one byte wide.");
  return (const T*)detail::find(span<const char>((const char*)input.data(), input.size()), *((char*)&value));
}

/// \brief Finds the maximum absolute value in a complex span.
///
/// In case two elements have the same absolute value, the one with lowest index is selected.
///
/// The implementation is equivalent to:
/// \code
///  std::pair<unsigned, float> max_abs_element(span<const cf_t> x) {
///    const cf_t* it = std::max_element(x.begin(), x.end(), [](cf_t a, cf_t b){ return (abs_sq(a) < abs_sq(b)); });
///    return {static_cast<unsigned>(it - x.begin()), abs_sq(*it)};
///  }
/// \endcode
///
/// \param[in] x Input samples.
/// \return A pair comprising the index and the squared modulo of the maximum element.
std::pair<unsigned, float> max_abs_element(span<const cf_t> x);

/// \brief Finds the maximum value in a real span.
///
/// In case two elements have the same value, the one with lowest index is selected.
///
/// The implementation is equivalent to:
/// \code
///  std::pair<unsigned, float> max_element(span<const float> x) {
///    const float* it = std::max_element(x.begin(), x.end());
///    return {static_cast<unsigned>(it - x.begin()), *it};
///  }
/// \endcode
///
/// \param[in] x Input samples.
/// \return A pair comprising the index and the value of the maximum element.
std::pair<unsigned, float> max_element(span<const float> x);

} // namespace srsvec
} // namespace srsran
