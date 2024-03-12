/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/fapi/message_builders.h"
#include <gtest/gtest.h>

using namespace srsran;
using namespace fapi;

TEST(dl_csi_pdu_builder, valid_basic_parameters_passes)
{
  dl_csi_rs_pdu         pdu;
  dl_csi_rs_pdu_builder builder(pdu);

  unsigned                  start_rb     = 200;
  unsigned                  nof_rb       = 150;
  csi_rs_type               type         = csi_rs_type::CSI_RS_ZP;
  unsigned                  row          = 10;
  bounded_bitset<12, false> freq_domain  = {0, 0, 1};
  unsigned                  sym_l0       = 2;
  unsigned                  sym_l1       = 3;
  csi_rs_cdm_type           cdm          = csi_rs_cdm_type::cdm8_FD2_TD4;
  csi_rs_freq_density_type  freq_density = csi_rs_freq_density_type::one;
  unsigned                  scram_id     = 523;

  builder.set_basic_parameters(start_rb, nof_rb, type, row, freq_domain, sym_l0, sym_l1, cdm, freq_density, scram_id);

  ASSERT_EQ(start_rb, pdu.start_rb);
  ASSERT_EQ(nof_rb, pdu.num_rbs);
  ASSERT_EQ(type, pdu.type);
  ASSERT_EQ(row, pdu.row);
  ASSERT_EQ(freq_domain, pdu.freq_domain);
  ASSERT_EQ(sym_l0, pdu.symb_L0);
  ASSERT_EQ(sym_l1, pdu.symb_L1);
  ASSERT_EQ(cdm, pdu.cdm_type);
  ASSERT_EQ(freq_density, pdu.freq_density);
  ASSERT_EQ(scram_id, pdu.scramb_id);
}

TEST(dl_csi_pdu_builder, valid_bwp_parameters_passes)
{
  dl_csi_rs_pdu         pdu;
  dl_csi_rs_pdu_builder builder(pdu);

  subcarrier_spacing scs      = subcarrier_spacing::kHz60;
  cyclic_prefix      cyclic_p = cyclic_prefix::NORMAL;

  builder.set_bwp_parameters(scs, cyclic_p);

  ASSERT_EQ(scs, pdu.scs);
  ASSERT_EQ(cyclic_p, pdu.cp);
}

TEST(dl_csi_pdu_builder, valid_tx_power_info_parameters_passes)
{
  for (auto power : {0, -8}) {
    dl_csi_rs_pdu         pdu;
    dl_csi_rs_pdu_builder builder(pdu);

    power_control_offset_ss ss = power_control_offset_ss::dB3;

    builder.set_tx_power_info_parameters(power, ss);

    ASSERT_EQ(ss, pdu.power_control_offset_ss_profile_nr);
    ASSERT_EQ(power, pdu.power_control_offset_profile_nr);
  }
}
