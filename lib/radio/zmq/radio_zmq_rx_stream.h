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

#include "radio_zmq_rx_channel.h"
#include "radio_zmq_tx_align_interface.h"
#include "srsran/gateways/baseband/baseband_gateway_receiver.h"
#include <memory>

namespace srsran {

class radio_zmq_rx_stream : public baseband_gateway_receiver
{
private:
  /// Alignment timeout. Waits this time before padding zeros.
  const std::chrono::milliseconds RECEIVE_TS_ALIGN_TIMEOUT = std::chrono::milliseconds(100);
  /// Desired receive number of samples.
  static constexpr unsigned RECEIVE_BUFFER_SIZE = 1920;
  /// Transmitter alignment interface.
  radio_zmq_tx_align_interface& tx_align;
  /// Indicates whether the class was initialized successfully.
  bool successful = false;
  /// Stores independent channels.
  std::vector<std::unique_ptr<radio_zmq_rx_channel>> channels;
  /// Counts the number of received samples.
  uint64_t sample_count = 0;

public:
  /// Describes the necessary parameters to create a ZMQ Tx stream.
  struct stream_description {
    /// Indicates the socket type.
    int socket_type;
    /// Indicates the addresses to bind. The number of elements indicate the number of channels.
    std::vector<std::string> address;
    /// Stream identifier.
    unsigned stream_id;
    /// Stream identifier string.
    std::string stream_id_str;
    /// Logging level.
    std::string log_level;
    /// Indicates the socket send and receive timeout in milliseconds. It is ignored if it is zero.
    unsigned trx_timeout_ms;
    /// Indicates the socket linger timeout in milliseconds. If is ignored if trx_timeout_ms is zero.
    unsigned linger_timeout_ms;
    /// Indicates the channel buffer size.
    unsigned buffer_size;
  };

  radio_zmq_rx_stream(void*                         zmq_context,
                      const stream_description&     config,
                      task_executor&                async_executor_,
                      radio_zmq_tx_align_interface& tx_align_,
                      radio_notification_handler&   notification_handler);

  bool is_successful() const { return successful; }

  uint64_t get_sample_count() const { return sample_count; }

  unsigned int get_buffer_size() override;

  // See interface for documentation.
  metadata receive(baseband_gateway_buffer& data) override;

  void stop();

  void wait_stop();
};

} // namespace srsran
