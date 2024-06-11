/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "lib/srslog/sinks/syslog_sink.h"
#include "test_dummies.h"
#include "testing_helpers.h"
#include "srsran/srslog/srslog.h"
#include <fstream>
#include <sstream>

using namespace srslog;

static bool find_string_infile(std::string filename, std::string pattern)
{
  std::ifstream file(filename);
  std::string   line;
  bool          found = false;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      if (line.find(pattern) != std::string::npos) { // WILL SEARCH 2015-1113 in file
        found = true;
      }
    }
  } else {
    printf("WARNING: Could not open file %s", filename.c_str());
  }
  return found;
}

static bool syslog_basic_test()
{
  syslog_sink syslog_sink(get_default_log_formatter());

  // Build a 1000 byte entry.
  std::string entry(1000, 'a');

  syslog_sink.write(detail::memory_buffer(entry));

  syslog_sink.flush();

  ASSERT_EQ(find_string_infile("/var/log/syslog", entry), true);
  return true;
}

int main()
{
  TEST_FUNCTION(syslog_basic_test);
  return 0;
}
