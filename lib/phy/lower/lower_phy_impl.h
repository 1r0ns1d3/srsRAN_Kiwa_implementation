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

#include "processors/adaptors/processor_baseband_adaptor.h"
#include "processors/adaptors/processor_handler_adaptor.h"
#include "processors/adaptors/processor_notifier_adaptor.h"
#include "srsran/adt/circular_array.h"
#include "srsran/adt/optional.h"
#include "srsran/gateways/baseband/baseband_gateway.h"
#include "srsran/phy/lower/amplitude_controller/amplitude_controller.h"
#include "srsran/phy/lower/lower_phy.h"
#include "srsran/phy/lower/lower_phy_configuration.h"
#include "srsran/phy/lower/lower_phy_controller.h"
#include "srsran/phy/lower/lower_phy_error_notifier.h"
#include "srsran/phy/lower/lower_phy_request_handler.h"
#include "srsran/phy/lower/lower_phy_rg_handler.h"
#include "srsran/phy/lower/lower_phy_rx_symbol_notifier.h"
#include "srsran/phy/lower/lower_phy_timing_notifier.h"
#include "srsran/phy/lower/modulation/ofdm_modulator.h"
#include "srsran/phy/lower/processors/downlink/downlink_processor.h"
#include "srsran/phy/lower/processors/uplink/uplink_processor.h"
#include "srsran/phy/support/resource_grid_pool.h"
#include "srsran/support/stats.h"

namespace srsran {

/// Lower physical layer implementation.
class lower_phy_impl : public lower_phy
{
public:
  /// Collects the configuration parameters required to create a lower physical layer.
  struct configuration {
    /// Downlink processor.
    std::unique_ptr<lower_phy_downlink_processor> downlink_proc;
    /// Uplink processor.
    std::unique_ptr<lower_phy_uplink_processor> uplink_proc;
    /// Baseband controller.
    std::unique_ptr<lower_phy_controller> controller;
    /// Provides a symbol handler to notify the reception of symbols.
    lower_phy_rx_symbol_notifier* rx_symbol_notifier;
    /// Provides the timing handler to notify the timing boundaries.
    lower_phy_timing_notifier* timing_notifier;
    /// Provides the error handler to notify runtime errors.
    lower_phy_error_notifier* error_notifier;
  };

  /// Constructs a generic lower physical layer.
  lower_phy_impl(configuration& config);

  // See interface for documentation.
  lower_phy_controller& get_controller() override { return *controller; }

  // See interface for documentation.
  lower_phy_request_handler& get_request_handler() override { return handler_adaptor.get_request_handler(); }

  // See interface for documentation.
  lower_phy_rg_handler& get_rg_handler() override { return handler_adaptor.get_rg_handler(); }

  /// Downlink processor.
  std::unique_ptr<lower_phy_downlink_processor> downlink_proc;
  /// Uplink processor.
  std::unique_ptr<lower_phy_uplink_processor> uplink_proc;
  /// Processor handler adaptor.
  processor_handler_adaptor handler_adaptor;
  /// Processor notification adaptor.
  processor_notifier_adaptor notification_adaptor;
  /// Baseband adaptor. It implements the lower physical layer controller.
  std::unique_ptr<lower_phy_controller> controller;
};

} // namespace srsran
