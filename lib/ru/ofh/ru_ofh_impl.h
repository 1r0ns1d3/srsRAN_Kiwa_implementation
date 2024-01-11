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

#include "ru_ofh_controller_impl.h"
#include "ru_ofh_downlink_plane_handler_proxy.h"
#include "ru_ofh_timing_notifier_impl.h"
#include "ru_ofh_uplink_plane_handler_proxy.h"
#include "srsran/ofh/ethernet/ethernet_frame_pool.h"
#include "srsran/ofh/ethernet/ethernet_gateway.h"
#include "srsran/ofh/ofh_sector.h"
#include "srsran/ofh/ofh_uplane_rx_symbol_notifier.h"
#include "srsran/ofh/timing/ofh_timing_manager.h"
#include "srsran/ru/ru.h"
#include "srsran/ru/ru_ofh_configuration.h"
#include "srsran/ru/ru_timing_notifier.h"
#include "srsran/ru/ru_uplink_plane.h"
#include "srsran/srslog/logger.h"

namespace srsran {

/// Open FrontHaul implementation configuration.
struct ru_ofh_impl_config {
  unsigned nof_slot_offset_du_ru;
  unsigned nof_symbols_per_slot;
};

/// Open FrontHaul implementation dependencies.
struct ru_ofh_impl_dependencies {
  srslog::basic_logger*                     logger;
  std::unique_ptr<ofh::timing_manager>      timing_mngr;
  ru_timing_notifier*                       timing_notifier;
  std::vector<std::unique_ptr<ofh::sector>> sectors;
};

/// Open FrontHaul Radio Unit implementation.
class ru_ofh_impl : public radio_unit
{
public:
  ru_ofh_impl(const ru_ofh_impl_config& config, ru_ofh_impl_dependencies&& dependencies);

  // See interface for documentation.
  ru_controller& get_controller() override;

  // See interface for documentation.
  ru_downlink_plane_handler& get_downlink_plane_handler() override;

  // See interface for documentation.
  ru_uplink_plane_handler& get_uplink_plane_handler() override;

private:
  ru_ofh_timing_notifier_impl               timing_notifier;
  std::vector<std::unique_ptr<ofh::sector>> sectors;
  std::unique_ptr<ofh::timing_manager>      ofh_timing_mngr;
  ru_ofh_controller_impl                    controller;
  ru_downlink_plane_handler_proxy           downlink_handler;
  ru_uplink_plane_handler_proxy             uplink_handler;
};

} // namespace srsran
