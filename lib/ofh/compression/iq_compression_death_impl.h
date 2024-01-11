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

#include "srsran/ofh/compression/iq_compressor.h"
#include "srsran/ofh/compression/iq_decompressor.h"

namespace srsran {
namespace ofh {

/// \brief IQ compression death implementation.
///
/// Using this compression will kill the application.
class iq_compression_death_impl : public iq_compressor, public iq_decompressor
{
public:
  // See interface for documentation.
  void compress(span<compressed_prb>         compressed_prbs,
                span<const cf_t>             iq_data,
                const ru_compression_params& params) override;

  // See interface for documentation.
  void decompress(span<cf_t>                   iq_data,
                  span<const compressed_prb>   compressed_prbs,
                  const ru_compression_params& params) override;
};

} // namespace ofh
} // namespace srsran
