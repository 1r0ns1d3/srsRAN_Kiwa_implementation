/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/pdcp/pdcp_rx_metrics.h"
#include "srsran/support/resource_usage/resource_usage_utils.h"
#include <atomic>

namespace srsran {
class pdcp_rx_metrics
{
  pdcp_rx_metrics_container metrics = {};

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

  void add_reordering_delay_us(uint32_t reordering_delay_us_)
  {
    metrics.reordering_delay_us += reordering_delay_us_;
    metrics.reordering_counter++;
  }

  // Called from the security engine, possibly from many threads.
  void add_crypto_processing_latency(uint32_t crypto_processing_latency)
  {
    sum_crypto_processing_latency_ns.fetch_add(crypto_processing_latency, std::memory_order_relaxed);
  }

  void add_sdu_latency_ns(uint32_t sdu_latency_ns)
  {
    metrics.sum_sdu_latency_ns += sdu_latency_ns;

    unsigned bin_idx = sdu_latency_ns / (1000 * pdcp_rx_metrics_container::nof_usec_per_bin);

    bin_idx = std::min(bin_idx, pdcp_rx_metrics_container::sdu_latency_hist_bins - 1);
    metrics.sdu_latency_hist[bin_idx]++;

    metrics.max_sdu_latency_ns = std::max(sdu_latency_ns, metrics.max_sdu_latency_ns);
  }

  pdcp_rx_metrics_container get_metrics()
  {
    pdcp_rx_metrics_container ret        = metrics;
    ret.sum_crypto_processing_latency_ns = sum_crypto_processing_latency_ns;
    return ret;
  }

  pdcp_rx_metrics_container get_metrics_and_reset()
  {
    pdcp_rx_metrics_container ret = get_metrics();
    ret.counter++;
    reset_metrics();
    return ret;
  }

  void reset_metrics()
  {
    metrics                          = {};
    sum_crypto_processing_latency_ns = 0;
  }

private:
  std::atomic<uint32_t> sum_crypto_processing_latency_ns = 0;
};

} // namespace srsran
