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

#include "srsran/ofh/ofh_constants.h"
#include "srsran/support/srsran_assert.h"
#include <array>

namespace srsran {
namespace ofh {

/// Sequence identifier generator.
class sequence_identifier_generator
{
  std::array<std::atomic<uint8_t>, MAX_SUPPORTED_EAXC_ID_VALUE> counters;

public:
  /// Default constructor.
  explicit sequence_identifier_generator(unsigned init_value = 0)
  {
    for (unsigned K = 0; K != MAX_SUPPORTED_EAXC_ID_VALUE; ++K) {
      counters[K] = init_value;
    }
  }

  /// Generates a new sequence identifier and returns it.
  uint8_t generate(unsigned eaxc)
  {
    srsran_assert(eaxc < MAX_SUPPORTED_EAXC_ID_VALUE,
                  "Invalid eAxC value '{}'. Maximum eAxC value is '{}'",
                  eaxc,
                  MAX_SUPPORTED_EAXC_ID_VALUE);

    auto& value = counters[eaxc];
    return value++;
  }
};

} // namespace ofh
} // namespace srsran
