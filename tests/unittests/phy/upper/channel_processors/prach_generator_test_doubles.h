/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "../../phy_test_utils.h"
#include "srsran/phy/upper/channel_processors/channel_processor_factories.h"
#include "srsran/ran/prach/prach_preamble_information.h"
#include <random>

namespace srsran {

class prach_generator_spy : public prach_generator
{
public:
  struct generate_entry {
    configuration     config;
    std::vector<cf_t> result;
  };

  span<const cf_t> generate(const configuration& config) override
  {
    // Extract sequence length.
    unsigned sequence_length = is_long_preamble(config.format) ? prach_constants::LONG_SEQUENCE_LENGTH
                                                               : prach_constants::SHORT_SEQUENCE_LENGTH;

    // Create entry.
    entries.emplace_back();
    generate_entry& entry = entries.back();
    entry.config          = config;
    entry.result.resize(sequence_length);

    // Generates the random result.
    std::generate(entry.result.begin(), entry.result.end(), [&, n = 0]() mutable {
      return std::polar(1.0F, static_cast<float>((n++) * config.preamble_index) / static_cast<float>(sequence_length));
    });

    return entry.result;
  }

  const std::vector<generate_entry>& get_entries() const { return entries; }

  void clear_entries() { entries.clear(); }

private:
  std::vector<generate_entry> entries;
};

PHY_SPY_FACTORY_TEMPLATE(prach_generator);

} // namespace srsran
