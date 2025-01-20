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

namespace srsran {

class prach_processor_notifier;
class prach_processor_request_handler;
class prach_processor_baseband;

/// \brief PRACH processor main interface.
///
/// Provides a single access point to all PRACH-related interfaces, that is \ref prach_processor_notifier,
/// \ref prach_processor_request_handler and \ref prach_processor_baseband.
///
/// \note All implementations of this interface must trigger an assertion error if the PRACH processor is not connected
/// to a notifier before calling \ref get_request_handler() or \ref get_baseband().
class prach_processor
{
public:
  /// Default destructor.
  virtual ~prach_processor() = default;

  /// Connects the PRACH processor with a notifier.
  virtual void connect(prach_processor_notifier& notifier) = 0;

  /// \brief Gets the PRACH processor request handler.
  /// \return A reference to the internal PRACH processor request handler.
  virtual prach_processor_request_handler& get_request_handler() = 0;

  /// \brief Gets the PRACH processor baseband interface.
  /// \return A reference to the internal PRACH processor baseband interface.
  virtual prach_processor_baseband& get_baseband() = 0;
};

} // namespace srsran