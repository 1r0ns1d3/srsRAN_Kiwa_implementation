/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "uplink_request_processor_impl.h"
#include "srsran/phy/support/prach_buffer_pool.h"
#include "srsran/phy/support/shared_resource_grid.h"
#include "srsran/phy/upper/upper_phy_rx_symbol_request_notifier.h"

using namespace srsran;

uplink_request_processor_impl::uplink_request_processor_impl(
    upper_phy_rx_symbol_request_notifier& rx_symbol_request_notifier_,
    prach_buffer_pool&                    prach_pool_) :
  rx_symbol_request_notifier(rx_symbol_request_notifier_), prach_pool(prach_pool_)
{
}

void uplink_request_processor_impl::process_prach_request(const prach_buffer_context& context)
{
  // Grab a PRACH buffer from the pool.
  prach_buffer& buffer = prach_pool.get_prach_buffer();

  // Notify the PRACH capture request event.
  rx_symbol_request_notifier.on_prach_capture_request(context, buffer);
}

void uplink_request_processor_impl::process_uplink_slot_request(const resource_grid_context& context,
                                                                const shared_resource_grid&  grid)
{
  rx_symbol_request_notifier.on_uplink_slot_request(context, grid);
}
