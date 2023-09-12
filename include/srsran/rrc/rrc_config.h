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

#include "rrc_ue_config.h"
#include "srsran/adt/optional.h"
#include "srsran/asn1/rrc_nr/rrc_nr.h"
#include <map>
#include <memory>

namespace srsran {

namespace srs_cu_cp {

/// RLC and PDCP configuration of a radio bearer.
struct rb_cfg_t {
  asn1::rrc_nr::pdcp_cfg_s pdcp_cfg;
  asn1::rrc_nr::rlc_cfg_c  rlc_cfg;
};

struct rrc_cfg_t {
  asn1::rrc_nr::pdcp_cfg_s              srb1_pdcp_cfg; ///< PDCP configuration for SRB1.
  optional<rb_cfg_t>                    srb2_cfg;      ///< Optional SRB2 config. SRB1 is configured by DU
  std::map<five_qi_t, cu_cp_qos_config> drb_config;    ///< Configuration for available 5QI.
  bool                                  force_reestablishment_fallback = false; ///< Force re-establishment fallback.
  unsigned                              rrc_procedure_timeout_ms       = 360;   ///< Timeout for RRC procedures.
};

} // namespace srs_cu_cp

} // namespace srsran
