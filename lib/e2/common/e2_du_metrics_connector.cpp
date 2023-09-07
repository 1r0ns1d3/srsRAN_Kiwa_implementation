/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/e2/e2_du_metrics_connector.h"

using namespace srsran;

e2_du_metrics_connector::e2_du_metrics_connector()
{
  ue_metrics_queue.resize(MAX_UE_METRICS);
}

void e2_du_metrics_connector::report_metrics(span<const scheduler_ue_metrics> ue_metrics)
{
  for (auto& ue_metric : ue_metrics) {
    if (ue_metrics_queue.size() == MAX_UE_METRICS) {
      ue_metrics_queue.pop_front();
    }
    ue_metrics_queue.push_back(ue_metric);
  }

  if (e2_meas_provider) {
    // Pass metrics to the E2 Measurement Provider.
    e2_meas_provider->report_metrics(ue_metrics);
  }
}

void e2_du_metrics_connector::get_metrics(scheduler_ue_metrics& ue_metrics)
{
  if (ue_metrics_queue.empty()) {
    return;
  }
  ue_metrics = ue_metrics_queue.front();
}

void e2_du_metrics_connector::connect_e2_du_meas_provider(std::unique_ptr<e2_du_metrics_notifier> meas_provider)
{
  e2_meas_provider = std::move(meas_provider);
}