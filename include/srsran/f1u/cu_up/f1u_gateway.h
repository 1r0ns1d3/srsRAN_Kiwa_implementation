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

#include "srsran/f1u/cu_up/f1u_bearer.h"
#include "srsran/f1u/cu_up/f1u_rx_delivery_notifier.h"
#include "srsran/f1u/cu_up/f1u_rx_sdu_notifier.h"
#include "srsran/support/timers.h"

namespace srsran {

/// This class will be used to provide the interfaces to
/// the CU-UP to create and manage F1-U bearers.
class f1u_cu_up_gateway : public srs_cu_up::f1u_bearer_disconnector
{
public:
  f1u_cu_up_gateway()                                    = default;
  virtual ~f1u_cu_up_gateway()                           = default;
  f1u_cu_up_gateway(const f1u_cu_up_gateway&)            = default;
  f1u_cu_up_gateway& operator=(const f1u_cu_up_gateway&) = default;
  f1u_cu_up_gateway(f1u_cu_up_gateway&&)                 = default;
  f1u_cu_up_gateway& operator=(f1u_cu_up_gateway&&)      = default;

  virtual std::unique_ptr<srs_cu_up::f1u_bearer>
  create_cu_bearer(uint32_t                             ue_index,
                   uint32_t                             ul_teid,
                   srs_cu_up::f1u_rx_delivery_notifier& rx_delivery_notifier,
                   srs_cu_up::f1u_rx_sdu_notifier&      rx_sdu_notifier,
                   timer_factory                        timers) = 0;

  virtual void attach_dl_teid(uint32_t ul_teid, uint32_t dl_teid) = 0;
};

} // namespace srsran
