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

#include "srsran/phy/lower/lower_phy_timing_notifier.h"
#include "srsran/phy/upper/upper_phy_rx_symbol_handler.h"
#include <mutex>

namespace srsran {

class rx_symbol_handler_example : public upper_phy_rx_symbol_handler
{
private:
  srslog::basic_logger& logger;
  std::mutex            mutex;

public:
  rx_symbol_handler_example(std::string log_level) : logger(srslog::fetch_basic_logger("RxSyHan"))
  {
    logger.set_level(srslog::str_to_basic_level(log_level));
  }

  void handle_rx_symbol(const upper_phy_rx_symbol_context& context, const resource_grid_reader& grid) override
  {
    std::unique_lock<std::mutex> lock(mutex);
    logger.debug(context.slot.sfn(),
                 context.slot.slot_index(),
                 "Rx symbol {} received for sector {}",
                 context.symbol,
                 context.sector);
  }

  void handle_rx_prach_window(const prach_buffer_context& context, const prach_buffer& buffer) override
  {
    std::unique_lock<std::mutex> lock(mutex);
    logger.debug(context.slot.sfn(),
                 context.slot.slot_index(),
                 "PRACH symbol {} received for sector {}",
                 context.start_symbol,
                 context.sector);
  }
};

} // namespace srsran
