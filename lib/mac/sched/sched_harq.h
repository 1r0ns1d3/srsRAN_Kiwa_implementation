/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2021 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#ifndef SCHED_HARQ_H
#define SCHED_HARQ_H

#include "sched_dci.h"
#include "sched_prb.h"
#include "srsgnb/adt/byte_buffer.h"
#include "srsgnb/ran/slot_point.h"
#include <array>

namespace srsgnb {

class harq_proc
{
public:
  explicit harq_proc(uint32_t id_) : pid(id_) {}

  bool empty() const
  {
    return std::all_of(tb.begin(), tb.end(), [](const tb_t& t) { return not t.active; });
  }
  bool empty(uint32_t tb_idx) const { return not tb[tb_idx].active; }
  bool has_pending_retx(slot_point slot_rx) const
  {
    return not empty() and not tb[0].ack_state and slot_ack <= slot_rx;
  }
  uint32_t         nof_retx() const { return tb[0].n_rtx; }
  uint32_t         max_nof_retx() const { return max_retx; }
  uint32_t         tbs() const { return tb[0].tbs; }
  uint32_t         ndi() const { return tb[0].ndi; }
  uint32_t         mcs() const { return tb[0].mcs; }
  const prb_grant& prbs() const { return prbs_; }
  slot_point       harq_slot_tx() const { return slot_tx; }
  slot_point       harq_slot_ack() const { return slot_ack; }

  int ack_info(uint32_t tb_idx, bool ack);

  bool clear_if_maxretx(slot_point slot_rx);
  void reset();
  bool new_retx(slot_point slot_tx, slot_point slot_ack);

  // NOTE: Has to be used before first tx is dispatched
  bool set_tbs(uint32_t tbs);
  bool set_mcs(uint32_t mcs);

  const uint32_t pid;

protected:
  bool new_tx(slot_point slot_tx, slot_point slot_ack, const prb_grant& grant, uint32_t mcs, uint32_t max_retx);
  bool new_retx(slot_point slot_tx, slot_point slot_ack, const prb_grant& grant);

  struct tb_t {
    bool     active    = false;
    bool     ack_state = false;
    bool     ndi       = false;
    uint32_t n_rtx     = 0;
    uint32_t mcs       = 0;
    uint32_t tbs       = 0;
  };

  uint32_t                     max_retx = 1;
  slot_point                   slot_tx;
  slot_point                   slot_ack;
  prb_grant                    prbs_;
  std::array<tb_t, MAX_NOF_TB> tb;
};

class dl_harq_proc : public harq_proc
{
public:
  dl_harq_proc(uint32_t id_, uint32_t nprb);

  std::vector<uint8_t>& get_softbuffer() { return softbuffer; }
  byte_buffer*          get_tx_pdu() { return &pdu; }

  bool new_tx(slot_point       slot_tx,
              slot_point       slot_ack,
              const prb_grant& grant,
              uint32_t         mcs,
              uint32_t         max_retx,
              dci_dl_t&        dci);

  bool new_retx(slot_point slot_tx, slot_point slot_ack, const prb_grant& grant, dci_dl_t& dci);

private:
  void fill_dci(dci_dl_t& dci);

  std::vector<uint8_t> softbuffer;
  byte_buffer          pdu;
};

class ul_harq_proc : public harq_proc
{
public:
  ul_harq_proc(uint32_t id_, uint32_t nprb) : harq_proc(id_) {}

  bool new_tx(slot_point slot_tx, const prb_grant& grant, uint32_t mcs, uint32_t max_retx, dci_ul_t& dci);

  bool new_retx(slot_point slot_tx, const prb_grant& grant, dci_ul_t& dci);

  std::vector<uint8_t>& get_softbuffer() { return softbuffer; }

  bool set_tbs(uint32_t tbs)
  {
    softbuffer.resize(tbs);
    return harq_proc::set_tbs(tbs);
  }

private:
  void fill_dci(dci_ul_t& dci);

  std::vector<uint8_t> softbuffer;
};

class harq_entity
{
public:
  explicit harq_entity(uint16_t rnti, uint32_t nprb, uint32_t nof_harq_procs, srslog::basic_logger& logger);
  void new_slot(slot_point slot_rx_);

  int dl_ack_info(uint32_t pid, uint32_t tb_idx, bool ack) { return dl_harqs[pid].ack_info(tb_idx, ack); }
  int ul_crc_info(uint32_t pid, bool ack) { return ul_harqs[pid].ack_info(0, ack); }

  uint32_t            nof_dl_harqs() const { return dl_harqs.size(); }
  uint32_t            nof_ul_harqs() const { return ul_harqs.size(); }
  const dl_harq_proc& dl_harq(uint32_t pid) const { return dl_harqs[pid]; }
  const ul_harq_proc& ul_harq(uint32_t pid) const { return ul_harqs[pid]; }

  dl_harq_proc* find_pending_dl_retx()
  {
    return find_dl([this](const dl_harq_proc& h) { return h.has_pending_retx(slot_rx); });
  }
  ul_harq_proc* find_pending_ul_retx()
  {
    return find_ul([this](const ul_harq_proc& h) { return h.has_pending_retx(slot_rx); });
  }
  dl_harq_proc* find_empty_dl_harq()
  {
    return find_dl([](const dl_harq_proc& h) { return h.empty(); });
  }
  ul_harq_proc* find_empty_ul_harq()
  {
    return find_ul([](const ul_harq_proc& h) { return h.empty(); });
  }

private:
  template <typename Predicate>
  dl_harq_proc* find_dl(Predicate p)
  {
    auto it = std::find_if(dl_harqs.begin(), dl_harqs.end(), p);
    return (it == dl_harqs.end()) ? nullptr : &(*it);
  }
  template <typename Predicate>
  ul_harq_proc* find_ul(Predicate p)
  {
    auto it = std::find_if(ul_harqs.begin(), ul_harqs.end(), p);
    return (it == ul_harqs.end()) ? nullptr : &(*it);
  }

  uint16_t              rnti;
  srslog::basic_logger& logger;

  slot_point                slot_rx;
  std::vector<dl_harq_proc> dl_harqs;
  std::vector<ul_harq_proc> ul_harqs;
};

} // namespace srsgnb

#endif // SCHED_HARQ_H
