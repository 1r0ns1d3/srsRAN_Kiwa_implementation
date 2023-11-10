/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ofh_receiver_impl.h"
#include "srsran/ofh/ethernet/ethernet_properties.h"

using namespace srsran;
using namespace ofh;

static message_receiver_config get_message_receiver_configuration(const receiver_config& rx_config)
{
  message_receiver_config config;

  config.vlan_params.mac_src_address = rx_config.mac_src_address;
  config.vlan_params.mac_dst_address = rx_config.mac_dst_address;
  config.vlan_params.tci             = rx_config.tci;
  config.vlan_params.eth_type        = ether::ECPRI_ETH_TYPE;

  config.prach_eaxc = rx_config.prach_eaxc;
  config.ul_eaxc    = rx_config.ul_eaxc;

  return config;
}

static message_receiver_dependencies get_message_receiver_dependencies(receiver_impl_dependencies&& rx_dependencies,
                                                                       rx_window_checker&           window_checker)
{
  message_receiver_dependencies dependencies;

  dependencies.logger         = rx_dependencies.logger;
  dependencies.window_checker = &window_checker;
  dependencies.ecpri_decoder  = std::move(rx_dependencies.ecpri_decoder);
  srsran_assert(dependencies.ecpri_decoder, "Invalid eCPRI decoder");
  dependencies.eth_frame_decoder = std::move(rx_dependencies.eth_frame_decoder);
  srsran_assert(dependencies.eth_frame_decoder, "Invalid Ethernet frame decoder");
  dependencies.uplane_decoder = std::move(rx_dependencies.uplane_decoder);
  srsran_assert(dependencies.uplane_decoder, "Invalid Open Fronthaul User-Plane decoder");
  dependencies.data_flow_uplink = std::move(rx_dependencies.data_flow_uplink);
  srsran_assert(dependencies.data_flow_uplink, "Invalid uplink data flow decoder");
  dependencies.data_flow_prach = std::move(rx_dependencies.data_flow_prach);
  srsran_assert(dependencies.data_flow_prach, "Invalid PRACH data flow decoder");

  return dependencies;
}

receiver_impl::receiver_impl(const receiver_config& config, receiver_impl_dependencies&& dependencies) :
  window_checker(*dependencies.logger,
                 config.rx_timing_params,
                 std::chrono::duration<double, std::nano>(
                     1e6 / (get_nsymb_per_slot(config.cp) * get_nof_slots_per_subframe(config.scs)))),
  msg_receiver(get_message_receiver_configuration(config),
               get_message_receiver_dependencies(std::move(dependencies), window_checker)),
  ctrl(msg_receiver)
{
}

ether::frame_notifier& receiver_impl::get_ethernet_frame_notifier()
{
  return msg_receiver;
}

ota_symbol_handler& receiver_impl::get_ota_symbol_handler()
{
  return window_checker;
}

controller& receiver_impl::get_controller()
{
  return ctrl;
}
