/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "rrc_ue_helpers.h"
#include "srsran/asn1/rrc_nr/msg_common.h"
#include "srsran/asn1/rrc_nr/rrc_nr.h"

using namespace srsran;
using namespace srs_cu_cp;

template <class T>
void srsran::srs_cu_cp::log_rrc_message(rrc_ue_logger&    logger,
                                        const direction_t dir,
                                        byte_buffer_view  pdu,
                                        const T&          msg,
                                        const char*       msg_type)
{
  if (logger.get_basic_logger().debug.enabled()) {
    asn1::json_writer js;
    msg.to_json(js);
    logger.log_debug(pdu.begin(),
                     pdu.end(),
                     "{} {} {} ({} B)",
                     (dir == Rx) ? "Rx" : "Tx",
                     msg_type,
                     msg.msg.c1().type().to_string(),
                     pdu.length());
    logger.log_debug("Containerized {}: {}", msg.msg.c1().type().to_string(), js.to_string());
  } else if (logger.get_basic_logger().info.enabled()) {
    std::vector<uint8_t> bytes{pdu.begin(), pdu.end()};
    logger.log_info(pdu.begin(), pdu.end(), "{}", msg_type);
  }
}

template void srsran::srs_cu_cp::log_rrc_message<asn1::rrc_nr::ul_ccch_msg_s>(rrc_ue_logger&                     logger,
                                                                              const direction_t                  dir,
                                                                              byte_buffer_view                   pdu,
                                                                              const asn1::rrc_nr::ul_ccch_msg_s& msg,
                                                                              const char* msg_type);

template void srsran::srs_cu_cp::log_rrc_message<asn1::rrc_nr::ul_dcch_msg_s>(rrc_ue_logger&                     logger,
                                                                              const direction_t                  dir,
                                                                              byte_buffer_view                   pdu,
                                                                              const asn1::rrc_nr::ul_dcch_msg_s& msg,
                                                                              const char* msg_type);

template void srsran::srs_cu_cp::log_rrc_message<asn1::rrc_nr::dl_ccch_msg_s>(rrc_ue_logger&                     logger,
                                                                              const direction_t                  dir,
                                                                              byte_buffer_view                   pdu,
                                                                              const asn1::rrc_nr::dl_ccch_msg_s& msg,
                                                                              const char* msg_type);

template void srsran::srs_cu_cp::log_rrc_message<asn1::rrc_nr::dl_dcch_msg_s>(rrc_ue_logger&                     logger,
                                                                              const direction_t                  dir,
                                                                              byte_buffer_view                   pdu,
                                                                              const asn1::rrc_nr::dl_dcch_msg_s& msg,
                                                                              const char* msg_type);
