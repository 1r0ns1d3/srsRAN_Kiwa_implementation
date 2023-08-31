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

#include "srsran/phy/upper/channel_processors/pusch/pusch_codeword_buffer.h"
#include "srsran/phy/upper/channel_processors/pusch/ulsch_demultiplex.h"
#include "srsran/ran/pusch/pusch_constants.h"

namespace srsran {

class ulsch_demultiplex_impl : public ulsch_demultiplex, private pusch_codeword_buffer
{
public:
  /// Resource element set type.
  using re_set_type = bounded_bitset<MAX_RB * NRE>;

  // See interface for documentation.
  void
  set_csi_part2(pusch_decoder_buffer& csi_part2, unsigned nof_csi_part2_bits, unsigned nof_csi_part2_enc_bits) override;

  // See interface for documentation.
  pusch_codeword_buffer& demultiplex(pusch_decoder_buffer& sch_data,
                                     pusch_decoder_buffer& harq_ack,
                                     pusch_decoder_buffer& csi_part1,
                                     const configuration&  config) override;

private:
  // See pusch_codeword_buffer for documentation.
  span<log_likelihood_ratio> get_next_block_view(unsigned block_size) override;

  // See pusch_codeword_buffer for documentation.
  void on_new_block(span<const log_likelihood_ratio> demodulated,
                    span<const log_likelihood_ratio> descrambled) override;

  // See pusch_codeword_buffer for documentation.
  void on_end_codeword() override;

  pusch_decoder_buffer* sch_data  = nullptr;
  pusch_decoder_buffer* harq_ack  = nullptr;
  pusch_decoder_buffer* csi_part1 = nullptr;
  pusch_decoder_buffer* csi_part2 = nullptr;

  /// Configures the current OFDM symbol.
  void configure_current_ofdm_symbol();

  /// Configures CSI Part 2 for the current OFDM symbol.
  void configure_csi_part2_current_ofdm_symbol();

  /// Demultiplexes the current OFDM symbol.
  void demux_current_ofdm_symbol();

  /// Transmission configuration.
  configuration config;
  /// Number of CSI Part 2 information bits multiplexed in the PUSCH message. Parameter \f$O_\textup{CSI-2}\f$.
  unsigned nof_csi_part2_bits;
  /// Number of encoded and rate-matched CSI Part 2 data bits. Parameter \f$G^\textup{CSI-2}\f$.
  unsigned nof_csi_part2_enc_bits;
  /// Number of bits per resource element.
  unsigned nof_bits_per_re;
  /// OFDM symbol index of the first OFDM symbol after the first set of consecutive OFDM symbol(s) carrying DM-RS in the
  /// first hop.
  unsigned l1;
  /// OFDM symbol index of the first OFDM symbol that does not carry DM-RS in the first hop.
  unsigned l1_csi;
  /// Number of UL-SCH REs in OFDM symbols containing DM-RS.
  unsigned nof_re_dmrs;
  /// Count the number of reserved bits.
  unsigned m_rvd_count;
  /// Count the number of HARQ-ACK bits.
  unsigned m_harq_ack_count;
  /// Count the number of CSI Part1 bits.
  unsigned m_csi_part1_count;
  /// Count the number of CSI Part2 bits.
  unsigned m_csi_part2_count;
  /// Current OFDM symbol index.
  unsigned ofdm_symbol_index;
  /// Number of softbits available for UL-SCH in the current OFDM symbol.
  unsigned nof_softbits;
  /// Keeps count of softbits in \c temp_softbit_buffer.
  unsigned softbit_count;
  /// Parameter \f$\Phi^\textup{UL-SCH}_\textup{l}\f$. Set of resource elements available for transmission of data in
  /// the OFDM symbol \f$l\f$.
  re_set_type ulsch_re_set;
  /// Parameter \f$\Phi^\textup{UCI}_\textup{l}\f$. Set of resource elements available for transmission of UCI in the
  /// OFDM symbol \f$l\f$.
  re_set_type uci_re_set;
  /// Parameter \f$\Phi^\textup{rvd}_\textup{l}\f$. Set of reserved resource elements for potential HARQ-ACK
  /// transmission.
  re_set_type rvd_re_set;
  /// Set of resource elements for HARQ-ACK transmission.
  re_set_type harq_ack_re_set;
  /// Set of resource elements for CSI Part 1 transmission.
  re_set_type csi_part1_re_set;
  /// Set of resource elements for CSI Part 2 transmission.
  re_set_type csi_part2_re_set;
  /// Demodulated soft bits buffer for an entire OFDM symbol.
  std::array<log_likelihood_ratio, MAX_RB * NRE * pusch_constants::MAX_MODULATION_ORDER> temp_demodulated_buffer;
  /// Descrambled soft bits buffer for an entire OFDM symbol.
  std::array<log_likelihood_ratio, MAX_RB * NRE * pusch_constants::MAX_MODULATION_ORDER> temp_descrambled_buffer;
};

} // namespace srsran
