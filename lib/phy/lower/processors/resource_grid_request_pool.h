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

#include "srsran/adt/circular_array.h"
#include "srsran/ran/slot_point.h"
#include <mutex>
#include <utility>

namespace srsran {

/// \brief Thread-safe resource grid request pool.
///
/// Contains a pool of requests of slot points and resource grids indexed by slots. A request consist of a slot point a
/// resource grid. The pool access is thread-safe and it is done by exchange requests.
///
/// \tparam GridType Resource grid type.
template <typename GridType>
class resource_grid_request_pool
{
public:
  /// Internal storage type.
  struct request_type {
    slot_point slot;
    GridType   grid;
  };

  /// \brief Exchanges a request from the pool by the given one.
  /// \param[in] request The given request, it is copied into <tt>request.slot.slot_index() % REQUEST_ARRAY_SIZE</tt>.
  /// \return The previous request at position  <tt> request.slot.slot_index() % REQUEST_ARRAY_SIZE </tt>.
  request_type exchange(request_type request) { return requests[request.slot.slot_index()].exchange(request); }

private:
  /// Number of requests contained in the array.
  static constexpr unsigned REQUEST_ARRAY_SIZE = 16;

  /// Wraps the request in a thread-safe access.
  class request_wrapper
  {
  public:
    /// \brief Exchanges the previous request with a new request.
    /// \param[in] new_request New request.
    /// \return A copy of the previous request.
    request_type exchange(const request_type& new_request)
    {
      std::unique_lock<std::mutex> lock(mutex);
      return std::exchange(request, new_request);
    }

  private:
    request_type request;
    std::mutex   mutex;
  };

  /// Request storage, indexed by slots.
  circular_array<request_wrapper, REQUEST_ARRAY_SIZE> requests = {};
};

} // namespace srsran
