/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ofh_sector_controller.h"

using namespace srsran;
using namespace ofh;

void sector_controller::start()
{
  receiver.start();
}

void sector_controller::stop()
{
  receiver.stop();
}
