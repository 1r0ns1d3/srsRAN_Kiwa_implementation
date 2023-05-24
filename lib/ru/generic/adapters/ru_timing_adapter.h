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

#include "srsran/phy/lower/lower_phy_timing_notifier.h"
#include "srsran/ru/ru_timing_notifier.h"

namespace srsran {

/// Implements a generic lower physical layer to Radio Unit timing adapter.
class ru_timing_adapter : public lower_phy_timing_notifier
{
public:
  explicit ru_timing_adapter(ru_timing_notifier& timing_handler_) : timing_handler(timing_handler_) {}

  // See interface for documentation.
  void on_tti_boundary(const lower_phy_timing_context& context) override
  {
    timing_handler.on_tti_boundary(context.slot);
  }

  // See interface for documentation.
  void on_ul_half_slot_boundary(const lower_phy_timing_context& context) override
  {
    timing_handler.on_ul_half_slot_boundary(context.slot);
  }

  // See interface for documentation.
  void on_ul_full_slot_boundary(const lower_phy_timing_context& context) override
  {
    timing_handler.on_ul_full_slot_boundary(context.slot);
  }

private:
  ru_timing_notifier& timing_handler;
};

} // namespace srsran
