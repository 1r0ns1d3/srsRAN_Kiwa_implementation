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

namespace srsran {
namespace srs_cu_cp {

/// \brief Generate a Inter DU Handover Request.
cu_cp_inter_du_handover_request generate_inter_du_handover_request();

} // namespace srs_cu_cp
} // namespace srsran
