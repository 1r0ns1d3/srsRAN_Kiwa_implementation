/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "cell_meas_manager_test_helpers.h"

using namespace srsran;
using namespace srs_cu_cp;

TEST_F(cell_meas_manager_test, when_empty_cell_config_is_used_validation_fails)
{
  cell_meas_cfg cell_cfg;
  ASSERT_FALSE(is_complete(cell_cfg));
}

TEST_F(cell_meas_manager_test, when_valid_cell_config_is_used_validation_succeeds)
{
  cell_meas_cfg cell_cfg;
  cell_cfg.nci                 = 0;
  cell_cfg.band.emplace()      = nr_band::n78;
  cell_cfg.ssb_arfcn.emplace() = 632628;
  cell_cfg.ssb_scs.emplace()   = subcarrier_spacing::kHz30;
  rrc_ssb_mtc ssb_mtc;
  ssb_mtc.dur                                  = 1;
  ssb_mtc.periodicity_and_offset.sf5.emplace() = 0;
  cell_cfg.ssb_mtc.emplace()                   = ssb_mtc;
  ASSERT_TRUE(is_complete(cell_cfg));
}

TEST_F(cell_meas_manager_test, when_empty_config_is_used_validation_succeeds)
{
  cell_meas_manager_cfg cfg = {};
  ASSERT_TRUE(is_valid_configuration(cfg));
}

TEST_F(cell_meas_manager_test, when_empty_neighbor_is_defined_but_no_event_configured_validation_fails)
{
  cell_meas_manager_cfg cfg = {};
  cell_meas_cfg         cell_cfg;
  cell_cfg.nci = 0;
  cfg.cells.insert({cell_cfg.nci, cell_cfg});

  ASSERT_FALSE(is_valid_configuration(cfg));
}

TEST_F(cell_meas_manager_test, when_empty_config_is_used_then_no_neighbor_cells_are_available)
{
  create_empty_manager();

  nr_cell_id_t           cid      = 0;
  optional<rrc_meas_cfg> meas_cfg = manager->get_measurement_config(cid);

  // Make sure meas_cfg is empty.
  verify_empty_meas_cfg(meas_cfg);
}

TEST_F(cell_meas_manager_test, when_serving_cell_not_found_no_neighbor_cells_are_available)
{
  create_default_manager();

  nr_cell_id_t           cid      = 5;
  optional<rrc_meas_cfg> meas_cfg = manager->get_measurement_config(cid);

  // Make sure meas_cfg is empty.
  verify_empty_meas_cfg(meas_cfg);
}

TEST_F(cell_meas_manager_test, when_serving_cell_found_then_neighbor_cells_are_available)
{
  create_default_manager();

  for (unsigned cid = 0; cid < 2; ++cid) {
    optional<rrc_meas_cfg> meas_cfg = manager->get_measurement_config(cid);
    check_default_meas_cfg(meas_cfg);
  }
}

TEST_F(cell_meas_manager_test, when_inexisting_cell_config_is_updated_then_update_fails)
{
  create_default_manager();

  const nr_cell_id_t nci = 1;

  // get current config
  optional<cell_meas_cfg> cell_cfg = manager->get_cell_config(nci);
  ASSERT_TRUE(cell_cfg.has_value());

  // update config for cell 3
  auto& cell_cfg_val               = cell_cfg.value();
  cell_cfg_val.nci                 = 3;
  cell_cfg_val.band.emplace()      = nr_band::n78;
  cell_cfg_val.ssb_arfcn.emplace() = 632628;
  cell_cfg_val.ssb_scs.emplace()   = subcarrier_spacing::kHz30;
  ASSERT_FALSE(manager->update_cell_config(cell_cfg_val.nci, cell_cfg_val));
}

TEST_F(cell_meas_manager_test, when_incomplete_cell_config_is_updated_then_valid_meas_config_is_created)
{
  create_default_manager();

  const nr_cell_id_t nci = 1;

  // get current config
  optional<cell_meas_cfg> cell_cfg = manager->get_cell_config(nci);
  ASSERT_TRUE(cell_cfg.has_value());

  // update config for cell 1
  auto& cell_cfg_val               = cell_cfg.value();
  cell_cfg_val.band.emplace()      = nr_band::n78;
  cell_cfg_val.ssb_arfcn.emplace() = 632628;
  cell_cfg_val.ssb_scs.emplace()   = subcarrier_spacing::kHz30;
  ASSERT_TRUE(manager->update_cell_config(cell_cfg_val.nci, cell_cfg_val));

  // Make sure meas_cfg is created.
  optional<rrc_meas_cfg> meas_cfg = manager->get_measurement_config(nci);
  check_default_meas_cfg(meas_cfg);
}
