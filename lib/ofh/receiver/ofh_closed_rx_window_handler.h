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

#include "../support/prach_context_repository.h"
#include "../support/uplink_context_repository.h"
#include "srsran/ofh/ofh_uplane_rx_symbol_notifier.h"
#include "srsran/ofh/receiver/ofh_receiver_timing_parameters.h"
#include "srsran/ofh/receiver/ofh_receiver_warn_unreceived_frames_parameters.h"
#include "srsran/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include "srsran/ofh/timing/slot_symbol_point.h"
#include "srsran/srslog/logger.h"

namespace srsran {

class task_executor;

namespace ofh {

/// Closed reception window handler configuration.
struct closed_rx_window_handler_config {
  /// Radio sector identifier.
  unsigned sector;
  /// Time in number of symbols that the decoder needs to process an Open Fronthaul message. It delays closing the
  /// reception window.
  unsigned nof_symbols_to_process_uplink = 0;
  /// Open Fronthaul receive window parameters.
  rx_window_timing_parameters rx_timing_params;
  /// Warn unreceived Open Fronthaul messages.
  warn_unreceived_ru_frames warn_unreceived_frames = warn_unreceived_ru_frames::after_traffic_detection;
};

/// Closed reception window handler dependencies.
struct closed_rx_window_handler_dependencies {
  srslog::basic_logger*                      logger   = nullptr;
  task_executor*                             executor = nullptr;
  std::shared_ptr<prach_context_repository>  prach_repo;
  std::shared_ptr<uplink_context_repository> uplink_repo;
  std::shared_ptr<uplane_rx_symbol_notifier> notifier;
};

/// Open Fronthaul closed reception window handler.
class closed_rx_window_handler : public ota_symbol_boundary_notifier
{
public:
  closed_rx_window_handler(const closed_rx_window_handler_config&  config,
                           closed_rx_window_handler_dependencies&& dependencies);

  // See interface for documentation.
  void on_new_symbol(slot_symbol_point symbol_point) override;

  /// Starts logging unreceived OFH messages.
  void start_logging_unreceived_messages()
  {
    if (warn_unreceived_frames == warn_unreceived_ru_frames::after_traffic_detection && !log_unreceived_messages) {
      log_unreceived_messages = true;
    }
  }

private:
  /// \brief Handles the uplink context for the closed reception window given by symbol point.
  ///
  /// Pops an uplink context from the uplink repository and when the context is valid, notifies it using the User-Plane
  /// received symbol notifier.
  void handle_uplink_context(slot_symbol_point symbol_point);

  /// \brief Handles the PRACH context for the closed reception window given by symbol point.
  ///
  /// Pops a PRACH context from the PRACH repository and when the context is valid, notifies it using the User-Plane
  /// received symbol notifier.
  void handle_prach_context(slot_symbol_point symbol_point);

private:
  /// \brief Notification delay of the resource grid or PRACH buffer in symbol units.
  ///
  /// This delay is calculated with the T4a_max parameter plus the number of symbols that takes to decode a received
  /// Open Fronthaul message.
  const unsigned                             notification_delay_in_symbols;
  const unsigned                             sector_id;
  const warn_unreceived_ru_frames            warn_unreceived_frames;
  bool                                       log_unreceived_messages;
  srslog::basic_logger&                      logger;
  task_executor&                             executor;
  std::shared_ptr<prach_context_repository>  prach_repo;
  std::shared_ptr<uplink_context_repository> uplink_repo;
  std::shared_ptr<uplane_rx_symbol_notifier> notifier;
};

} // namespace ofh
} // namespace srsran
