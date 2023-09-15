/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "e2_entity.h"
#include "../e2sm/e2sm_kpm/e2sm_kpm_asn1_packer.h"
#include "../e2sm/e2sm_kpm/e2sm_kpm_impl.h"
#include "e2_impl.h"
#include "e2_subscription_manager_impl.h"
#include "e2sm/e2sm_kpm/e2sm_kpm_du_meas_provider_impl.h"
#include "srsran/asn1/e2ap/e2ap.h"
#include "srsran/e2/e2.h"
#include <memory>

using namespace srsran;
using namespace asn1::e2ap;

e2_entity::e2_entity(e2ap_configuration&           cfg_,
                     std::unique_ptr<e2_interface> decorated_e2_iface_,
                     task_executor&                task_exec_) :
  logger(srslog::fetch_basic_logger("E2")), cfg(cfg_), task_exec(task_exec_), main_ctrl_loop(128)
{
  decorated_e2_iface = std::move(decorated_e2_iface_);
}

e2_entity::e2_entity(e2ap_configuration&      cfg_,
                     e2_connection_client*    e2_client_,
                     e2_du_metrics_interface& e2_du_metrics_iface_,
                     timer_factory            timers_,
                     task_executor&           task_exec_) :
  logger(srslog::fetch_basic_logger("E2AP")), cfg(cfg_), task_exec(task_exec_), main_ctrl_loop(128)
{
  e2_pdu_notifier   = e2_client_->handle_connection_request();
  e2sm_mngr         = std::make_unique<e2sm_manager>(logger);
  subscription_mngr = std::make_unique<e2_subscription_manager_impl>(*e2_pdu_notifier, *e2sm_mngr);

  if (cfg.e2sm_kpm_enabled) {
    auto e2sm_kpm_meas_provider = std::make_unique<e2sm_kpm_du_meas_provider_impl>();
    auto e2sm_packer            = std::make_unique<e2sm_kpm_asn1_packer>(*e2sm_kpm_meas_provider);
    auto e2sm_iface             = std::make_unique<e2sm_kpm_impl>(logger, *e2sm_packer, *e2sm_kpm_meas_provider);
    e2sm_handlers.push_back(std::move(e2sm_packer));
    e2sm_mngr->add_e2sm_service(e2sm_kpm_asn1_packer::oid, std::move(e2sm_iface));
    subscription_mngr->add_ran_function_oid(e2sm_kpm_asn1_packer::ran_func_id, e2sm_kpm_asn1_packer::oid);
    e2_du_metrics_iface_.connect_e2_du_meas_provider(std::move(e2sm_kpm_meas_provider));
  }

  decorated_e2_iface = std::make_unique<e2_impl>(cfg_, timers_, *e2_pdu_notifier, *subscription_mngr, *e2sm_mngr);
  e2_client_->connect_e2ap(e2_pdu_notifier.get(), this, this);
}

void e2_entity::start()
{
  if (not task_exec.execute([this]() {
        main_ctrl_loop.schedule([this](coro_context<async_task<void>>& ctx) {
          CORO_BEGIN(ctx);

          // Send E2AP Setup Request and await for E2AP setup response.
          CORO_AWAIT(decorated_e2_iface->start_initial_e2_setup_routine());

          CORO_RETURN();
        });
      })) {
    report_fatal_error("Unable to initiate E2AP setup procedure");
  }
}

void e2_entity::stop()
{
  // placeholder_
}

async_task<e2_setup_response_message> e2_entity::handle_e2_setup_request(e2_setup_request_message& request)
{
  return decorated_e2_iface->handle_e2_setup_request(request);
}

async_task<e2_setup_response_message> e2_entity::start_initial_e2_setup_routine()
{
  return decorated_e2_iface->start_initial_e2_setup_routine();
}

void e2_entity::handle_connection_loss()
{
  task_exec.execute([this]() { decorated_e2_iface->handle_connection_loss(); });
}

void e2_entity::handle_message(const e2_message& msg)
{
  task_exec.execute([this, msg]() { decorated_e2_iface->handle_message(msg); });
}
