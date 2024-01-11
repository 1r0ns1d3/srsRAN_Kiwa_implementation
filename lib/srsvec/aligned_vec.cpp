/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsran/srsvec/aligned_vec.h"
#include "simd.h"
#include "srsran/support/error_handling.h"
#include <cstdlib>

void* srsran::srsvec::detail::mem_alloc(std::size_t size)
{
  void* ptr = nullptr;
  int   ret = posix_memalign(&ptr, SIMD_BYTE_ALIGN * 8, size);
  report_fatal_error_if_not(ret == 0 && ptr, "Failed posix_memalign.");
  return ptr;
}

void srsran::srsvec::detail::mem_free(void* ptr)
{
  free(ptr);
}
