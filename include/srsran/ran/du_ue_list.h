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

#include "srsran/adt/slotted_array.h"
#include "srsran/ran/du_types.h"

namespace srsran {

/// \brief Representation of a list of UEs indexed by DU UE Index.
template <typename T>
using du_ue_list = slotted_array<T, MAX_NOF_DU_UES>;

} // namespace srsran
