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

#include "srsran/adt/span.h"
#include "srsran/psup/psup_message.h"
#include "srsran/srslog/logger.h"

namespace srsran {

/// Packing and unpacking of PDU Session Container
///
/// Ref: TS 38.415
class psup_packing
{
public:
  psup_packing(srslog::basic_logger& logger_) : logger(logger_) {}

  bool unpack(psup_dl_pdu_session_information& dl_pdu_session_information, const span<uint8_t> container);

private:
  srslog::basic_logger& logger;
};

} // namespace srsran
