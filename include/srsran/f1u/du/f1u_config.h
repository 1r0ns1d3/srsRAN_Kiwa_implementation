/*
 *
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "fmt/format.h"
#include <cstdint>

namespace srsran {
namespace srs_du {

/// \brief Configurable parameters of the F1-U bearer in the DU
struct f1u_config {
  uint32_t t_notify; ///< Timer used for periodic transmission of uplink notifications
};

} // namespace srs_du
} // namespace srsran

namespace fmt {

// F1-U config formatter
template <>
struct formatter<srsran::srs_du::f1u_config> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(srsran::srs_du::f1u_config cfg, FormatContext& ctx) -> decltype(std::declval<FormatContext>().out())
  {
    return format_to(ctx.out(), "t_notif={}", cfg.t_notify);
  }
};

} // namespace fmt
