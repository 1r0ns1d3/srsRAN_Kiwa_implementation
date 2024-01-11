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

#include "srsran/ofh/serdes/ofh_uplane_message_decoder_properties.h"

namespace srsran {
namespace ofh {

/// Open Fronthaul message decoder properties.
struct message_decoder_results {
  /// eAxC.
  unsigned eaxc;
  /// User-Plane decoding results.
  uplane_message_decoder_results uplane_results;
};

} // namespace ofh
} // namespace srsran
