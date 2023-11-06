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
#include "srsran/adt/blocking_queue.h"
#include "srsran/gateways/baseband/buffer/baseband_gateway_buffer_dynamic.h"
#include "srsran/phy/lower/amplitude_controller/amplitude_controller.h"
#include "srsran/phy/lower/processors/downlink/downlink_processor.h"
#include "srsran/phy/lower/processors/downlink/downlink_processor_baseband.h"
#include "srsran/phy/lower/processors/downlink/downlink_processor_notifier.h"
#include "srsran/phy/lower/processors/downlink/pdxch/pdxch_processor.h"
#include "srsran/phy/lower/processors/downlink/pdxch/pdxch_processor_baseband.h"
#include "srsran/phy/lower/sampling_rate.h"
#include "srsran/ran/cyclic_prefix.h"
#include "srsran/support/stats.h"

namespace srsran {

/// Collects downlink processor baseband configuration parameters.
struct downlink_processor_baseband_configuration {
  /// Sector identifier.
  unsigned sector_id;
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// Cyclic prefix configuration.
  cyclic_prefix cp;
  /// Baseband sampling rate.
  sampling_rate rate;
  /// Number of transmit ports.
  unsigned nof_tx_ports;
  /// Number of slots notified in advance in the TTI boundary event.
  unsigned nof_slot_tti_in_advance;
  /// Logger.
  srslog::basic_logger* logger;
};

/// Implements a software generic lower PHY downlink baseband processor.
class downlink_processor_baseband_impl : public downlink_processor_baseband
{
public:
  /// \brief Constructs a software generic lower PHY downlink processor that can process downlink resource grids.
  /// \param[in] pdxch_proc_baseband_ PDxCH processor baseband.
  /// \param[in] amplitude_control_   Amplitude controller.
  /// \param[in] config               Downlink processor configuration.
  downlink_processor_baseband_impl(pdxch_processor_baseband&                        pdxch_proc_baseband_,
                                   amplitude_controller&                            amplitude_control_,
                                   const downlink_processor_baseband_configuration& config);

  // See interface for documentation.
  void connect(downlink_processor_notifier& notifier_) { notifier = &notifier_; }

  // See interface for documentation.
  void process(baseband_gateway_buffer_writer& buffer, baseband_gateway_timestamp timestamp) override;

private:
  //  class temp_symbol_buffer
  //  {
  //  public:
  //    void clear()
  //    {
  //      // Mark buffer as empty.
  //      empty = true;
  //    }
  //
  //    unsigned read(baseband_gateway_buffer_writer& out, baseband_gateway_timestamp timestamp)
  //    {
  //      srsran_assert(!is_empty(), "Attempting to read from empty buffer.");
  //      srsran_assert(out.get_nof_channels() == nof_tx_ports, "Number of ports does not match.");
  //
  //      // Clear the buffer if attempting to read samples in the past.
  //      if (timestamp < symbol_start_timestamp) {
  //        clear();
  //        return 0;
  //      }
  //
  //      unsigned read_index = timestamp - symbol_start_timestamp;
  //
  //      // Clear the buffer if attempting to read samples in the future.
  //      if (read_index >= buffer.get_nof_samples()) {
  //        clear();
  //        return 0;
  //      }
  //
  //      // Select the minimum among the samples to process and the number of stored samples that have not been read.
  //      unsigned nof_available_samples = buffer.get_nof_samples() - read_index;
  //      unsigned count                 = std::min(out.get_nof_samples(), nof_available_samples);
  //
  //      // For each port, concatenate samples.
  //      for (unsigned i_port = 0; i_port != nof_tx_ports; ++i_port) {
  //        // Select view of the temporary buffer.
  //        span<const cf_t> temp_buffer_src = buffer[i_port].subspan(read_index, count);
  //
  //        // Select view of the output samples.
  //        span<cf_t> temp_buffer_dst = out.get_channel_buffer(i_port).first(count);
  //
  //        srsvec::copy(temp_buffer_dst, temp_buffer_src);
  //      }
  //
  //      // Clear the buffer if all available
  //      if (count == nof_available_samples) {
  //        clear();
  //      }
  //
  //      // Return the number of read samples.
  //      return count;
  //    }
  //
  //    baseband_gateway_buffer_writer& write_symbol(unsigned symbol_size, baseband_gateway_timestamp symbol_timestamp)
  //    {
  //      srsran_assert(is_empty(), "Attempting to write into non-empty buffer.");
  //      srsran_assert(symbol_size > 0, "Symbol size cannot be zero.");
  //
  //      buffer.resize(symbol_size);
  //      symbol_start_timestamp = symbol_timestamp;
  //      empty                  = false;
  //    }
  //
  //    unsigned get_nof_available_samples(baseband_gateway_timestamp timestamp) const
  //    {
  //      if (empty) {
  //        return 0;
  //      }
  //      unsigned read_index = timestamp - symbol_start_timestamp;
  //      return buffer.get_nof_samples() - read_index;
  //    }
  //
  //    bool is_empty() const { return empty; }
  //
  //  private:
  //    /// Temporal storage of baseband samples.
  //    baseband_gateway_buffer_dynamic buffer;
  //
  //    /// Timestamp of the first baseband sample stored in the temporary buffer.
  //    baseband_gateway_timestamp symbol_start_timestamp;
  //
  //    unsigned nof_tx_ports;
  //
  //    bool empty = true;
  //  };

  /// \brief Processes a new symbol.
  ///
  /// \param[out] buffer Destination buffer.
  /// \param slot Slot number.
  /// \param i_symbol Symbol number within the current slot.
  void process_new_symbol(baseband_gateway_buffer_writer& buffer, slot_point slot, unsigned i_symbol);

  /// Logger for printing amplitude control.
  srslog::basic_logger& amplitude_control_logger;
  /// PDxCH baseband processor.
  pdxch_processor_baseband& pdxch_proc_baseband;
  /// Amplitude control.
  amplitude_controller& amplitude_control;
  /// Number of slots notified in advanced in the TTI boundary.
  unsigned nof_slot_tti_in_advance;
  /// Sector identifier.
  unsigned sector_id;
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// Number of receive ports.
  unsigned nof_rx_ports;
  /// Number of samples per subframe;
  unsigned nof_samples_per_subframe;
  /// Number of slots per subframe;
  unsigned nof_slots_per_subframe;
  /// Number of symbols per slot.
  unsigned nof_symbols_per_slot;
  /// \brief Reading index for the \ref temp_buffer holding OFDM symbols.
  ///
  /// Sample index within the \c temp_buffer data, it points the reading position within the generated signal. It is
  /// used to copy the samples aligned with the requested timestamp into the destination buffer.
  unsigned temp_buffer_read_index;
  /// List of the symbol sizes in number samples for each symbol within the subframe.
  std::vector<unsigned> symbol_sizes;
  /// Temporal storage of baseband samples.
  baseband_gateway_buffer_dynamic temp_buffer;
  /// Reference to the downlink notifier.
  downlink_processor_notifier* notifier = nullptr;
  /// Average symbol power statistics.
  sample_statistics<float> avg_symbol_power;
  /// Peak symbol power statistics.
  sample_statistics<float> peak_symbol_power;
  /// Symbol PAPR statistics.
  sample_statistics<float> symbol_papr;
  /// Timestamp of the first baseband sample stored in the temporary buffer.
  baseband_gateway_timestamp read_index_timestamp;
};

} // namespace srsran
