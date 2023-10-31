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

#include "rlc_bearer_logger.h"
#include "rlc_tx_metrics_container.h"
#include "srsran/pcap/pcap_rlc.h"
#include "srsran/rlc/rlc_tx.h"

namespace srsran {

/// Base class used for transmitting RLC bearers.
/// It provides interfaces for the RLC bearers, for both higher layers and lower layers
/// It also stores interfaces for the higher layers, both for the user-plane
/// and the control plane.
class rlc_tx_entity : public rlc_tx_upper_layer_data_interface,
                      public rlc_tx_lower_layer_interface,
                      public rlc_tx_metrics
{
protected:
  rlc_tx_entity(du_ue_index_t                        du_index,
                rb_id_t                              rb_id,
                rlc_tx_upper_layer_data_notifier&    upper_dn_,
                rlc_tx_upper_layer_control_notifier& upper_cn_,
                rlc_tx_lower_layer_notifier&         lower_dn_,
                pcap_rlc&                            pcap_) :
    logger("RLC", {du_index, rb_id, "DL"}), upper_dn(upper_dn_), upper_cn(upper_cn_), lower_dn(lower_dn_), pcap(pcap_)
  {
  }

  rlc_bearer_logger                    logger;
  rlc_tx_metrics_container             metrics;
  rlc_tx_upper_layer_data_notifier&    upper_dn;
  rlc_tx_upper_layer_control_notifier& upper_cn;
  rlc_tx_lower_layer_notifier&         lower_dn;
  pcap_rlc&                            pcap;

public:
  rlc_tx_metrics get_metrics() { return metrics.get_metrics(); }
  void           reset_metrics() { return metrics.reset_metrics(); }
};

} // namespace srsran
