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

#include "srsran/adt/byte_buffer.h"
#include "srsran/gateways/sctp_network_gateway.h"
#include "srsran/ngap/ngap.h"
#include "srsran/pcap/dlt_pcap.h"
#include "srsran/srslog/srslog.h"
#include <cstdio>

namespace srsran {
namespace srs_cu_cp {

struct ngap_message;

class ngap_asn1_packer : public srs_cu_cp::ngap_message_handler
{
public:
  ngap_asn1_packer(sctp_network_gateway_data_handler& gw, ngap_message_handler& ngap, dlt_pcap& pcap_);

  void handle_packed_pdu(const byte_buffer& pdu);

  void handle_message(const srs_cu_cp::ngap_message& msg) override;

private:
  srslog::basic_logger&              logger;
  sctp_network_gateway_data_handler& gw;
  ngap_message_handler&              ngap;
  dlt_pcap&                          pcap;
};

} // namespace srs_cu_cp
} // namespace srsran
