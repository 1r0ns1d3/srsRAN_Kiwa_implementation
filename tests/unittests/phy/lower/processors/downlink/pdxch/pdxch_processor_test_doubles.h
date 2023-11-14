/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "../../../../../gateways/baseband/baseband_gateway_buffer_test_doubles.h"
#include "srsran/phy/lower/lower_phy_rx_symbol_context.h"
#include "srsran/phy/lower/processors/downlink/pdxch/pdxch_processor_baseband.h"
#include "srsran/phy/lower/processors/downlink/pdxch/pdxch_processor_factories.h"
#include "srsran/phy/lower/processors/downlink/pdxch/pdxch_processor_notifier.h"
#include "srsran/phy/lower/processors/downlink/pdxch/pdxch_processor_request_handler.h"
#include "srsran/phy/support/resource_grid_context.h"
#include "srsran/srslog/srslog.h"
#include <random>
#include <vector>

namespace srsran {

class pdxch_processor_baseband_spy : public pdxch_processor_baseband
{
public:
  struct entry_t {
    baseband_gateway_buffer_read_only samples;
    symbol_context                    context;
  };

  pdxch_processor_baseband_spy() : random_data(1009)
  {
    std::mt19937                          rgen;
    std::uniform_real_distribution<float> sample_dist(-1, 1);
    std::generate(random_data.begin(), random_data.end(), [&sample_dist, &rgen]() {
      return cf_t(sample_dist(rgen), sample_dist(rgen));
    });
  }

  void process_symbol(baseband_gateway_buffer_writer& samples, const symbol_context& context) override
  {
    // Counter for the remaining samples to generate.
    std::size_t remaining = samples.get_nof_samples();
    span<cf_t>  random_data_view(random_data);

    while (remaining > 0) {
      // Number of samples to copy for this iteration.
      unsigned   nof_copied_samples = std::min(random_data.size() - random_data_index, remaining);
      span<cf_t> random_samples     = random_data_view.subspan(random_data_index, nof_copied_samples);

      for (unsigned i_ch = 0, i_channel_end = samples.get_nof_channels(); i_ch != i_channel_end; ++i_ch) {
        span<cf_t> channel_samples =
            samples.get_channel_buffer(i_ch).subspan(samples.get_nof_samples() - remaining, nof_copied_samples);

        srsvec::copy(channel_samples, random_samples);
      }

      // Update remaining samples and buffer index.
      remaining -= nof_copied_samples;
      random_data_index = (random_data_index + nof_copied_samples) % random_data.size();
    }

    entries.emplace_back();
    entry_t& entry = entries.back();
    entry.context  = context;
    entry.samples  = samples;
  }

  const std::vector<entry_t>& get_entries() const { return entries; }

  void clear() { entries.clear(); }

private:
  unsigned             random_data_index = 0;
  std::vector<cf_t>    random_data;
  std::vector<entry_t> entries;
};

class pdxch_processor_request_handler_spy : public pdxch_processor_request_handler
{
public:
  void handle_request(const resource_grid_reader& grid, const resource_grid_context& context) override
  {
    // TBD.
  }
};

class pdxch_processor_spy : public pdxch_processor
{
public:
  pdxch_processor_spy(const pdxch_processor_configuration& config_) : config(config_) {}

  void                             connect(pdxch_processor_notifier& notifier_) override { notifier = &notifier_; }
  pdxch_processor_request_handler& get_request_handler() override { return request_handler; }
  pdxch_processor_baseband&        get_baseband() override { return baseband; }

  const pdxch_processor_configuration& get_configuration() const { return config; }

  const pdxch_processor_notifier* get_notifier() const { return notifier; }

  const std::vector<pdxch_processor_baseband_spy::entry_t>& get_baseband_entries() const
  {
    return baseband.get_entries();
  }

  void clear() { baseband.clear(); }

private:
  pdxch_processor_notifier*           notifier = nullptr;
  pdxch_processor_configuration       config;
  pdxch_processor_request_handler_spy request_handler;
  pdxch_processor_baseband_spy        baseband;
};

class pdxch_processor_factory_spy : public pdxch_processor_factory
{
public:
  std::unique_ptr<pdxch_processor> create(const pdxch_processor_configuration& config) override
  {
    std::unique_ptr<pdxch_processor_spy> ptr = std::make_unique<pdxch_processor_spy>(config);
    instance                                 = ptr.get();
    return std::move(ptr);
  }

  pdxch_processor_spy& get_spy() { return *instance; }

private:
  pdxch_processor_spy* instance = nullptr;
};

} // namespace srsran