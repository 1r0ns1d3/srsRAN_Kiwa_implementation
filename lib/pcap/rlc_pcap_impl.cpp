/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "rlc_pcap_impl.h"
#include <linux/udp.h>
#include <netinet/in.h>
#include <sys/time.h>

using namespace srsran;

// PCAP tags as defined in Wireshark's "packet-rlc-nr.h"
constexpr const char* PCAP_RLC_NR_START_STRING    = "rlc-nr";
constexpr uint8_t     PCAP_RLC_NR_PAYLOAD_TAG     = 0x01;
constexpr uint8_t     PCAP_RLC_NR_DIRECTION_TAG   = 0x02;
constexpr uint8_t     PCAP_RLC_NR_UEID_TAG        = 0x03;
constexpr uint8_t     PCAP_RLC_NR_BEARER_TYPE_TAG = 0x04;
constexpr uint8_t     PCAP_RLC_NR_BEARER_ID_TAG   = 0x05;

// Other constants
constexpr uint16_t UDP_DLT = 149;

constexpr uint32_t pcap_rlc_max_pdu_len = 131072;

int nr_pcap_pack_rlc_context_to_buffer(const pcap_rlc_pdu_context& context, uint8_t* buffer, unsigned int length);

rlc_pcap_impl::rlc_pcap_impl(const std::string& filename,
                             bool               capture_srb,
                             bool               capture_drb,
                             task_executor&     backend_exec) :
  srb_enabled(capture_srb), drb_enabled(capture_drb), writer(UDP_DLT, "RLC", filename, backend_exec)
{
  tmp_mem.resize(pcap_rlc_max_pdu_len);
}

rlc_pcap_impl::~rlc_pcap_impl()
{
  close();
}

void rlc_pcap_impl::close()
{
  writer.close();
}

void rlc_pcap_impl::push_pdu(const pcap_rlc_pdu_context& context, const byte_buffer_chain& pdu)
{
  if (!is_write_enabled() || pdu.empty()) {
    // skip
    return;
  }

  // Filter DRBs if disabled
  if (!drb_enabled && context.bearer_type == PCAP_RLC_BEARER_TYPE_DRB) {
    return;
  }

  // Filter SRBs if disabled
  if (!srb_enabled &&
      (context.bearer_type == PCAP_RLC_BEARER_TYPE_SRB || context.bearer_type == PCAP_RLC_BEARER_TYPE_CCCH)) {
    return;
  }

  byte_buffer buffer;
  buffer.append(pdu.begin(), pdu.end()); // TODO: optimize copy
  writer.dispatch([this, pdu = std::move(buffer), context](pcap_file_base& file) { write_pdu(file, context, pdu); });
  if (!is_write_enabled() || pdu.empty()) {
    // skip
    return;
  }
}

void rlc_pcap_impl::push_pdu(const pcap_rlc_pdu_context& context, const byte_buffer_slice& pdu)
{
  push_pdu(context, byte_buffer_chain{pdu.copy()});
}

void rlc_pcap_impl::write_pdu(pcap_file_base& file, const pcap_rlc_pdu_context& context, const byte_buffer& buf)
{
  if (buf.length() > pcap_rlc_max_pdu_len) {
    srslog::fetch_basic_logger("ALL").warning(
        "Dropped RLC PCAP PDU. PDU is too big. pdu_len={} max_size={}", buf.length(), pcap_rlc_max_pdu_len);
    return;
  }

  span<const uint8_t> pdu = to_span(buf, span<uint8_t>(tmp_mem).first(buf.length()));

  uint8_t        context_header[PCAP_CONTEXT_HEADER_MAX] = {};
  const uint16_t length                                  = pdu.size();

  struct udphdr* udp_header;
  int            offset = 0;

  // Add dummy UDP header, start with src and dest port
  udp_header       = (struct udphdr*)context_header;
  udp_header->dest = htons(0xdead);
  offset += 2;
  udp_header->source = htons(0xbeef);
  offset += 2;
  // length to be filled later
  udp_header->len = 0x0000;
  offset += 2;
  // dummy CRC
  udp_header->check = 0x0000;
  offset += 2;

  // Start magic string
  memcpy(&context_header[offset], PCAP_RLC_NR_START_STRING, strlen(PCAP_RLC_NR_START_STRING));
  offset += strlen(PCAP_RLC_NR_START_STRING);

  offset += nr_pcap_pack_rlc_context_to_buffer(context, &context_header[offset], PCAP_CONTEXT_HEADER_MAX);

  udp_header->len = htons(offset + length);

  // Write header
  file.write_pcap_header(offset + pdu.size());
  // Write context
  file.write_pcap_pdu(span<uint8_t>(context_header, offset));
  // Write PDU
  file.write_pcap_pdu(pdu);
}

/// Helper function to serialize RLC NR context
int nr_pcap_pack_rlc_context_to_buffer(const pcap_rlc_pdu_context& context, uint8_t* buffer, unsigned int length)
{
  int      offset = {};
  uint16_t tmp16  = {};

  if (buffer == nullptr || length < PCAP_CONTEXT_HEADER_MAX) {
    printf("Error: Writing buffer null or length to small\n");
    return -1;
  }

  /*****************************************************************/
  /* Context information (same as written by UDP heuristic clients */
  buffer[offset++] = context.rlc_mode;
  buffer[offset++] = context.sequence_number_length;

  /* Direction */
  buffer[offset++] = PCAP_RLC_NR_DIRECTION_TAG;
  buffer[offset++] = context.direction;

  /* UEID */
  buffer[offset++] = PCAP_RLC_NR_UEID_TAG;
  tmp16            = htons(context.ueid);
  memcpy(buffer + offset, &tmp16, 2);
  offset += 2;

  /* Bearer type */
  buffer[offset++] = PCAP_RLC_NR_BEARER_TYPE_TAG;
  buffer[offset++] = context.bearer_type;

  /* Bearer ID */
  buffer[offset++] = PCAP_RLC_NR_BEARER_ID_TAG;
  buffer[offset++] = context.bearer_id;

  /* Data tag immediately preceding PDU */
  buffer[offset++] = PCAP_RLC_NR_PAYLOAD_TAG;
  return offset;
}

std::unique_ptr<rlc_pcap> srsran::create_rlc_pcap(const std::string& filename,
                                                  task_executor&     backend_exec,
                                                  bool               srb_pdus_enabled,
                                                  bool               drb_pdus_enabled)
{
  if (filename.empty()) {
    return std::make_unique<null_rlc_pcap>();
  }
  return std::make_unique<rlc_pcap_impl>(filename, srb_pdus_enabled, drb_pdus_enabled, backend_exec);
}
