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

#include "srsran/support/units.h"

namespace srsran {

/// \brief Maximum number of SI messages that can be scheduled as per TS 38.331, "maxSI-Message".
const size_t MAX_SI_MESSAGES = 32;

/// Scheduling parameters of the SI message.
struct si_message_scheduling_config {
  /// SI message payload size in bytes.
  units::bytes msg_len;
  /// Periodicity of the SI-message in radio frames. Values: {8, 16, 32, 64, 128, 256, 512}.
  unsigned period_radio_frames;
};

/// \brief Configuration of the SI message scheduling.
///
/// This struct will be handled by the MAC scheduler to determine the required PDCCH and PDSCH grants for SI.
struct si_scheduling_config {
  /// List of SI-messages to schedule.
  std::vector<si_message_scheduling_config> si_messages;
  /// \brief The length of the SI scheduling window, in slots.
  ///
  /// It is always shorter or equal to the period of the SI message. Values: {5, 10, 20, 40, 80, 160, 320, 640, 1280}.
  unsigned si_window_len_slots;
};

} // namespace srsran
