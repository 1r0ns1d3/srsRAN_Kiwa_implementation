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

#include "srsran/adt/variant.h"
#include "srsran/ru/ru_generic_configuration.h"
#include "srsran/ru/ru_ofh_configuration.h"

namespace srsran {

/// Radio Unit configuration.
struct ru_configuration {
  variant<ru_generic_configuration, ru_ofh_configuration> config;
};

} // namespace srsran
