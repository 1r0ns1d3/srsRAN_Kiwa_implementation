/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "gtpu_test_shared.h"
#include "srsran/gtpu/gtpu_demux.h"
#include "srsran/gtpu/gtpu_demux_factory.h"
#include "srsran/support/executors/manual_task_worker.h"
#include "srsran/support/executors/task_worker.h"
#include <gtest/gtest.h>
#include <sys/socket.h>

using namespace srsran;

class gtpu_tunnel_rx_upper_dummy : public gtpu_tunnel_rx_upper_layer_interface
{
public:
  void handle_pdu(byte_buffer pdu, const sockaddr_storage& src_addr) final { last_rx = std::move(pdu); }

  byte_buffer last_rx;
};

/// Fixture class for GTPU demux tests
class gtpu_demux_test : public ::testing::Test
{
protected:
  void SetUp() override
  {
    srslog::fetch_basic_logger("TEST").set_level(srslog::basic_levels::debug);
    srslog::init();

    gtpu_tunnel = std::make_unique<gtpu_tunnel_rx_upper_dummy>();

    // create DUT object
    gtpu_demux_creation_request msg = {};
    msg.gtpu_pcap                   = &dummy_pcap;
    dut                             = create_gtpu_demux(msg);
  }

  void TearDown() override
  {
    // flush logger after each test
    srslog::flush();
  }

  std::unique_ptr<gtpu_tunnel_rx_upper_dummy> gtpu_tunnel;
  manual_task_worker                          teid_worker{128};

  task_worker          worker{"GTP-U demux#0", 128};
  task_worker_executor exec{worker};
  null_dlt_pcap        dummy_pcap;

  std::unique_ptr<gtpu_demux> dut;
  srslog::basic_logger&       test_logger = srslog::fetch_basic_logger("TEST", false);
};

//// GTPU demux tesst
TEST_F(gtpu_demux_test, when_tunnel_not_registered_pdu_is_dropped)
{
  sockaddr_storage src_addr = {};
  byte_buffer      pdu{gtpu_ping_vec_teid_1};

  dut->handle_pdu(std::move(pdu), src_addr);
  worker.wait_pending_tasks();

  ASSERT_EQ(gtpu_tunnel->last_rx.length(), 0);
}

TEST_F(gtpu_demux_test, when_tunnel_registered_pdu_is_forwarded)
{
  sockaddr_storage src_addr = {};
  byte_buffer      pdu{gtpu_ping_vec_teid_1};
  dut->add_tunnel(gtpu_teid_t{0x1}, teid_worker, gtpu_tunnel.get());

  dut->handle_pdu(std::move(pdu), src_addr);
  worker.wait_pending_tasks();

  ASSERT_EQ(gtpu_tunnel->last_rx.length(), sizeof(gtpu_ping_vec_teid_1));
}

TEST_F(gtpu_demux_test, when_tunnel_is_removed_pdu_is_dropped)
{
  sockaddr_storage src_addr = {};
  byte_buffer      pdu{gtpu_ping_vec_teid_1};
  dut->add_tunnel(gtpu_teid_t{0x1}, teid_worker, gtpu_tunnel.get());
  dut->remove_tunnel(gtpu_teid_t{0x1});

  dut->handle_pdu(std::move(pdu), src_addr);
  worker.wait_pending_tasks();

  ASSERT_EQ(gtpu_tunnel->last_rx.length(), 0);
}

TEST_F(gtpu_demux_test, when_different_tunnel_registered_pdu_is_dropped)
{
  sockaddr_storage src_addr = {};
  byte_buffer      pdu{gtpu_ping_vec_teid_2};
  dut->add_tunnel(gtpu_teid_t{0x1}, teid_worker, gtpu_tunnel.get());

  dut->handle_pdu(std::move(pdu), src_addr);
  worker.wait_pending_tasks();

  ASSERT_EQ(gtpu_tunnel->last_rx.length(), 0);
}
