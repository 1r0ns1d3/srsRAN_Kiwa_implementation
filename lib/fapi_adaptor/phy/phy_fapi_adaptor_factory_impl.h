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

#include "srsran/fapi_adaptor/phy/phy_fapi_adaptor_factory.h"

namespace srsran {

namespace fapi_adaptor {

/// Implementation of the PHY&ndash;FAPI adaptor factory.
class phy_fapi_adaptor_factory_impl : public phy_fapi_adaptor_factory
{
public:
  // See interface for documentation.
  std::unique_ptr<phy_fapi_adaptor> create(const phy_fapi_adaptor_factory_config&  config,
                                           phy_fapi_adaptor_factory_dependencies&& dependencies) override;
};

} // namespace fapi_adaptor
} // namespace srsran
