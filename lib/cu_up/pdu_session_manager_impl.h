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

#include "pdu_session.h"
#include "pdu_session_manager.h"
#include "srsran/cu_up/cu_up_configuration.h"
#include "srsran/cu_up/cu_up_types.h"
#include "srsran/e1ap/common/e1ap_types.h"
#include "srsran/f1u/cu_up/f1u_gateway.h"
#include "srsran/gtpu/gtpu_demux.h"
#include "srsran/gtpu/gtpu_tunnel_tx.h"
#include "srsran/support/timers.h"
#include <map>

namespace srsran {

namespace srs_cu_up {

class pdu_session_manager_impl final : public pdu_session_manager_ctrl
{
public:
  pdu_session_manager_impl(ue_index_t                           ue_index_,
                           network_interface_config&            net_config_,
                           srslog::basic_logger&                logger_,
                           unique_timer&                        ue_inactivity_timer,
                           timer_factory                        timers_,
                           f1u_cu_up_gateway&                   f1u_gw_,
                           gtpu_tunnel_tx_upper_layer_notifier& gtpu_tx_notifier_,
                           gtpu_demux_ctrl&                     gtpu_rx_demux_);

  pdu_session_setup_result        setup_pdu_session(const e1ap_pdu_session_res_to_setup_item& session) override;
  pdu_session_modification_result modify_pdu_session(const e1ap_pdu_session_res_to_modify_item& session) override;
  void                            remove_pdu_session(pdu_session_id_t pdu_session_id) override;
  size_t                          get_nof_pdu_sessions() override;

private:
  uint32_t allocate_local_teid(pdu_session_id_t pdu_session_id);
  uint32_t allocate_local_f1u_teid(pdu_session_id_t pdu_session_id, drb_id_t drb_id);

  drb_setup_result handle_drb_to_setup_item(pdu_session&                         new_session,
                                            const e1ap_drb_to_setup_item_ng_ran& drb_to_setup);

  ue_index_t                                               ue_index;
  network_interface_config&                                net_config;
  srslog::basic_logger&                                    logger;
  unique_timer&                                            ue_inactivity_timer;
  timer_factory                                            timers;
  gtpu_tunnel_tx_upper_layer_notifier&                     gtpu_tx_notifier;
  gtpu_demux_ctrl&                                         gtpu_rx_demux;
  f1u_cu_up_gateway&                                       f1u_gw;
  std::map<pdu_session_id_t, std::unique_ptr<pdu_session>> pdu_sessions; // key is pdu_session_id
};

} // namespace srs_cu_up

} // namespace srsran
