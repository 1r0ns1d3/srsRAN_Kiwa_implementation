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

#include "srsran/f1ap/du/f1ap_du_ue_context_update.h"
#include "srsran/ran/up_transport_layer_info.h"

namespace srsran {
namespace srs_du {

/// \brief Creates a \c srb_id_t from ASN.1 type.
///
/// This function is used by the following procedures:
/// - f1ap_du_ue_context_setup_procedure
/// - f1ap_du_ue_context_modification_procedure
///
/// \param srb_item ASN.1 item with SRB-specific parameters to be setup.
/// \return srb_id_t object.
template <typename Asn1Type>
srb_id_t make_srb_id(const Asn1Type& srb_item)
{
  return static_cast<srb_id_t>(srb_item.srb_id);
}

/// \brief Creates a \c f1ap_drb_to_setup from ASN.1 type.
///
/// This function is used by the following procedures:
/// - f1ap_du_ue_context_setup_procedure
/// - f1ap_du_ue_context_modification_procedure
///
/// \param drb_item ASN.1 item with DRB-specific parameters to be setup.
/// \return f1ap_drb_to_setup object.
template <typename Asn1Type>
f1ap_drb_to_setup make_drb_to_setup(const Asn1Type& drb_item)
{
  f1ap_drb_to_setup drb_obj;

  drb_obj.drb_id  = static_cast<drb_id_t>(drb_item.drb_id);
  drb_obj.mode    = static_cast<drb_rlc_mode>(static_cast<unsigned>(drb_item.rlc_mode));
  drb_obj.five_qi = uint_to_five_qi(
      drb_item.qos_info.choice_ext().value().drb_info().drb_qos.qos_characteristics.non_dyn_5qi().five_qi);
  drb_obj.uluptnl_info_list.reserve(drb_item.ul_up_tnl_info_to_be_setup_list.size());
  for (const auto& tnl_info : drb_item.ul_up_tnl_info_to_be_setup_list) {
    drb_obj.uluptnl_info_list.push_back(asn1_to_up_transport_layer_info(tnl_info.ul_up_tnl_info));
  }

  // TODO: Handle Dynamic 5QI.
  drb_obj.five_qi = uint_to_five_qi(
      drb_item.qos_info.choice_ext().value().drb_info().drb_qos.qos_characteristics.non_dyn_5qi().five_qi);
  drb_obj.arp_priority_level =
      drb_item.qos_info.choice_ext().value().drb_info().drb_qos.ngra_nalloc_retention_prio.prio_level;
  // TODO: Do not populate gbr_flow_info for non-GBR flows.
  if (drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info_present) {
    drb_obj.gbr_flow_info.emplace();
    drb_obj.gbr_flow_info.value().max_flow_dl_bitrate =
        drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.max_flow_bit_rate_dl;
    drb_obj.gbr_flow_info.value().max_flow_ul_bitrate =
        drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.max_flow_bit_rate_ul;
    drb_obj.gbr_flow_info.value().guaranteed_flow_dl_bitrate =
        drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.guaranteed_flow_bit_rate_dl;
    drb_obj.gbr_flow_info.value().guaranteed_flow_ul_bitrate =
        drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.guaranteed_flow_bit_rate_ul;
    if (drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.max_packet_loss_rate_dl_present) {
      drb_obj.gbr_flow_info.value().max_packet_loss_rate_dl.emplace(
          drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.max_packet_loss_rate_dl);
    }
    if (drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.max_packet_loss_rate_ul_present) {
      drb_obj.gbr_flow_info.value().max_packet_loss_rate_dl.emplace(
          drb_item.qos_info.choice_ext().value().drb_info().drb_qos.gbr_qos_flow_info.max_packet_loss_rate_ul);
    }
  }
  return drb_obj;
}

/// \brief Creates a \c drb_id_t from ASN.1 type.
///
/// This function is used by the following procedures:
/// - f1ap_du_ue_context_modification_procedure
///
/// \param drb_item ASN.1 item with DRB-specific parameters to be removed.
/// \return drb_id_t object.
template <typename Asn1Type>
drb_id_t make_drb_id(const Asn1Type& drb_item)
{
  return static_cast<drb_id_t>(drb_item.drb_id);
}

} // namespace srs_du
} // namespace srsran
