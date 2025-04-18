#
# Copyright 2021-2025 Software Radio Systems Limited
#
# This file is part of srsRAN
#
# srsRAN is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# srsRAN is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# A copy of the GNU Affero General Public License can be found in
# the LICENSE file in the top-level directory of this distribution
# and at http://www.gnu.org/licenses/.
#

set(SOURCES
        logging_decorator_impl.cpp
        logging_slot_data_notifier_decorator.cpp
        logging_slot_error_notifier_decorator.cpp
        logging_slot_gateway_decorator.cpp
        logging_slot_time_notifier_decorator.cpp
        message_loggers.cpp)

add_library(srsran_fapi_loggers STATIC ${SOURCES})
target_include_directories(srsran_fapi_loggers PRIVATE ${CMAKE_SOURCE_DIR}/lib/fapi)
target_link_libraries(srsran_fapi_loggers srslog srsran_fapi_decorator_helpers)
