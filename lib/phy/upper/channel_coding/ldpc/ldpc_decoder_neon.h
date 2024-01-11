/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

/// \file
/// \brief LDPC decoder - declaration of the NEON-optimized implementation.

#pragma once

#include "ldpc_decoder_impl.h"

namespace srsran {

/// LDPC decoder implementation based on NEON intrinsics.
class ldpc_decoder_neon : public ldpc_decoder_impl
{
private:
  // See ldpc_decoder_impl for the documentation.
  void specific_init() override;

  void compute_soft_bits(span<log_likelihood_ratio>       this_soft_bits,
                         span<const log_likelihood_ratio> this_var_to_check,
                         span<const log_likelihood_ratio> this_check_to_var) override;

  void get_hard_bits(bit_buffer& out) override;

  void compute_var_to_check_msgs(span<log_likelihood_ratio>       this_var_to_check,
                                 span<const log_likelihood_ratio> this_soft_bits,
                                 span<const log_likelihood_ratio> this_check_to_var) override;

  span<log_likelihood_ratio> get_rotated_node(unsigned var_node) override;

  void analyze_var_to_check_msgs(span<log_likelihood_ratio>       min_var_to_check,
                                 span<log_likelihood_ratio>       second_min_var_to_check,
                                 span<uint8_t>                    min_var_to_check_index,
                                 span<uint8_t>                    sign_prod_var_to_check,
                                 span<log_likelihood_ratio>       rotated_node,
                                 span<const log_likelihood_ratio> this_var_to_check,
                                 unsigned                         shift,
                                 unsigned                         var_node) override;

  void compute_check_to_var_msgs(span<log_likelihood_ratio>       this_check_to_var,
                                 span<const log_likelihood_ratio> this_var_to_check,
                                 span<const log_likelihood_ratio> rotated_node,
                                 span<const log_likelihood_ratio> min_var_to_check,
                                 span<const log_likelihood_ratio> second_min_var_to_check,
                                 span<const uint8_t>              min_var_to_check_index,
                                 span<const uint8_t>              sign_prod_var_to_check,
                                 unsigned                         shift,
                                 unsigned                         var_node) override;

  /// Auxiliary buffer to store the rotated variable-to-check messages.
  std::array<log_likelihood_ratio, ldpc::MAX_LIFTING_SIZE * MAX_CHECK_NODE_DEGREE> rotated_var_to_check;

  /// Number of NEON vectors needed to cover a lifted node.
  unsigned node_size_neon = 0;
};
} // namespace srsran