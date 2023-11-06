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

#include "srsran/fapi/messages.h"
#include "srsran/fapi_adaptor/phy/phy_fapi_adaptor.h"
#include "srsran/fapi_adaptor/precoding_matrix_repository.h"
#include "srsran/phy/upper/tx_buffer_pool.h"
#include "srsran/ran/subcarrier_spacing.h"
#include "srsran/support/executors/task_executor.h"
#include <memory>

namespace srsran {

class downlink_pdu_validator;
class downlink_processor_pool;
class resource_grid_pool;
class uplink_pdu_validator;
class uplink_request_processor;
class uplink_slot_pdu_repository;

namespace fapi_adaptor {

/// Configuration parameters for the PHY&ndash;FAPI adaptor factory.
struct phy_fapi_adaptor_factory_config {
  /// Base station sector identifier.
  unsigned sector_id;
  /// Subcarrier spacing as per TS38.211 Section 4.2.
  subcarrier_spacing scs;
  /// Common subcarrier spacing as per TS38.331 Section 6.2.2.
  subcarrier_spacing scs_common;
  /// PRACH configuration as per SCF-222 v4.0 Section 3.3.2.4 TLV 0x1031.
  fapi::prach_config prach_cfg;
  /// Carrier configuration per SCF-222 v4.0 Section 3.3.2.4 TLV 0x102d.
  fapi::carrier_config carrier_cfg;
  /// Precoding matrix repository.
  std::unique_ptr<precoding_matrix_repository> pm_repo;
  /// Asynchronous task executor.
  task_executor* async_executor;
  /// Transmit buffer pool.
  tx_buffer_pool* buffer_pool;
  /// PRACH port list.
  std::vector<uint8_t> prach_ports;
};

/// Factory to create \c phy_fapi_adaptor objects.
class phy_fapi_adaptor_factory
{
public:
  virtual ~phy_fapi_adaptor_factory() = default;

  /// Creates a \c phy_fapi_adaptor object using the given configuration.
  virtual std::unique_ptr<phy_fapi_adaptor> create(phy_fapi_adaptor_factory_config&& config) = 0;
};

/// Creates a \c phy_fapi_adaptor_factory object.
std::unique_ptr<phy_fapi_adaptor_factory>
create_phy_fapi_adaptor_factory(downlink_processor_pool&      dl_processor_pool,
                                resource_grid_pool&           rg_pool,
                                uplink_request_processor&     ul_request_processor,
                                resource_grid_pool&           ul_rg_pool,
                                uplink_slot_pdu_repository&   ul_pdu_repository,
                                const downlink_pdu_validator& dl_pdu_validator,
                                const uplink_pdu_validator&   ul_pdu_validator);

} // namespace fapi_adaptor
} // namespace srsran
