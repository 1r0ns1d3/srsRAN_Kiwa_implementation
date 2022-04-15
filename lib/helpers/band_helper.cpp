
#include "band_helper.h"
#include <algorithm>
#include <cmath>

namespace srsgnb {

// definition of static members
constexpr std::array<band_helper::nr_band, band_helper::nof_nr_bands_fr1> band_helper::nr_band_table_fr1;
constexpr std::array<band_helper::nr_raster_params, 3> band_helper::nr_fr_params;
constexpr std::array<band_helper::nr_operating_band, band_helper::nof_nr_operating_band_fr1>
          band_helper::nr_operating_bands_fr1;
constexpr std::array<band_helper::nr_band_ss_raster, band_helper::nof_nr_band_ss_raster>
          band_helper::nr_band_ss_raster_table;

// Formula in 5.4.2.1
double band_helper::nr_arfcn_to_freq(uint32_t nr_arfcn)
{
  nr_raster_params params = get_raster_params(nr_arfcn);
  if (not is_valid_raster_param(params)) {
    return 0.0;
  }
  return (params.F_REF_Offs_MHz * 1e6 + params.delta_F_global_kHz * (nr_arfcn - params.N_REF_Offs) * 1e3);
}

uint32_t band_helper::freq_to_nr_arfcn(double freq)
{
  nr_raster_params params = get_raster_params(freq);
  if (not is_valid_raster_param(params)) {
    return 0;
  }
  return (((freq - params.F_REF_Offs_MHz * 1e6) / 1e3 / params.delta_F_global_kHz) + params.N_REF_Offs);
}

#if 0
// Implements 5.4.2.1 in TS 38.104
std::vector<uint32_t> band_helper::get_bands_nr(uint32_t                             nr_arfcn,
                                                      band_helper::delta_f_raster_t delta_f_raster)
{
 std::vector<uint32_t> bands;
 for (const auto& nr_band : nr_band_table_fr1) {
   if (nr_arfcn >= nr_band.dl_nref_first && nr_arfcn <= nr_band.dl_nref_last && nr_arfcn % nr_band.dl_nref_step == 0) {
     // band must not already be present
     if (std::find(bands.begin(), bands.end(), nr_band.band) == bands.end()) {
       if (delta_f_raster == DEFAULT) {
         // add band if delta_f_raster has default value
         bands.push_back(nr_band.band);
       } else {
         // if delta_f_raster is set explicitly, only add if band matches
         if (nr_band.delta_f_raster == delta_f_raster) {
           bands.push_back(nr_band.band);
         }
       }
     }
   }
 }
 return bands;
}
#endif

uint16_t band_helper::get_band_from_dl_freq_Hz(double freq) const
{
  uint32_t freq_MHz = (uint32_t)round(freq / 1e6);
  for (const nr_operating_band& band : nr_operating_bands_fr1) {
    if (freq_MHz >= band.F_DL_low and freq_MHz <= band.F_DL_high) {
      return band.band;
    }
  }
  return UINT16_MAX;
}

uint16_t band_helper::get_band_from_dl_arfcn(uint32_t arfcn)
{
  for (const nr_band& band : nr_band_table_fr1) {
    // Check given ARFCN is between the first and last possible ARFCN and matches step
    if (arfcn >= band.dl_nref_first and arfcn <= band.dl_nref_last and
        (arfcn - band.dl_nref_first) % band.dl_nref_step == 0) {
      return band.band;
    }
  }
  return UINT16_MAX;
}

uint32_t band_helper::get_ul_arfcn_from_dl_arfcn(uint32_t dl_arfcn)
{
  // return same ARFCN for TDD bands
  auto asd = band_helper::get_band_from_dl_arfcn(dl_arfcn);
  if (band_helper::get_duplex_mode(asd) == duplex_mode::TDD) {
    return dl_arfcn;
  }

  // derive UL ARFCN for FDD bands
  for (const auto& band : nr_band_table_fr1) {
    if (band.band == get_band_from_dl_arfcn(dl_arfcn)) {
      uint32_t offset = (dl_arfcn - band.dl_nref_first) / band.dl_nref_step;
      return (band.ul_nref_first + offset * band.ul_nref_step);
    }
  }

  return 0;
}

#if 0
double band_helper::get_center_freq_from_abs_freq_point_a(uint32_t nof_prb, uint32_t freq_point_a_arfcn)
{
 // for FR1 unit of resources blocks for freq calc is always 180kHz regardless for actual SCS of carrier
 // TODO: add offset_to_carrier
 double abs_freq_point_a_freq = nr_arfcn_to_freq(freq_point_a_arfcn);
 return abs_freq_point_a_freq +
        (nof_prb / 2 * SRSRAN_SUBC_SPACING_NR(srsran_subcarrier_spacing_t::srsran_subcarrier_spacing_15kHz) *
         SRSRAN_NRE);
}


uint32_t band_helper::get_abs_freq_point_a_arfcn(uint32_t nof_prb, uint32_t arfcn)
{
 return freq_to_nr_arfcn(get_abs_freq_point_a_from_center_freq(nof_prb, nr_arfcn_to_freq(arfcn)));
}

double band_helper::get_abs_freq_point_a_from_center_freq(uint32_t nof_prb, double center_freq)
{
 // for FR1 unit of resources blocks for freq calc is always 180kHz regardless for actual SCS of carrier
 // TODO: add offset_to_carrier
 return center_freq -
        (nof_prb / 2 * SRSRAN_SUBC_SPACING_NR(srsran_subcarrier_spacing_t::srsran_subcarrier_spacing_15kHz) *
         SRSRAN_NRE);
}

uint32_t band_helper::find_lower_bound_abs_freq_ssb(uint16_t                    band,
                                                          srsran_subcarrier_spacing_t scs,
                                                          uint32_t                    min_center_freq_hz)
{
 sync_raster_t sync_raster = get_sync_raster(band, scs);
 if (!sync_raster.valid()) {
   return 0;
 }

 double ssb_bw_hz = SRSRAN_SSB_BW_SUBC * SRSRAN_SUBC_SPACING_NR(scs);
 while (!sync_raster.end()) {
   double abs_freq_ssb_hz = sync_raster.get_frequency();

   if ((abs_freq_ssb_hz > min_center_freq_hz + ssb_bw_hz / 2) and
       ((uint32_t)std::round(abs_freq_ssb_hz - min_center_freq_hz) % SRSRAN_SUBC_SPACING_NR(scs) == 0)) {
     return freq_to_nr_arfcn(abs_freq_ssb_hz);
   }

   sync_raster.next();
 }
 return 0;
}

uint32_t band_helper::get_abs_freq_ssb_arfcn(uint16_t                    band,
                                                   srsran_subcarrier_spacing_t scs,
                                                   uint32_t                    freq_point_a_arfcn,
                                                   uint32_t                    coreset0_offset_rb)
{
 double freq_point_a_hz    = nr_arfcn_to_freq(freq_point_a_arfcn);
 double coreset0_offset_hz = coreset0_offset_rb * SRSRAN_NRE * SRSRAN_SUBC_SPACING_NR(scs);
 return find_lower_bound_abs_freq_ssb(band, scs, freq_point_a_hz + coreset0_offset_hz);
}
#endif

ssb_pattern_case band_helper::get_ssb_pattern(uint16_t band, subcarrier_spacing scs)
{
  // Look for the given band and SCS
  for (const nr_band_ss_raster& ss_raster : nr_band_ss_raster_table) {
    // Check if band and SCS match!
    if (ss_raster.band == band && ss_raster.scs == scs) {
      return ss_raster.pattern;
    }

    // As bands are in ascending order, do not waste more time if the current band is bigger
    if (ss_raster.band > band) {
      return ssb_pattern_case::invalid;
    }
  }

  // Band is out of range, so consider invalid
  return ssb_pattern_case::invalid;
}

subcarrier_spacing band_helper::get_ssb_scs(uint16_t band) const
{
  // Look for the given band and SCS
  for (const nr_band_ss_raster& ss_raster : nr_band_ss_raster_table) {
    // Check if band and SCS match!
    if (ss_raster.band == band) {
      return ss_raster.scs;
    }

    // As bands are in ascending order, do not waste more time if the current band is bigger
    if (ss_raster.band > band) {
      return subcarrier_spacing::invalid;
    }
  }
  return subcarrier_spacing::invalid;
}

duplex_mode band_helper::get_duplex_mode(uint16_t band)
{
  // Look for the given band
  for (const nr_operating_band& b : nr_operating_bands_fr1) {
    // Check if band and SCS match!
    if (b.band == band) {
      return b.duplex;
    }

    // As bands are in ascending order, do not waste more time if the current band is bigger
    if (b.band > band) {
      return duplex_mode::INVALID;
    }
  }

  // Band is out of range, so consider invalid
  return duplex_mode::INVALID;
}

bool band_helper::is_paired_spectrum(uint16_t band)
{
  duplex_mode mode = get_duplex_mode(band);
  srsran_assert(mode < duplex_mode::INVALID, "Returned invalid duplex MODE");
  return mode == duplex_mode::FDD ? true : false;
}

#if 0
struct sync_raster_impl : public band_helper::sync_raster_t {
public:
 sync_raster_impl(uint32_t gscn_f, uint32_t gscn_s, uint32_t gscn_l) : sync_raster_t(gscn_f, gscn_s, gscn_l)
 {
   // Do nothing
 }
};


double band_helper::sync_raster_t::get_frequency() const
{
 // see TS38.104 table 5.4.3.1-1

 // Row 1
 if (gscn_last <= 7498) {
   return N * 1200e3 + M[M_idx] * 50e3;
 }

 // Row 2
 if (7499 <= gscn_last and gscn_last <= 22255) {
   return 3000e6 + N * 1.44e6;
 }

 // Row 3
 if (22256 <= gscn_last and gscn_last <= 26639) {
   return 2425.08e6 + N * 17.28e6;
 }

 // Unhandled case
 return NAN;
}

uint32_t band_helper::sync_raster_t::get_gscn() const
{
 if (gscn_last <= 7498) {
   return 3 * N + (M[M_idx] - 3) / 2;
 } else if (7499 <= gscn_last and gscn_last <= 22255) {
   return 7499 + N;
 } else if (22256 <= gscn_last and gscn_last <= 26639) {
   return 22256 + N;
 }

 return 0;
}

band_helper::sync_raster_t band_helper::get_sync_raster(uint16_t                    band,
                                                                     srsran_subcarrier_spacing_t scs) const
{
 // Look for the given band and SCS
 for (const nr_band_ss_raster& ss_raster : nr_band_ss_raster_table) {
   // Check if band and SCS match!
   if (ss_raster.band == band && ss_raster.scs == scs) {
     return sync_raster_impl(ss_raster.gscn_first, ss_raster.gscn_step, ss_raster.gscn_last);
   }

   // As bands are in ascending order, do not waste more time if the current band is bigger
   if (ss_raster.band > band) {
     return sync_raster_impl(0, 0, 0);
   }
 }

 // Band is out of range, so consider invalid
 return sync_raster_impl(0, 0, 0);
}

#endif

band_helper::nr_raster_params band_helper::get_raster_params(uint32_t nr_arfcn)
{
  for (auto& fr : nr_fr_params) {
    if (nr_arfcn >= fr.N_REF_min && nr_arfcn <= fr.N_REF_max) {
      return fr;
    }
  }
  return {}; // return empty params
}

band_helper::nr_raster_params band_helper::get_raster_params(double freq)
{
  for (auto& fr : nr_fr_params) {
    if (freq >= fr.freq_range_start * 1e6 && freq <= fr.freq_range_end * 1e6) {
      return fr;
    }
  }
  return {}; // return empty params
}

bool band_helper::is_valid_raster_param(const band_helper::nr_raster_params& raster)
{
  for (auto& fr : nr_fr_params) {
    if (fr == raster) {
      return true;
    }
  }
  return false;
}

} // namespace srsgnb
