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

#include "srsran/adt/slotted_array.h"
#include "srsran/asn1/rrc_nr/rrc_nr.h"
#include "srsran/cu_cp/cu_cp_types.h"
#include "srsran/ran/band_helper.h"
#include "srsran/ran/nr_cgi.h"
#include <string>

namespace srsran {
namespace srs_cu_cp {

/// Basic cell system information provided by DU
struct du_sys_info {
  asn1::rrc_nr::mib_s mib;
  byte_buffer         packed_mib;

  asn1::rrc_nr::sib1_s sib1;
  byte_buffer          packed_sib1;

  const asn1::rrc_nr::serving_cell_cfg_common_sib_s& serv_cell_cfg_common() const
  {
    return sib1.serving_cell_cfg_common;
  }
};

struct du_cell_context {
  du_cell_index_t      cell_index = du_cell_index_t::invalid; /// CU internal cell ID
  du_index_t           du_index   = du_index_t::invalid;      /// Index of the DU containing the cell
  nr_cell_global_id_t  cgi;                                   /// global cell ID
  uint32_t             tac;                                   /// tracking area code
  pci_t                pci;                                   /// Physical cell ID
  std::vector<nr_band> bands;                                 /// NR bands provided/supported by the cell.
  du_sys_info          sys_info;                              /// System information provided by DU
};

struct du_processor_context {
  du_index_t  du_index = du_index_t::invalid; /// Index assisgned by CU-CP
  uint64_t    id;                             /// the gNB-DU-ID
  std::string name = "none";                  /// gNB-DU-Name
};

} // namespace srs_cu_cp

} // namespace srsran
