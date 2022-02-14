
#ifndef SRSGNB_TEST_H
#define SRSGNB_TEST_H

#ifdef __cplusplus

#include "srsran_assert.h"

#define TESTASSERT_EQ(EXPECTED, ACTUAL)                                                                                \
  (void)((EXPECTED == ACTUAL) ||                                                                                       \
         (srsran_assertion_failure(                                                                                    \
              "%s", fmt::format("Actual value '{}' differs from expected '{}'", ACTUAL, EXPECTED).c_str()),            \
          0))

#define TESTASSERT_NEQ(EXPECTED, ACTUAL)                                                                               \
  (void)((EXPECTED != ACTUAL) ||                                                                                       \
         (srsran_assertion_failure("%s", fmt::format("Value should not be equal to '{}'", ACTUAL).c_str()), 0))

#define TESTASSERT(cond) srsran_assert((cond), "Fail at \"%s\"", (#cond))

#define TESTASSERT_SUCCESS(cond) srsran_assert((cond == SRSGNB_SUCCESS), "Operation \"%s\" was not successful", (#cond))

#else // __cplusplus

#include <stdio.h>

#define TESTASSERT(cond)                                                                                               \
  do {                                                                                                                 \
    if (!(cond)) {                                                                                                     \
      fprintf(stderr, "%s:%d: Assertion Failure: \"%s\"\n", __FUNCTION__, __LINE__, (#cond));                          \
      return -1;                                                                                                       \
    }                                                                                                                  \
  } while (0)

#endif // __cplusplus

#endif // SRSGNB_TEST_H
