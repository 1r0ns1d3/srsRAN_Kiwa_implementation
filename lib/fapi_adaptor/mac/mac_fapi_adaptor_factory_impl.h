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

#include "srsran/fapi_adaptor/mac/mac_fapi_adaptor_factory.h"

namespace srsran {
namespace fapi_adaptor {

/// Implementation of the MAC&ndash;FAPI adaptor factory.
class mac_fapi_adaptor_factory_impl : public mac_fapi_adaptor_factory
{
public:
  // See interface for documentation.
  std::unique_ptr<mac_fapi_adaptor> create(const mac_fapi_adaptor_config&  config,
                                           mac_fapi_adaptor_dependencies&& dependencies) override;
};

} // namespace fapi_adaptor
} // namespace srsran
