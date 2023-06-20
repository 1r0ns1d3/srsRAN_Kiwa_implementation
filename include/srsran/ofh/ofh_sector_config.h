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

#include "srsran/adt/static_vector.h"
#include "srsran/ofh/compression/compression_params.h"
#include "srsran/ofh/ethernet/ethernet_mac_address.h"
#include "srsran/ofh/ofh_constants.h"
#include "srsran/ofh/ofh_uplane_rx_symbol_notifier.h"
#include "srsran/ofh/transmitter/ofh_transmitter_configuration.h"
#include "srsran/ran/bs_channel_bandwidth.h"
#include "srsran/ran/cyclic_prefix.h"
#include <string>

namespace srsran {

class task_executor;

namespace ofh {

/// Open Fronthaul sector configuration.
struct sector_configuration {
  /// Logger.
  srslog::basic_logger* logger = nullptr;
  /// Receiver task executor.
  task_executor* receiver_executor = nullptr;
  /// User-Plane received symbol notifier.
  uplane_rx_symbol_notifier* notifier = nullptr;

  /// Ethernet interface name.
  std::string interface;
  /// Destination MAC address, corresponds to the Radio Unit MAC address.
  ether::mac_address mac_dst_address;
  /// Source MAC address, corresponds to the Distributed Unit MAC address.
  ether::mac_address mac_src_address;
  /// Tag control information field.
  uint16_t tci;

  /// DU transmission window timing parameters.
  ofh::du_tx_window_timing_parameters tx_window_timing_params;

  /// Cyclic prefix.
  cyclic_prefix cp;
  /// Highest subcarrier spacing.
  subcarrier_spacing scs;
  /// Cell channel bandwidth.
  bs_channel_bandwidth_fr1 bw;
  /// \brief RU operating bandwidth.
  ///
  /// Set this option when the operating bandwidth of the RU is larger than the configured bandwidth of the cell.
  bs_channel_bandwidth_fr1 ru_operating_bw;

  /// Uplink PRACH eAxC.
  unsigned ul_prach_eaxc;
  /// Downlink eAxC.
  static_vector<unsigned, ofh::MAX_NOF_SUPPORTED_EAXC> dl_eaxc;
  /// Uplink eAxC.
  static_vector<unsigned, ofh::MAX_NOF_SUPPORTED_EAXC> ul_eaxc;

  /// Enables the Control-Plane PRACH message signalling.
  bool is_prach_control_plane_enabled = false;
  /// \brief Downlink broadcast flag.
  ///
  /// If enabled, broadcasts the contents of a single antenna port to all downlink RU eAxCs.
  bool is_downlink_broadcast_enabled = false;
  /// Uplink compression parameters.
  ofh::ru_compression_params ul_compression_params;
  /// Downlink compression parameters.
  ofh::ru_compression_params dl_compression_params;
  /// IQ data scaling to be applied prior to Downlink data compression.
  float iq_scaling;
  /// \brief Number of slots the timing handler is notified in advance of the transmission time.
  ///
  /// Sets the maximum allowed processing delay in slots.
  unsigned max_processing_delay_slots;
};

} // namespace ofh
} // namespace srsran
