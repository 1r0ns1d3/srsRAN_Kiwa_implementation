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

#include "srsran/cu_cp/cu_cp_types.h"
#include <chrono>
#include <map>
#include <string>

namespace srsran {

namespace srs_cu_cp {

/// \brief NGAP configuration
struct ngap_configuration {
  unsigned               gnb_id = 0;
  std::string            ran_node_name;
  std::string            plmn; /// Full PLMN as string (without possible filler digit) e.g. "00101"
  unsigned               tac;
  std::vector<s_nssai_t> slice_configurations;
  std::chrono::seconds   ue_context_setup_timeout_s; // timeout for ue context setup in seconds
};

} // namespace srs_cu_cp

} // namespace srsran
