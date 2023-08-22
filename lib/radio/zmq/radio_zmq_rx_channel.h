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

#include "radio_zmq_rx_channel_fsm.h"
#include "srsran/adt/blocking_queue.h"
#include "srsran/gateways/baseband/buffer/baseband_gateway_buffer_writer.h"
#include "srsran/radio/radio_notification_handler.h"
#include "srsran/srslog/srslog.h"
#include "srsran/support/async/async_queue.h"
#include "srsran/support/executors/task_executor.h"
#include <atomic>
#include <set>
#include <zmq.h>

namespace srsran {

class radio_zmq_rx_channel
{
private:
  /// Lists the supported socket types.
  static const std::set<int> VALID_SOCKET_TYPES;
  /// Wait time after a buffer try push failed.
  const std::chrono::microseconds circ_buffer_try_push_sleep{1};
  /// Wait time after a buffer try pop failed.
  const std::chrono::microseconds circ_buffer_try_pop_sleep{1};
  /// Indicates the stream identifier. Used for notifying events.
  unsigned stream_id;
  /// Channel identifier. Used for notifying events.
  unsigned channel_id;
  /// Indicates the current state of the stream.
  radio_zmq_rx_channel_fsm state_fsm;
  /// ZMQ socket.
  void* sock = nullptr;
  /// ZMQ socket type.
  int socket_type;
  /// Logger.
  srslog::basic_logger& logger;
  /// Stores transmit buffer.
  blocking_queue<cf_t> circular_buffer;
  /// Transmission buffer.
  std::vector<cf_t> buffer;
  /// Notification handler.
  radio_notification_handler& notification_handler;
  /// Asynchronous task executor.
  task_executor& async_executor;

public:
  /// Describes the necessary parameters to create a ZMQ Tx channel.
  struct channel_description {
    /// Indicates the socket type.
    int socket_type;
    /// Indicates the address to bind.
    std::string address;
    /// Stream identifier.
    unsigned stream_id;
    /// Channel identifier.
    unsigned channel_id;
    /// Stream identifier string.
    std::string channel_id_str;
    /// Logging level.
    srslog::basic_levels log_level;
    /// Indicates the socket send and receive timeout in milliseconds. It is ignored if it is zero.
    unsigned trx_timeout_ms;
    /// Indicates the socket linger timeout in milliseconds. If is ignored if trx_timeout_ms is zero.
    unsigned linger_timeout_ms;
    /// Buffer size.
    unsigned buffer_size;
  };

  radio_zmq_rx_channel(void*                       zmq_context,
                       const channel_description&  config,
                       radio_notification_handler& notification_handler,
                       task_executor&              async_executor_);

  ~radio_zmq_rx_channel();

  bool is_successful() const { return state_fsm.is_running(); }

  void send_request();

  void receive_response();

  void run_async();

  void receive(span<cf_t> buffer);

  void start();

  void stop();

  void wait_stop();
};

} // namespace srsran
