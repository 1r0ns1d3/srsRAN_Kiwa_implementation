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

#include "srsran/radio/radio_factory.h"
#include <memory>
#include <string>

namespace srsran {

std::unique_ptr<radio_factory> create_plugin_radio_factory(std::string driver_name);

} // namespace srsran
