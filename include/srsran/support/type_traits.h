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

#include <type_traits>

namespace srsran {

namespace detail {

// To allow ADL with custom begin/end.
using std::begin;
using std::end;

template <typename T>
auto is_iterable_impl(int)
    -> decltype(begin(std::declval<T&>()) != end(std::declval<T&>()),   // begin/end and operator !=
                void(),                                                 // Handle evil operator ,
                ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
                void(*begin(std::declval<T&>())),                       // operator*
                std::true_type{});

template <typename T>
std::false_type is_iterable_impl(...);

} // namespace detail

template <typename T>
constexpr bool is_iterable = decltype(detail::is_iterable_impl<T>(0))::value;

} // namespace srsran
