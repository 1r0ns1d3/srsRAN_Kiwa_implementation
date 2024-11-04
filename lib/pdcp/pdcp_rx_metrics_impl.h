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

#include "srsran/pdcp/pdcp_rx_metrics.h"
#include <mutex>

namespace srsran {

class pdcp_rx_metrics
{
  pdcp_rx_metrics_container metrics = {};
  std::mutex                metrics_mutex;

public:
  void add_sdus(uint32_t num_sdus_, size_t num_sdu_bytes_)
  {
    metrics.num_sdus += num_sdus_;
    metrics.num_sdu_bytes += num_sdu_bytes_;
  }

  void add_pdus(uint32_t num_pdus_, size_t num_pdu_bytes_)
  {
    metrics.num_pdus += num_pdus_;
    metrics.num_pdu_bytes += num_pdu_bytes_;
  }

  void add_lost_pdus(uint32_t num_pdus_) { metrics.num_dropped_pdus += num_pdus_; }

  void add_dropped_pdus(uint32_t num_pdus_) { metrics.num_dropped_pdus += num_pdus_; }

  void add_integrity_verified_pdus(uint32_t num_pdus_) { metrics.num_integrity_verified_pdus += num_pdus_; }

  void add_integrity_failed_pdus(uint32_t num_pdus_) { metrics.num_integrity_failed_pdus += num_pdus_; }

  void add_t_reordering_timeouts(uint32_t num_timeouts_) { metrics.num_t_reordering_timeouts += num_timeouts_; }

  pdcp_rx_metrics_container get_metrics() { return metrics; }

  pdcp_rx_metrics_container get_metrics_and_reset()
  {
    pdcp_rx_metrics_container   ret = metrics;
    metrics                         = {};
    return ret;
  }

  void reset_metrics() { metrics = {}; }
};

} // namespace srsran
