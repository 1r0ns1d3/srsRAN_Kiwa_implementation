/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/hal/phy/upper/channel_processors/pusch/ext_harq_buffer_context_repository_factory.h"

using namespace srsran;
using namespace hal;

std::shared_ptr<ext_harq_buffer_context_repository>
srsran::hal::create_ext_harq_buffer_context_repository(unsigned nof_rnti, unsigned nof_harq_id, bool debug_mode)
{
  return std::make_shared<ext_harq_buffer_context_repository>(nof_rnti, nof_harq_id, debug_mode);
}
