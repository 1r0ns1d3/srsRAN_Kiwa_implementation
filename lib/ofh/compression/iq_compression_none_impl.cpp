/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "iq_compression_none_impl.h"
#include "compressed_prb_packer.h"
#include "compressed_prb_unpacker.h"
#include "quantizer.h"

using namespace srsran;
using namespace ofh;

void iq_compression_none_impl::compress(span<compressed_prb>         output,
                                        span<const cf_t>             input,
                                        const ru_compression_params& params)
{
  // Quantizer object.
  quantizer q(params.data_width);

  // Determine a scaling factor to scale input IQ data to the range [-1: +1) and convert it to int16_t below.
  span<const float> float_samples((const float*)(input.data()), input.size() * 2);

  unsigned in_sample_idx = 0;
  for (compressed_prb& c_prb : output) {
    // Auxiliary buffer used for float to int16_t conversion.
    std::array<int16_t, NOF_SUBCARRIERS_PER_RB * 2> conv_buffer;

    q.to_fixed_point(conv_buffer, float_samples.subspan(in_sample_idx, NOF_SUBCARRIERS_PER_RB * 2), iq_scaling);

    compressed_prb_packer packer(c_prb);
    packer.pack(conv_buffer, params.data_width);

    in_sample_idx += (NOF_SUBCARRIERS_PER_RB * 2);
  }
}

void iq_compression_none_impl::decompress(span<cf_t>                   output,
                                          span<const compressed_prb>   input,
                                          const ru_compression_params& params)
{
  // Quantizer object.
  quantizer q(params.data_width);

  unsigned out_idx = 0;
  for (const auto& c_prb : input) {
    compressed_prb_unpacker unpacker(c_prb);
    for (unsigned i = 0, read_pos = 0; i != NOF_SUBCARRIERS_PER_RB; ++i) {
      int16_t re = q.sign_extend(unpacker.unpack(read_pos, params.data_width));
      int16_t im = q.sign_extend(unpacker.unpack(read_pos + params.data_width, params.data_width));
      read_pos += (params.data_width * 2);
      output[out_idx++] = {q.to_float(re), q.to_float(im)};
    }
  }
}
