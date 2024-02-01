/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

namespace srsran {
namespace ether {

class frame_notifier;

/// \brief Describes an Ethernet receiver.
///
/// The receiver notifies incoming Ethernet frames through the \c frame_notifier interface.
class receiver
{
public:
  /// Default destructor.
  virtual ~receiver() = default;

  /// \brief Starts the Ethernet receiver operation.
  ///
  /// \param[in] notifier Ethernet frames reception notifier.
  /// \note Caller will be blocked until the receiver is fully started.
  virtual void start(frame_notifier& notifier) = 0;

  /// \brief Stops the Ethernet receiver operation.
  /// \note Caller will be blocked until the receiver is fully stopped.
  virtual void stop() = 0;
};

} // namespace ether
} // namespace srsran
