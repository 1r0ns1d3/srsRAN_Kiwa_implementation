/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ru_ofh_factories.h"
#include "apps/services/worker_manager/worker_manager.h"
#include "apps/units/flexible_o_du/split_helpers/flexible_o_du_configs.h"
#include "ru_ofh_config_translator.h"
#include "srsran/ru/ofh/ru_ofh_factory.h"

using namespace srsran;

std::unique_ptr<radio_unit> srsran::create_ofh_radio_unit(const ru_ofh_unit_config&            ru_cfg,
                                                          const flexible_o_du_ru_config&       ru_config,
                                                          const flexible_o_du_ru_dependencies& ru_dependencies)
{
  ru_ofh_dependencies dependencies;

  dependencies.logger             = &srslog::fetch_basic_logger("OFH");
  dependencies.rt_timing_executor = ru_dependencies.workers.ru_timing_exec;
  dependencies.timing_notifier    = &ru_dependencies.timing_notifier;
  dependencies.rx_symbol_notifier = &ru_dependencies.symbol_notifier;
  dependencies.error_notifier     = &ru_dependencies.error_notifier;

  const unsigned nof_sectors = ru_cfg.cells.size();

  // Number of OFH sectors served by a single executor for transmitter and receiver tasks.
  unsigned nof_txrx_threads = ru_dependencies.workers.ru_txrx_exec.size();
  unsigned nof_sectors_per_txrx_thread =
      (nof_sectors > nof_txrx_threads) ? static_cast<unsigned>(std::ceil(nof_sectors / float(nof_txrx_threads))) : 1;

  // Configure sector.
  for (unsigned i = 0; i != nof_sectors; ++i) {
    ofh::sector_dependencies& sector_deps = dependencies.sector_dependencies.emplace_back();

    // Note, one executor for transmitter and receiver tasks is shared per two sectors.
    sector_deps.txrx_executor     = ru_dependencies.workers.ru_txrx_exec[i / nof_sectors_per_txrx_thread];
    sector_deps.uplink_executor   = ru_dependencies.workers.ru_rx_exec[i];
    sector_deps.downlink_executor = ru_dependencies.workers.ru_dl_exec[i];
    sector_deps.logger            = dependencies.logger;
  }

  return create_ofh_ru(generate_ru_ofh_config(ru_cfg, ru_config.du_cells, ru_config.max_processing_delay),
                       std::move(dependencies));
}
