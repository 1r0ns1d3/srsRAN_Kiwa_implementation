/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

/// \file
/// \brief Channel precoder AVX2 implementation.

#pragma once

#include "channel_precoder_impl.h"

namespace srsran {

/// Channel precoder implementation.
class channel_precoder_avx2 : public channel_precoder_impl
{
public:
  // See interface for documentation.
  void
  apply_precoding_port(span<cf_t> port_re, const re_buffer_reader& input_re, span<const cf_t> port_weights) override;

  // See interface for documentation.
  void apply_layer_map_and_precoding(re_buffer_writer&              output,
                                     span<const ci8_t>              input,
                                     const precoding_weight_matrix& precoding) override;
};

} // namespace srsran
