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

#include "srsran/phy/upper/channel_processors/pucch_uci_message.h"
#include "srsran/phy/upper/channel_state_information.h"

namespace srsran {

/// Collects PUCCH processor results.
struct pucch_processor_result {
  /// Channel state information.
  channel_state_information csi;
  /// UCI message.
  pucch_uci_message message;
  /// Detection metric normalized with respect to the detection threshold (if applicable).
  std::optional<float> detection_metric;
};

} // namespace srsran
