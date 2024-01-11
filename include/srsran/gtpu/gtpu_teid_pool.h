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

#include "srsran/adt/expected.h"
#include "srsran/gtpu/gtpu_teid.h"
#include "srsran/support/compiler.h"
#include <vector>

namespace srsran {

/// \brief GTP-U TEID pool
///
/// This class provides a TEID pool that users can request unused TEIDs.
/// This allows the CU-UP/DU to allocate unused local TEIDs safely event
/// in the event of TEID wrap-around.
class gtpu_teid_pool
{
public:
  virtual ~gtpu_teid_pool() = default;

  SRSRAN_NODISCARD virtual expected<gtpu_teid_t> request_teid() = 0;

  SRSRAN_NODISCARD virtual bool release_teid(gtpu_teid_t teid) = 0;

  virtual bool full() const = 0;

  virtual uint32_t get_max_teids() = 0;
};
} // namespace srsran
