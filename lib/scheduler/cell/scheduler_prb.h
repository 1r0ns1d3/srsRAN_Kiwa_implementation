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

#include "../support/rb_helper.h"
#include "srsran/adt/bounded_bitset.h"
#include "srsran/adt/interval.h"
#include "srsran/scheduler/rb_alloc.h"

namespace srsran {

struct bwp_rb_bitmap {
public:
  bwp_rb_bitmap() = default;
  bwp_rb_bitmap(uint32_t bwp_nof_prbs, uint32_t bwp_prb_start_, bool config1_or_2);

  void reset()
  {
    prbs_.reset();
    rbgs_.reset();
  }

  template <typename T>
  void operator|=(const T& grant)
  {
    add(grant);
  }

  void add(const prb_interval& prbs)
  {
    prbs_.fill(prbs.start(), prbs.stop());
    add_prbs_to_rbgs(prbs);
  }
  void add(const prb_bitmap& grant)
  {
    prbs_ |= grant;
    add_prbs_to_rbgs(grant);
  }
  void add(const rbg_bitmap& grant)
  {
    rbgs_ |= grant;
    add_rbgs_to_prbs(grant);
  }
  void add(const rb_alloc& grant)
  {
    if (grant.is_type0()) {
      add(grant.type0());
    } else {
      add(grant.type1());
    }
  }
  bool collides(const rb_alloc& grant) const
  {
    if (grant.is_type0()) {
      return (rbgs() & grant.type0()).any();
    }
    return prbs().any(grant.type1().start(), grant.type1().stop());
  }
  bool test(uint32_t prb_idx) { return prbs().test(prb_idx); }
  void set(uint32_t prb_idx)
  {
    prbs_.set(prb_idx);
    rbgs_.set(prb_to_rbg_idx(prb_idx));
  }

  const prb_bitmap& prbs() const { return prbs_; }
  const rbg_bitmap& rbgs() const { return rbgs_; }
  uint32_t          P() const { return to_nominal_rbg_size_value(P_); }
  uint32_t          nof_prbs() const { return prbs_.size(); }
  uint32_t          nof_rbgs() const { return rbgs_.size(); }

  uint32_t prb_to_rbg_idx(uint32_t prb_idx) const;

  bwp_rb_bitmap& operator|=(const bwp_rb_bitmap& other)
  {
    prbs_ |= other.prbs_;
    rbgs_ |= other.rbgs_;
    return *this;
  }
  bwp_rb_bitmap& operator|=(const rbg_bitmap& other)
  {
    add(other);
    return *this;
  }
  bwp_rb_bitmap& operator|=(const prb_bitmap& other)
  {
    add(other);
    return *this;
  }

private:
  prb_bitmap       prbs_;
  rbg_bitmap       rbgs_;
  nominal_rbg_size P_;
  uint32_t         Pnofbits       = 0;
  uint32_t         first_rbg_size = 0;

  void add_prbs_to_rbgs(const prb_bitmap& grant);
  void add_prbs_to_rbgs(const prb_interval& grant);
  void add_rbgs_to_prbs(const rbg_bitmap& grant);
};

template <typename Other>
bwp_rb_bitmap operator|(const bwp_rb_bitmap& lhs, const Other& rhs)
{
  return bwp_rb_bitmap(lhs) |= rhs;
}

} // namespace srsran
