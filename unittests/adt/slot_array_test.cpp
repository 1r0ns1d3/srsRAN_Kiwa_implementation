/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2021 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srsgnb/adt/slot_array.h"
#include "srsgnb/support/test_utils.h"

using namespace srsgnb;

static_assert(std::is_same<slot_array<int, 5>::value_type, int>::value, "Invalid container value_type");
static_assert(std::is_same<slot_array<int, 5>::iterator::value_type, int>::value, "Invalid container value_type");
static_assert(std::is_same<slot_array<int, 5>::const_iterator::value_type, const int>::value,
              "Invalid container value_type");

void test_optional_array()
{
  slot_array<int, 5> table1;
  TESTASSERT(table1.size() == 0 and table1.empty());
  TESTASSERT(table1.begin() == table1.end());

  TESTASSERT(not table1.contains(0));
  table1.insert(0, 5);
  TESTASSERT(table1.size() == 1 and not table1.empty());
  TESTASSERT(table1.begin() != table1.end());
  table1.erase(0);
  TESTASSERT(table1.size() == 0 and table1.empty());
  table1.insert(1, 3);
  table1.insert(4, 2);
  TESTASSERT(table1.size() == 2);
  TESTASSERT(table1[4] == 2 and table1[1] == 3);

  size_t count   = 0;
  int    array[] = {3, 2};
  for (int e : table1) {
    TESTASSERT(array[count++] == e);
  }

  auto it = table1.begin();
  TESTASSERT(*it == 3);
  table1.erase(it);
  TESTASSERT(table1.size() == 1);
}

void test_optional_vector()
{
  slot_vector<int> table1;
  TESTASSERT(table1.size() == 0 and table1.empty());

  TESTASSERT(not table1.contains(0));
  table1.insert(0, 5);
  TESTASSERT(table1.size() == 1 and not table1.empty());
  table1.erase(0);
  TESTASSERT(table1.size() == 0 and table1.empty());
  table1.insert(1, 3);
  table1.insert(4, 2);
  TESTASSERT(table1.size() == 2);
  TESTASSERT(table1[4] == 2 and table1[1] == 3);

  size_t count   = 0;
  int    array[] = {3, 2};
  for (int e : table1) {
    TESTASSERT(array[count++] == e);
  }

  auto it = table1.begin();
  TESTASSERT(*it == 3);
  table1.erase(it);
  TESTASSERT(table1.size() == 1);
}

void test_split_slot_span()
{
  constexpr size_t     L                     = 7;
  int                  some_list[L]          = {};
  bool                 some_list_presence[L] = {};
  split_slot_span<int> view(some_list, some_list_presence, L);

  TESTASSERT(view.size() == 0 and view.empty());
  TESTASSERT(view.begin() == view.end());
  TESTASSERT(not view.contains(0));
  TESTASSERT(view.find_first_empty() == L);

  view.insert(1, 1);
  TESTASSERT(view.size() == 1 and not view.empty());
  TESTASSERT(view.begin() != view.end() and *view.begin() == 1);
  TESTASSERT(view.contains(1));
  TESTASSERT(view[1] == 1);
  TESTASSERT(view.find_first_empty() == 1);

  view.insert(3, 3);
  TESTASSERT(view[3] == 3);
  size_t c = 0;
  for (auto& e : view) {
    TESTASSERT(c == 0 ? e == 1 : e == 3);
    c++;
  }
  TESTASSERT(view.size() == 2);

  view.erase(view.begin());
  TESTASSERT(view.size() == 1);
  TESTASSERT(not view.contains(1) and view.contains(3));

  view.clear();
  TESTASSERT(view.empty());
}

int main()
{
  auto& test_log = srslog::fetch_basic_logger("TEST");
  test_log.set_level(srslog::basic_levels::info);

  test_optional_array();
  test_optional_vector();
  test_split_slot_span();

  printf("Success\n");
  return 0;
}
