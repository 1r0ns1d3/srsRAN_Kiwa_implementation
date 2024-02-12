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

#include <cstdint>

namespace srsran {

/// Global NodeB DU ID as per TS 38.473.
enum class gnb_du_id_t : uint64_t { min = 0, max = 68719476735, invalid = max + 1 };

inline gnb_du_id_t int_to_gnb_du_id(uint64_t id)
{
  return static_cast<gnb_du_id_t>(id);
}

} // namespace srsran