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

#include "ue_context.h"
#include <cstddef>

namespace srsran {

namespace srs_cu_up {

class ue_manager_ctrl
{
public:
  virtual ~ue_manager_ctrl() = default;

  virtual ue_context* add_ue(const ue_context_cfg& ue_cfg) = 0;
  virtual void        remove_ue(ue_index_t ue_index)       = 0;
  virtual ue_context* find_ue(ue_index_t ue_index)         = 0;
  virtual size_t      get_nof_ues() const                  = 0;
};

} // namespace srs_cu_up

} // namespace srsran
