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

#include "srsran/rlc/rlc_metrics.h"
#include "srsran/rlc/rlc_rx.h"
#include "srsran/rlc/rlc_tx.h"

namespace srsran {

/// Class used to interface with an RLC entity.
/// It will contain getters for the TX and RX entities interfaces.
class rlc_entity
{
public:
  rlc_entity()                              = default;
  virtual ~rlc_entity()                     = default;
  rlc_entity(const rlc_entity&)             = delete;
  rlc_entity& operator=(const rlc_entity&)  = delete;
  rlc_entity(const rlc_entity&&)            = delete;
  rlc_entity& operator=(const rlc_entity&&) = delete;

  virtual rlc_tx_upper_layer_data_interface* get_tx_upper_layer_data_interface() = 0;
  virtual rlc_tx_lower_layer_interface*      get_tx_lower_layer_interface()      = 0;
  virtual rlc_rx_lower_layer_interface*      get_rx_lower_layer_interface()      = 0;
  virtual rlc_metrics                        get_metrics()                       = 0;
};

} // namespace srsran
