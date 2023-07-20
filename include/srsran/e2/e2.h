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

#include "e2_event_manager.h"
#include "e2_messages.h"
#include "srsran/adt/byte_buffer.h"
#include "srsran/adt/expected.h"
#include "srsran/asn1/e2ap/e2ap.h"
#include "srsran/asn1/e2ap/e2sm_kpm.h"
#include "srsran/ran/lcid.h"
#include "srsran/scheduler/scheduler_metrics.h"
#include "srsran/support/async/async_task.h"
#include "srsran/support/async/eager_async_task.h"

namespace srsran {

/// This interface is used to push E2 messages to the E2 interface.
class e2_message_handler
{
public:
  virtual ~e2_message_handler() = default;

  /// Handle the incoming E2 message.
  virtual void handle_message(const e2_message& msg) = 0;
};

/// Interface used by E2 to inform about events.
class e2_event_handler
{
public:
  virtual ~e2_event_handler()           = default;
  virtual void handle_connection_loss() = 0;
};

/// This interface notifies the reception of new E2 messages over the E2 interface.
class e2_message_notifier
{
public:
  virtual ~e2_message_notifier() = default;

  /// This callback is invoked on each received E2 message.
  virtual void on_new_message(const e2_message& msg) = 0;
};

class e2_connection_manager
{
public:
  virtual ~e2_connection_manager() = default;

  /// \brief Initiates the E2 Setup procedure as per _____
  /// \param[in] request The E2SetupRequest message to transmit.
  /// \return Returns a e2_setup_response_message struct with the success member set to 'true' in case of a
  /// successful outcome, 'false' otherwise.
  /// and awaits the response. If a E2SetupFailure is received the E2 will handle the failure.
  virtual async_task<e2_setup_response_message> handle_e2_setup_request(e2_setup_request_message& request) = 0;
};

class e2_du_metrics_interface
{
public:
  virtual ~e2_du_metrics_interface() = default;
  /// @brief Get the metrics from the scheduler.
  /// @param ue_metrics
  virtual void get_metrics(scheduler_ue_metrics& ue_metrics) = 0;
};

/// Combined entry point for E2 handling.
class e2_interface : public e2_message_handler, public e2_event_handler, public e2_connection_manager
{
public:
  virtual ~e2_interface() = default;
};

} // namespace srsran
