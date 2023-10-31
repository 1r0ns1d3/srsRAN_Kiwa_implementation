/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/pcap/pcap_rlc.h"

using namespace srsran;

// Pre-defined values for data fields of the PCAP PDU context as defined in Wireshark's "packet-rlc-nr.h"

// RLC mode
constexpr uint8_t PCAP_RLC_TM_MODE = 1;
constexpr uint8_t PCAP_RLC_UM_MODE = 2;
constexpr uint8_t PCAP_RLC_AM_MODE = 4;

// Direction
constexpr uint8_t PCAP_RLC_DIRECTION_UPLINK   = 0;
constexpr uint8_t PCAP_RLC_DIRECTION_DOWNLINK = 1;

// Bearer type
constexpr uint8_t PCAP_RLC_BEARER_TYPE_SRB = 4;
constexpr uint8_t PCAP_RLC_BEARER_TYPE_DRB = 5;

// RLC sequence number length
constexpr uint8_t PCAP_RLC_TM_SN_LENGTH_0_BITS  = 0;
constexpr uint8_t PCAP_RLC_UM_SN_LENGTH_6_BITS  = 6;
constexpr uint8_t PCAP_RLC_UM_SN_LENGTH_12_BITS = 12;
constexpr uint8_t PCAP_RLC_AM_SN_LENGTH_12_BITS = 12;
constexpr uint8_t PCAP_RLC_AM_SN_LENGTH_18_BITS = 18;

pcap_rlc_pdu_context::pcap_rlc_pdu_context(du_ue_index_t ue_index, rb_id_t rb_id, const rlc_tx_am_config& cfg)
{
  rlc_mode  = PCAP_RLC_AM_MODE;
  direction = PCAP_RLC_DIRECTION_DOWNLINK;
  set_sequence_number_length(cfg.sn_field_length);
  set_bearer_info(rb_id);
  ueid = ue_index;
}

pcap_rlc_pdu_context::pcap_rlc_pdu_context(du_ue_index_t ue_index, rb_id_t rb_id, const rlc_rx_am_config& cfg)
{
  rlc_mode  = PCAP_RLC_AM_MODE;
  direction = PCAP_RLC_DIRECTION_UPLINK;
  set_sequence_number_length(cfg.sn_field_length);
  set_bearer_info(rb_id);
  ueid = ue_index;
}

pcap_rlc_pdu_context::pcap_rlc_pdu_context(du_ue_index_t ue_index, rb_id_t rb_id, const rlc_tx_um_config& cfg)
{
  rlc_mode  = PCAP_RLC_UM_MODE;
  direction = PCAP_RLC_DIRECTION_DOWNLINK;
  set_sequence_number_length(cfg.sn_field_length);
  set_bearer_info(rb_id);
  ueid = ue_index;
}

pcap_rlc_pdu_context::pcap_rlc_pdu_context(du_ue_index_t ue_index, rb_id_t rb_id, const rlc_rx_um_config& cfg)
{
  rlc_mode  = PCAP_RLC_UM_MODE;
  direction = PCAP_RLC_DIRECTION_UPLINK;
  set_sequence_number_length(cfg.sn_field_length);
  set_bearer_info(rb_id);
  ueid = ue_index;
}

pcap_rlc_pdu_context::pcap_rlc_pdu_context(du_ue_index_t ue_index, rb_id_t rb_id, bool is_uplink)
{
  rlc_mode               = PCAP_RLC_TM_MODE;
  direction              = is_uplink ? PCAP_RLC_DIRECTION_UPLINK : PCAP_RLC_DIRECTION_DOWNLINK;
  sequence_number_length = PCAP_RLC_TM_SN_LENGTH_0_BITS;
  set_bearer_info(rb_id);
  ueid = ue_index;
}

void pcap_rlc_pdu_context::set_sequence_number_length(rlc_am_sn_size sn_field_length)
{
  switch (sn_field_length) {
    case rlc_am_sn_size::size12bits:
      sequence_number_length = PCAP_RLC_AM_SN_LENGTH_12_BITS;
    case rlc_am_sn_size::size18bits:
      sequence_number_length = PCAP_RLC_AM_SN_LENGTH_18_BITS;
  }
}

void pcap_rlc_pdu_context::set_sequence_number_length(rlc_um_sn_size sn_field_length)
{
  switch (sn_field_length) {
    case rlc_um_sn_size::size6bits:
      sequence_number_length = PCAP_RLC_UM_SN_LENGTH_6_BITS;
    case rlc_um_sn_size::size12bits:
      sequence_number_length = PCAP_RLC_UM_SN_LENGTH_12_BITS;
  }
}

void pcap_rlc_pdu_context::set_bearer_info(rb_id_t rb_id)
{
  if (rb_id.is_drb()) {
    bearer_type = PCAP_RLC_BEARER_TYPE_DRB;
    bearer_id   = drb_id_to_uint(rb_id.get_drb_id());
  } else if (rb_id.is_srb()) {
    bearer_type = PCAP_RLC_BEARER_TYPE_SRB;
    bearer_id   = srb_id_to_uint(rb_id.get_srb_id());
  }
}
