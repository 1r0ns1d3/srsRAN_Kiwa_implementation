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

#include "srsran/adt/expected.h"
#include "srsran/asn1/e1ap/e1ap.h"
#include "srsran/support/async/event_signal.h"
#include "srsran/support/async/protocol_transaction_manager.h"
#include "srsran/support/timers.h"

namespace srsran {
namespace srs_cu_cp {

using e1ap_outcome     = expected<asn1::e1ap::successful_outcome_s, asn1::e1ap::unsuccessful_outcome_s>;
using e1ap_transaction = protocol_transaction<e1ap_outcome>;

class e1ap_transaction_manager
{
public:
  /// Transaction Response Container, which gets indexed by transaction_id.
  static constexpr size_t                    MAX_NOF_TRANSACTIONS = 256;
  protocol_transaction_manager<e1ap_outcome> transactions;

  explicit e1ap_transaction_manager(timer_factory timers) : transactions(MAX_NOF_TRANSACTIONS, timers) {}
};

} // namespace srs_cu_cp
} // namespace srsran
