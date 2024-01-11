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

#include "srsran/rlc/rlc_metrics.h"

namespace srsran {

/// Class used to receive metrics reports from scheduler and format them into a JSON file.
class rlc_metrics_plotter_json : public rlc_metrics_notifier
{
public:
  explicit rlc_metrics_plotter_json(srslog::log_channel& log_chan_) : log_chan(log_chan_) {}

  /// Notifier called from the scheduler.
  void report_metrics(const rlc_metrics& metrics) override;

private:
  srslog::log_channel& log_chan;
};

} // namespace srsran
