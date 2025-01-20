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
namespace fapi {

struct dl_csi_rs_pdu;
struct validator_report;

/// Validates the given DL CSI-RS PDU and returns true on success, otherwise false.
bool validate_dl_csi_pdu(const dl_csi_rs_pdu& pdu, validator_report& report);

} // namespace fapi
} // namespace srsran
