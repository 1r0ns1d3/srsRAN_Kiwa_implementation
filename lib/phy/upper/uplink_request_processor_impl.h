/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsgnb/phy/upper/uplink_request_processor.h"

namespace srsgnb {

class prach_buffer_pool;
class upper_phy_rx_symbol_request_notifier;

/// \brief Implementation of the uplink request processor interface.
///
/// This implementation processes uplink data requests according to the following steps.
///     1. It adds the received configuration to a ring buffer indexed by slot.
///     2. It resolves all the dependencies.
///     3. It calls a method from the internal upper_phy_rx_symbol_request_notifier object. This will produce and notify
///     an event that requests the capture of slot symbol data.
class uplink_request_processor_impl : public uplink_request_processor
{
public:
  uplink_request_processor_impl(upper_phy_rx_symbol_request_notifier& symbol_request_notifier,
                                prach_buffer_pool&                    prach_memory_pool);

  // See interface for documentation.
  void process_prach_request(const prach_buffer_context& context) override;

private:
  /// Symbol request notifier.
  upper_phy_rx_symbol_request_notifier& symbol_request_notifier;
  /// PRACH buffer pool.
  prach_buffer_pool& prach_memory_pool;
};

} // namespace srsgnb
