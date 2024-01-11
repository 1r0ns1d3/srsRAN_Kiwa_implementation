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

#include "srsran/ofh/compression/iq_decompressor.h"

namespace srsran {
namespace ofh {
namespace testing {

/// Dummy IQ decompressor implementation
class iq_decompressor_dummy : public iq_decompressor
{
public:
  // See interface for documentation.
  void decompress(span<cf_t>                   iq_data,
                  span<const compressed_prb>   compressed_prbs,
                  const ru_compression_params& params) override
  {
  }
};

} // namespace testing
} // namespace ofh
} // namespace srsran
