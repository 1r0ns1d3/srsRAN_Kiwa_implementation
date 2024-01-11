/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/phy/upper/log_likelihood_ratio.h"
#include <gtest/gtest.h>
#include <random>

using namespace srsran;

static std::mt19937       rgen(1234);
static constexpr unsigned nof_repetitions = 100;
static constexpr unsigned bitword_len     = 1000;

static void build_random_softbits(span<log_likelihood_ratio> soft_bits)
{
  std::uniform_int_distribution<log_likelihood_ratio::value_type> llr_dist(log_likelihood_ratio::min().to_int(),
                                                                           log_likelihood_ratio::max().to_int());

  for (auto& llr : soft_bits) {
    llr = llr_dist(rgen);
  }
}

static void hard_decision_golden(bit_buffer& hard_bits, span<const log_likelihood_ratio> soft_bits)
{
  for (unsigned index = 0, index_end = hard_bits.size(); index != index_end; ++index) {
    log_likelihood_ratio llr = soft_bits[index];
    hard_bits.insert(llr.to_hard_bit(), index, 1);
  }
}

TEST(HardDecision, valid_results)
{
  for (unsigned rep = 0; rep != nof_repetitions; ++rep) {
    // Buffer to hold soft bits.
    std::vector<log_likelihood_ratio> soft_bits(bitword_len);

    // Buffer to hold the hard bits generated with the implementation under test.
    dynamic_bit_buffer hard_bits_actual(bitword_len);

    // Buffer to hold the hard bits generated with the golden function.
    dynamic_bit_buffer hard_bits_expected(bitword_len);

    // Generate a pseudorandom bit word.
    build_random_softbits(soft_bits);

    // Compute hard bit sequence;
    srsran::hard_decision(hard_bits_actual, soft_bits);

    // Compute expected hard bit sequence.
    hard_decision_golden(hard_bits_expected, soft_bits);

    for (unsigned i_bit = 0; i_bit != bitword_len; ++i_bit) {
      // Assert results.
      ASSERT_EQ(hard_bits_expected.extract(i_bit, 1), hard_bits_actual.extract(i_bit, 1))
          << "Bit " << i_bit << " does not match.";
    }
  }
}
