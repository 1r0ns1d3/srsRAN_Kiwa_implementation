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

#include "srsran/adt/span.h"

namespace srsran {
namespace ether {

/// Describes an Ethernet gateway.
class gateway
{
public:
  /// Default destructor.
  virtual ~gateway() = default;

  /// Sends the given list of frames through the underlying Ethernet link.
  virtual void send(span<span<const uint8_t>> frames) = 0;
};

} // namespace ether
} // namespace srsran
