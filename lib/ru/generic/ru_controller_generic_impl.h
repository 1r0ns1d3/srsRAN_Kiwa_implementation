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

#include "srsran/ru/ru_controller.h"
#include <vector>

namespace srsran {

class lower_phy_controller;
class radio_session;

/// Radio Unit controller generic implementation.
class ru_controller_generic_impl : public ru_controller
{
public:
  ru_controller_generic_impl(std::vector<lower_phy_controller*> low_phy_crtl_,
                             radio_session&                     radio_,
                             double                             srate_MHz_);

  // See interface for documentation.
  void start() override;

  // See interface for documentation.
  void stop() override;

  // See interface for documentation.
  bool set_tx_gain(unsigned port_id, double gain_dB) override;

  // See interface for documentation.
  bool set_rx_gain(unsigned port_id, double gain_dB) override;

private:
  std::vector<lower_phy_controller*> low_phy_crtl;
  radio_session&                     radio;
  const double                       srate_MHz;
};

} // namespace srsran
