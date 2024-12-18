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

#include "fmt/args.h"
#include <chrono>

namespace srslog {

namespace detail {

/// This structure gives the user a way to log generic information as a context.
//: TODO: legacy struct, will get replaced by the new context framework.
struct log_context {
  /// Generic context value.
  uint64_t value64;
  /// When true, the context value will be printed in the log entry.
  bool enabled;
};

/// Metadata fields carried for each log entry.
struct log_entry_metadata {
  std::chrono::high_resolution_clock::time_point      tp;
  log_context                                         context;
  const char*                                         fmtstring;
  fmt::dynamic_format_arg_store<fmt::format_context>* store;
  std::string                                         log_name;
  char                                                log_tag;
  std::shared_ptr<const std::string>                  log_label;
  std::vector<uint8_t>                                hex_dump;
};

} // namespace detail

} // namespace srslog
