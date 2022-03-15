
#ifndef SRSGNB_MAC_SCH_PDU_H
#define SRSGNB_MAC_SCH_PDU_H

#include "srsgnb/adt/byte_buffer.h"
#include "srsgnb/adt/span.h"
#include "srsgnb/ran/lcid.h"
#include "srsgnb/ran/rnti.h"
#include "srsgnb/srslog/srslog.h"

namespace srsgnb {

class mac_sch_pdu;

class mac_sch_subpdu
{
public:
  /// 3GPP 38.321 v15.3.0 Combined Tables 6.2.1-1, 6.2.1-2
  enum lcid_sch_t {
    /// Values for DL-SCH
    CCCH       = 0b000000,
    DRX_CMD    = 0b111100,
    TA_CMD     = 0b111101,
    CON_RES_ID = 0b111110,

    /// Values for UL-SCH
    CRNTI           = 0b111010,
    SHORT_TRUNC_BSR = 0b111011,
    LONG_TRUNC_BSR  = 0b111100,
    CCCH_SIZE_48    = 0b110100,
    CCCH_SIZE_64    = 0b000000,
    SE_PHR          = 0b111001, // Single Entry PHR

    SHORT_BSR = 0b111101,
    LONG_BSR  = 0b111110,

    // Common
    PADDING = 0b111111
  };

  // SDUs up to 256 B can use the short 8-bit L field
  static const int32_t MAC_SUBHEADER_LEN_THRESHOLD = 256;

  explicit mac_sch_subpdu(mac_sch_pdu* parent_) : parent(parent_), logger(&srslog::fetch_basic_logger("MAC-NR")){};

  /// Type of LCID
  lcid_sch_t get_type() const { return lcid >= 32 ? (lcid_sch_t)lcid : CCCH; }

  /// Checks whether UL-DCCH handling in done as CE
  bool is_sdu() const { return lcid <= 32 and !is_ul_ccch(); }
  bool is_valid_lcid() const;
  bool is_var_len_ce(lcid_t lcid_) const;
  bool is_ul_ccch() const;

  int32_t        read_subheader(const uint8_t* ptr);
  uint32_t       get_total_length() const;
  uint32_t       get_sdu_length() const;
  lcid_t         get_lcid() const { return lcid; }
  uint8_t*       get_sdu();
  const uint8_t* get_sdu() const;
  rnti_t         get_c_rnti() const;

  // both return the reported values as per TS 38.321, mapping to dB according to TS 38.133 Sec 10.1.17 not done here
  uint8_t get_phr() const;
  uint8_t get_pcmax() const;

  // BSR
  struct lcg_bsr_t {
    uint8_t lcg_id;
    uint8_t buffer_size;
  };
  lcg_bsr_t            get_sbsr() const;
  static const uint8_t max_num_lcg_lbsr = 8;
  struct lbsr_t {
    uint8_t                bitmap; // the first octet of LBSR and Long Trunc BSR
    std::vector<lcg_bsr_t> list;   // one entry for each reported LCG
  };
  lbsr_t get_lbsr() const;

  // TA
  struct ta_t {
    uint8_t tag_id;
    uint8_t ta_command;
  };
  ta_t get_ta() const;

  // UE contention resolution identity CE
  static const uint8_t                           ue_con_res_id_len = 6;
  typedef std::array<uint8_t, ue_con_res_id_len> ue_con_res_id_t;
  ue_con_res_id_t                                get_ue_con_res_id_ce() const;

  // setters
  void set_sdu(uint32_t lcid_, span<uint8_t> payload_);
  void set_padding(uint32_t len_);
  void set_c_rnti(uint16_t crnti_);
  void set_se_phr(uint8_t phr_, uint8_t pcmax_);
  void set_sbsr(lcg_bsr_t bsr_);
  void set_lbsr(span<const mac_sch_subpdu::lcg_bsr_t> bsr_);
  void set_ue_con_res_id_ce(ue_con_res_id_t id);

  uint32_t write_subpdu(const uint8_t* start_);

  // Used by BSR procedure to determine size of BSR types
  static uint32_t sizeof_ce(uint32_t lcid, bool is_ul);

  void to_string(fmt::memory_buffer& buffer) const;

private:
  mac_sch_pdu*          parent = nullptr;
  srslog::basic_logger* logger;

  // internal helpers
  bool has_length_field();

  uint32_t lcid          = 0;
  int      header_length = 0;
  int      sdu_length    = 0;
  bool     F_bit         = false;

  /// This helper class manages a SDU pointer that can point to either a user provided external buffer or to a small
  /// internal buffer, useful for storing very short SDUs.
  class sdu_buffer
  {
    static const uint8_t mac_ce_payload_len = 8 + 1;         // Long BSR has max. 9 octets (see sizeof_ce() too)
    std::array<uint8_t, mac_ce_payload_len> ce_write_buffer; // Buffer for CE payload
    uint8_t*                                sdu = nullptr;

  public:
    sdu_buffer() = default;

    sdu_buffer(const sdu_buffer& other) : ce_write_buffer(other.ce_write_buffer)
    {
      // First check if we need to use internal storage.
      if (other.sdu == other.ce_write_buffer.data()) {
        sdu = ce_write_buffer.data();
        return;
      }
      sdu = other.sdu;
    }

    sdu_buffer& operator=(const sdu_buffer& other)
    {
      if (this == &other) {
        return *this;
      }
      ce_write_buffer = other.ce_write_buffer;
      if (other.sdu == other.ce_write_buffer.data()) {
        sdu = ce_write_buffer.data();
        return *this;
      }
      sdu = other.sdu;
      return *this;
    }

    explicit operator bool() const { return sdu; }

    /// Set the SDU pointer to use the internal buffer.
    uint8_t* use_internal_storage()
    {
      sdu = ce_write_buffer.data();
      return sdu;
    }

    /// Set the SDU pointer to point to the provided buffer.
    uint8_t* set_storage_to(uint8_t* p)
    {
      sdu = p;
      return sdu;
    }

    /// Returns the SDU pointer.
    const uint8_t* ptr() const { return sdu; }
    uint8_t*       ptr() { return sdu; }
  };

  sdu_buffer sdu;
};

class mac_sch_pdu
{
public:
  mac_sch_pdu(bool ulsch_ = false) : ulsch(ulsch_), logger(srslog::fetch_basic_logger("MAC-NR")) {}

  void                  pack();
  int                   unpack(span<const uint8_t> payload);
  uint32_t              get_num_subpdus() const { return subpdus.size(); }
  const mac_sch_subpdu& get_subpdu(const uint32_t& index) const;
  mac_sch_subpdu&       get_subpdu(uint32_t index);
  bool                  is_ulsch();

  int  init_tx(byte_buffer* buffer_, uint32_t pdu_len_, bool is_ulsch_ = false);
  void init_rx(bool ulsch_ = false);

  // Add SDU or CEs to PDU
  // All functions will return SRSRAN_SUCCESS on success, and SRSRAN_ERROR otherwise
  uint32_t add_sdu(lcid_t lcid_, span<uint8_t> payload_);
  uint32_t add_crnti_ce(uint16_t crnti_);
  uint32_t add_se_phr_ce(uint8_t phr_, uint8_t pcmax_);
  uint32_t add_sbsr_ce(mac_sch_subpdu::lcg_bsr_t bsr_);
  uint32_t add_lbsr_ce(span<const mac_sch_subpdu::lcg_bsr_t> bsr_);
  uint32_t add_ue_con_res_id_ce(mac_sch_subpdu::ue_con_res_id_t id);

  uint32_t get_remaing_len() const;

  void to_string(fmt::memory_buffer& buffer);

  uint32_t size_header_sdu(lcid_t lcid_, uint32_t nbytes);

private:
  /// Private helper that adds a subPDU to the MAC PDU
  uint32_t add_sudpdu(mac_sch_subpdu& subpdu);

  bool                        ulsch = false;
  std::vector<mac_sch_subpdu> subpdus;

  byte_buffer*          buffer        = nullptr;
  uint32_t              pdu_len       = 0;
  uint32_t              remaining_len = 0;
  srslog::basic_logger& logger;
};

} // namespace srsgnb

#endif // SRSGNB_MAC_SCH_PDU_H
