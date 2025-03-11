/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/adt/complex.h"
#include "srsran/adt/span.h"
#include "srsran/phy/upper/log_likelihood_ratio.h"

namespace srsran {

/// \brief Soft-demodulates 16-QAM modulation.
/// \param[out] llrs       Resultant log-likelihood ratios.
/// \param[in]  symbols    Input constellation symbols.
/// \param[in]  noise_vars Noise variance for each symbol in the constellation.
void demodulate_soft_QAM16(span<log_likelihood_ratio> llrs, span<const cf_t> symbols, span<const float> noise_vars);

} // namespace srsran
