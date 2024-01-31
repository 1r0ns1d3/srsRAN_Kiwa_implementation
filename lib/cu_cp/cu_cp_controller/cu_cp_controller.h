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

#include "amf_connection_manager.h"
#include "node_connection_notifier.h"
#include "srsran/cu_cp/cu_cp_configuration.h"

namespace srsran {
namespace srs_cu_cp {

/// \brief Entity responsible for managing the CU-CP connections to remote nodes and determining whether the CU-CP
/// is in a state to accept new connections.
///
/// In particular, this class is responsible for:
/// - triggering an AMF connection and tracking the status of the connection;
/// - determining whether a new DU setup request should be accepted based on the status of other remote node
/// connections;
/// - determining whether new UEs should be accepted depending on the status of the CU-CP remote connections.
class cu_cp_controller
{
public:
  cu_cp_controller(cu_cp_routine_manager&          routine_manager_,
                   const ngap_configuration&       ngap_cfg_,
                   ngap_cu_cp_connection_notifier& cu_cp_amf_conn_notif_,
                   cu_cp_ngap_control_notifier&    ngap_ctrl_notif_);

  amf_connection_manager& amf_connection_handler() { return amf_mng; }

  bool handle_du_setup_request(const du_setup_request& req);

  /// \brief Determines whether the CU-CP should accept a new UE connection.
  bool request_ue_setup() const;

private:
  amf_connection_manager amf_mng;
};

} // namespace srs_cu_cp
} // namespace srsran