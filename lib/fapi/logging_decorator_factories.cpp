/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/fapi/logging_decorator_factories.h"
#include "logging_slot_data_notifier_decorator.h"
#include "logging_slot_error_notifier_decorator.h"
#include "logging_slot_gateway_decorator.h"
#include "logging_slot_time_notifier_decorator.h"
#include "srsran/srslog/srslog.h"

using namespace srsran;
using namespace fapi;

std::unique_ptr<slot_message_gateway> srsran::fapi::create_logging_slot_gateway(slot_message_gateway& gateway)
{
  srslog::basic_logger& logger = srslog::fetch_basic_logger("FAPI", true);
  logger.set_level(srslog::basic_levels::debug);

  return std::make_unique<logging_slot_gateway_decorator>(logger, gateway);
}

std::unique_ptr<slot_time_message_notifier>
srsran::fapi::create_logging_slot_time_notifier(slot_time_message_notifier& notifier)
{
  srslog::basic_logger& logger = srslog::fetch_basic_logger("FAPI", true);
  logger.set_level(srslog::basic_levels::debug);

  return std::make_unique<logging_slot_time_notifier_decorator>(logger, notifier);
}

std::unique_ptr<slot_error_message_notifier>
srsran::fapi::create_logging_slot_error_notifier(slot_error_message_notifier& notifier)
{
  srslog::basic_logger& logger = srslog::fetch_basic_logger("FAPI", true);
  logger.set_level(srslog::basic_levels::debug);

  return std::make_unique<logging_slot_error_notifier_decorator>(logger, notifier);
}

std::unique_ptr<slot_data_message_notifier>
srsran::fapi::create_logging_slot_data_notifier(slot_data_message_notifier& notifier)
{
  srslog::basic_logger& logger = srslog::fetch_basic_logger("FAPI", true);
  logger.set_level(srslog::basic_levels::debug);

  return std::make_unique<logging_slot_data_notifier_decorator>(logger, notifier);
}
