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

#include "rlc_base_entity.h"
#include "rlc_rx_tm_entity.h"
#include "rlc_tx_tm_entity.h"

namespace srsran {

class rlc_tm_entity : public rlc_base_entity
{
public:
  rlc_tm_entity(uint32_t                             du_index_,
                du_ue_index_t                        ue_index_,
                rb_id_t                              rb_id_,
                timer_duration                       metrics_period_,
                rlc_metrics_notifier*                rlc_metrics_notifier_,
                rlc_rx_upper_layer_data_notifier&    rx_upper_dn,
                rlc_tx_upper_layer_data_notifier&    tx_upper_dn,
                rlc_tx_upper_layer_control_notifier& tx_upper_cn,
                rlc_tx_lower_layer_notifier&         tx_lower_dn,
                timer_manager&                       timers,
                task_executor&                       pcell_executor,
                task_executor&                       ue_executor,
                rlc_pcap&                            pcap) :
    rlc_base_entity(du_index_,
                    ue_index_,
                    rb_id_,
                    metrics_period_,
                    rlc_metrics_notifier_,
                    timer_factory{timers, ue_executor})
  {
    tx = std::unique_ptr<rlc_tx_entity>(new rlc_tx_tm_entity(du_index_,
                                                             ue_index_,
                                                             rb_id_,
                                                             tx_upper_dn,
                                                             tx_upper_cn,
                                                             tx_lower_dn,
                                                             pcell_executor,
                                                             metrics_period.count() != 0,
                                                             pcap));
    rx = std::unique_ptr<rlc_rx_entity>(
        new rlc_rx_tm_entity(du_index_, ue_index_, rb_id_, rx_upper_dn, metrics_period.count() != 0, pcap));
  }
};

} // namespace srsran
