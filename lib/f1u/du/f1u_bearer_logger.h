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

#include "srsran/ran/lcid.h"
#include "srsran/support/prefixed_logger.h"
#include "fmt/format.h"
#include <string.h>

namespace srsran {
namespace srs_du {

class f1u_bearer_log_prefix
{
public:
  f1u_bearer_log_prefix(uint32_t ue_index, drb_id_t drb_id)
  {
    fmt::memory_buffer buffer;
    fmt::format_to(buffer, "ue={} {}: ", ue_index, drb_id);
    prefix = srsran::to_c_str(buffer);
  }
  const char* to_c_str() const { return prefix.c_str(); }

private:
  std::string prefix;
};

using f1u_bearer_logger = prefixed_logger<f1u_bearer_log_prefix>;

} // namespace srs_du
} // namespace srsran

namespace fmt {

// associated formatter
template <>
struct formatter<srsran::srs_du::f1u_bearer_log_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(srsran::srs_du::f1u_bearer_log_prefix o, FormatContext& ctx)
      -> decltype(std::declval<FormatContext>().out())
  {
    return format_to(ctx.out(), "{}", o.to_c_str());
  }
};
} // namespace fmt
