/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/phy/upper/equalization/equalization_factories.h"
#include "channel_equalizer_zf_impl.h"

using namespace srsran;

namespace {

class channel_equalizer_factory_zf : public channel_equalizer_factory
{
public:
  channel_equalizer_factory_zf() = default;

  std::unique_ptr<channel_equalizer> create() override { return std::make_unique<channel_equalizer_zf_impl>(); }
};
} // namespace

std::shared_ptr<channel_equalizer_factory> srsran::create_channel_equalizer_factory_zf()
{
  return std::make_shared<channel_equalizer_factory_zf>();
}
