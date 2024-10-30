/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "cu_up_unit_config_translators.h"
#include "apps/services/worker_manager_config.h"
#include "cu_up_unit_config.h"
#include "srsran/cu_up/cu_up_configuration_helpers.h"
#include "srsran/e2/e2ap_configuration_helpers.h"
#include "srsran/rlc/rlc_config.h"

using namespace srsran;

srs_cu_up::cu_up_configuration srsran::generate_cu_up_config(const cu_up_unit_config& config)
{
  srs_cu_up::cu_up_configuration out_cfg;
  out_cfg.statistics_report_period     = std::chrono::seconds{config.metrics.cu_up_statistics_report_period};
  out_cfg.n3_cfg.gtpu_reordering_timer = std::chrono::milliseconds{config.gtpu_reordering_timer_ms};
  out_cfg.n3_cfg.warn_on_drop          = config.warn_on_drop;

  out_cfg.net_cfg.n3_bind_addr      = config.upf_cfg.bind_addr;
  out_cfg.net_cfg.n3_ext_addr       = config.upf_cfg.ext_addr;
  out_cfg.net_cfg.n3_bind_interface = config.upf_cfg.bind_interface;
  out_cfg.net_cfg.n3_rx_max_mmsg    = config.upf_cfg.udp_rx_max_msgs;
  out_cfg.net_cfg.pool_threshold    = config.upf_cfg.pool_threshold;

  out_cfg.test_mode_cfg.enabled           = config.test_mode_cfg.enabled;
  out_cfg.test_mode_cfg.integrity_enabled = config.test_mode_cfg.integrity_enabled;
  return out_cfg;
}

std::map<five_qi_t, srs_cu_up::cu_up_qos_config>
srsran::generate_cu_up_qos_config(const cu_up_unit_config& cu_up_config)
{
  std::map<five_qi_t, srs_cu_up::cu_up_qos_config> out_cfg = {};
  if (cu_up_config.qos_cfg.empty()) {
    out_cfg =
        config_helpers::make_default_cu_up_qos_config_list(cu_up_config.warn_on_drop,
                                                           timer_duration(cu_up_config.metrics.pdcp.report_period),
                                                           cu_up_config.test_mode_cfg.enabled);
    return out_cfg;
  }

  for (const auto& qos : cu_up_config.qos_cfg) {
    if (out_cfg.find(qos.five_qi) != out_cfg.end()) {
      report_error("Duplicate 5QI configuration: {}\n", qos.five_qi);
    }

    // Convert PDCP custom config
    pdcp_custom_config& out_pdcp_custom = out_cfg[qos.five_qi].pdcp_custom_cfg;
    out_pdcp_custom.tx.warn_on_drop     = cu_up_config.warn_on_drop;
    out_pdcp_custom.tx.test_mode        = cu_up_config.test_mode_cfg.enabled;
    out_pdcp_custom.metrics_period      = timer_duration(cu_up_config.metrics.pdcp.report_period);

    // Convert F1-U config
    srs_cu_up::f1u_config& f1u_cfg = out_cfg[qos.five_qi].f1u_cfg;
    f1u_cfg.warn_on_drop           = cu_up_config.warn_on_drop;
  }
  return out_cfg;
}

void srsran::fill_cu_up_worker_manager_config(worker_manager_config& config, const cu_up_unit_config& unit_cfg)
{
  config.cu_up_cfg = worker_manager_config::cu_up_config{};

  config.cu_up_cfg.value().gtpu_queue_size = unit_cfg.gtpu_queue_size;

  auto& pcap_cfg = config.pcap_cfg;
  if (unit_cfg.pcap_cfg.e1ap.enabled) {
    pcap_cfg.is_e1ap_enabled = true;
  }
  if (unit_cfg.pcap_cfg.n3.enabled) {
    pcap_cfg.is_n3_enabled = true;
  }
  if (unit_cfg.pcap_cfg.f1u.enabled) {
    pcap_cfg.is_f1u_enabled = true;
  }
}

e2ap_configuration srsran::generate_e2_config(const cu_up_unit_config& cu_cp)
{
  e2ap_configuration out_cfg = srsran::config_helpers::make_default_e2ap_config();
  out_cfg.e2_type            = e2_type_t::CU_UP;
  out_cfg.e2sm_kpm_enabled   = cu_cp.e2_cfg.e2sm_kpm_enabled;
  out_cfg.e2sm_rc_enabled    = cu_cp.e2_cfg.e2sm_rc_enabled;
  return out_cfg;
}