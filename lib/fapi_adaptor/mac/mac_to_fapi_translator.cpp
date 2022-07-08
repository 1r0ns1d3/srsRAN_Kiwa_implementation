/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "mac_to_fapi_translator.h"
#include "srsgnb/fapi/message_validators.h"
#include "srsgnb/fapi_adaptor/mac/messages/pdcch.h"
#include "srsgnb/fapi_adaptor/mac/messages/pdsch.h"
#include "srsgnb/fapi_adaptor/mac/messages/ssb.h"

using namespace srsgnb;
using namespace fapi;
using namespace fapi_adaptor;

namespace {

/// Auxiliary struct to group PDCCH PDUs.
struct pdcch_group {
  const pdcch_dl_information* info;
  const dci_payload*          payload;
};

inline bool operator==(const pdcch_group& lhs, const pdcch_group& rhs)
{
  // :TODO: comparing the 2 pointers, change this to compare the BWP.
  return lhs.info->ctx.bwp_cfg == rhs.info->ctx.bwp_cfg && lhs.info->ctx.coreset_cfg == rhs.info->ctx.coreset_cfg;
}

} // namespace

static static_vector<unsigned, MAX_DL_PDUS_PER_SLOT>
find_same_bwp_and_coreset_for_first_element(const static_vector<pdcch_group, MAX_DL_PDUS_PER_SLOT>& candidates)
{
  static_vector<unsigned, MAX_DL_PDUS_PER_SLOT> result;

  const pdcch_group& lhs = candidates.front();

  for (auto I = std::find(candidates.begin() + 1, candidates.end(), lhs), E = candidates.end(); I != E;
       I = std::find(I + 1, candidates.end(), lhs)) {
    result.push_back(std::distance(candidates.begin(), I));
  }

  return result;
}

static void add_pdcch_pdus_to_request(dl_tti_request_message_builder& builder, const mac_dl_sched_result& dl_res)
{
  // Group the PDU's.
  static_vector<mac_pdcch_pdu, MAX_DL_PDUS_PER_SLOT> pdus;

  static_vector<pdcch_group, MAX_DL_PDUS_PER_SLOT> candidates;

  // Fill the candidates.
  for (unsigned i = 0, e = dl_res.pdcch_pdus.size(); i != e; ++i) {
    candidates.push_back({&dl_res.dl_res->dl_pdcchs[i], &dl_res.pdcch_pdus[i]});
  }

  // Fill the PDUs.
  while (!candidates.empty()) {
    pdus.emplace_back();
    mac_pdcch_pdu& pdu = pdus.back();

    const pdcch_group& candidate = candidates.front();

    // Fill the PDU data.
    pdu.bwp_cfg     = candidate.info->ctx.bwp_cfg;
    pdu.coreset_cfg = candidate.info->ctx.coreset_cfg;
    pdu.dcis.push_back({candidate.info, candidate.payload});

    // Find the same BWP and Coreset PDUs.
    const static_vector<unsigned, MAX_DL_PDUS_PER_SLOT>& pdu_indexes =
        find_same_bwp_and_coreset_for_first_element(candidates);

    // Append the DCIs and remove them from the candidates.
    for (unsigned i = pdu_indexes.size(); i; --i) {
      unsigned index = i - 1;
      pdu.dcis.push_back({candidates[index].info, candidates[index].payload});
      candidates.erase((candidates.begin() + index));
    }

    // Remove the first element.
    candidates.erase(candidates.begin());
  }

  // Convert the MAC PDUs into FAPI PDUs.
  for (const auto& pdu : pdus) {
    dl_pdcch_pdu_builder pdcch_builder = builder.add_pdcch_pdu(pdu.dcis.size());
    convert_pdcch_mac_to_fapi(pdcch_builder, pdu);
  }
}

static void add_ssb_pdus_to_request(dl_tti_request_message_builder& builder, const mac_dl_sched_result& dl_res)
{
  for (const auto& pdu : dl_res.ssb_pdu) {
    dl_ssb_pdu_builder ssb_builder = builder.add_ssb_pdu();
    convert_ssb_mac_to_fapi(ssb_builder, pdu);
  }
}

static void add_pdsch_pdus_to_request(dl_tti_request_message_builder& builder,
                                      pdsch_pdu_registy&              pdsch_registry,
                                      const mac_dl_sched_result&      dl_res)
{
  for (const auto& pdu : dl_res.dl_res->bc.sibs) {
    dl_pdsch_pdu_builder pdsch_builder = builder.add_pdsch_pdu();
    convert_pdsch_mac_to_fapi(pdsch_builder, pdu);
    pdsch_registry.register_pdu(pdsch_builder.get_pdu_id(), pdsch_pdu_registy::sib);
  }
}

void mac_to_fapi_translator::on_new_downlink_scheduler_results(const mac_dl_sched_result& dl_res)
{
  // :TODO: should we manage here 2 different numerologies in the same dl_res?
  dl_tti_request_message         msg;
  dl_tti_request_message_builder builder(msg);

  // FAPI implementation doesn't support groups at the moment.
  static const unsigned num_groups = 0;
  builder.set_basic_parameters(dl_res.slot.sfn(), dl_res.slot.slot_index(), num_groups);

  // Add PDCCH PDUs to the DL_TTI.request.
  add_pdcch_pdus_to_request(builder, dl_res);

  // Add SSB PDUs to the DL_TTI.request.
  add_ssb_pdus_to_request(builder, dl_res);

  {
    std::lock_guard<std::mutex> lock(mutex);
    // Add PDSCH PDUs to the DL_TTI.request.
    add_pdsch_pdus_to_request(builder, pdsch_registry, dl_res);
  }

  // Validate that the DL_TTI.request message is correct.
  error_type<validator_report> result = validate_dl_tti_request(msg);

  if (!result) {
    // :TODO: log errors,

    return;
  }

  gateway.dl_tti_request(msg);
}

void mac_to_fapi_translator::on_new_downlink_data(const mac_dl_data_result& dl_data)
{
  std::lock_guard<std::mutex> lock(mutex);

  // Sanity checks.
  srsran_assert(dl_data.sib1_pdus.size() == pdsch_registry.get_nof_pdus(pdsch_pdu_registy::sib),
                "Number of PDUs ({}) and Payloads ({}) for SIB PDUs doesn't match",
                pdsch_registry.get_nof_pdus(pdsch_pdu_registy::sib),
                dl_data.sib1_pdus.size());

  srsran_assert(dl_data.rar_pdus.size() == pdsch_registry.get_nof_pdus(pdsch_pdu_registy::rar),
                "Number of PDUs ({}) and Payloads ({}) for RAR PDUs doesn't match",
                pdsch_registry.get_nof_pdus(pdsch_pdu_registy::rar),
                dl_data.rar_pdus.size());

  srsran_assert(dl_data.ue_pdus.size() == pdsch_registry.get_nof_pdus(pdsch_pdu_registy::ue),
                "Number of PDUs ({}) and Payloads ({}) for SIB PDUs doesn't match",
                pdsch_registry.get_nof_pdus(pdsch_pdu_registy::ue),
                dl_data.ue_pdus.size());

  tx_data_request_message msg;
  tx_data_request_builder builder(msg);

  builder.set_basic_parameters(dl_data.slot.sfn(), dl_data.slot.slot_index());

  // Add SIB1 PDUs.
  const static_vector<byte_buffer, MAX_SIB1_PDUS_PER_SLOT>& sib1_pdus = dl_data.sib1_pdus;
  for (unsigned i = 0, e = sib1_pdus.size(); i != e; ++i) {
    const byte_buffer& payload = sib1_pdus[i];
    builder.add_pdu_custom_payload(
        pdsch_registry.get_fapi_pdu_index(i, pdsch_pdu_registy::sib), 1, {&*payload.cbegin(), &*payload.cend()});
  }

  // Add RAR PDUs.
  const static_vector<byte_buffer, MAX_RAR_PDUS_PER_SLOT>& rar_pdus = dl_data.rar_pdus;
  for (unsigned i = 0, e = rar_pdus.size(); i != e; ++i) {
    const byte_buffer& payload = rar_pdus[i];
    builder.add_pdu_custom_payload(
        pdsch_registry.get_fapi_pdu_index(i, pdsch_pdu_registy::rar), 1, {&*payload.cbegin(), &*payload.cend()});
  }

  // Add UE PDUs.
  const static_vector<rlc_byte_buffer, MAX_DL_PDUS_PER_SLOT>& ue_pdus = dl_data.ue_pdus;
  for (unsigned i = 0, e = ue_pdus.size(); i != e; ++i) {
    const rlc_byte_buffer& payload = ue_pdus[i];
    builder.add_pdu_custom_payload(
        pdsch_registry.get_fapi_pdu_index(i, pdsch_pdu_registy::ue), 1, {&*payload.begin(), &*payload.end()});
  }

  // Send the message.
  gateway.tx_data_request(msg);
}

void mac_to_fapi_translator::on_new_uplink_scheduler_results(const mac_ul_sched_result& ul_res) {}
