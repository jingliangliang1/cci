/*****************************************************************************
  Copyright 2006-2014 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2010-2015 Texas Instruments Inc.
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 *****************************************************************************/

/**
 *  @file   testbench.cpp
 *  @brief  A testbench that demonstrates how to use default values and init values 
 *          for a parameter.
 *          Demonstrates relative precedence of default (supplied to parameter constructor) and initial
 *          (via name-based access prior to construction) values.
 *          
 *  @author Vishal Goel, Texas Instruments
 *
 */

#include "ex05_simple_ip.h"
#include "ex05_config_ip.h"

/**
 *  @fn     int sc_main(int argc, char* argv[])
 *  @brief  The testbench for the CCI simpl_int_param example
 *  @param  argc  The number of input arguments
 *  @param  argv  An array of input arguments
 *  @return An integer representing the execution status of the function
 */
int sc_main(int argc, char *argv[]) {
  ex05_config_ip cfg_ip("cfg_ip");
  ex05_simple_ip sim_ip("sim_ip");

  SC_REPORT_INFO("sc_main", "Begin Simulation.");
  sc_core::sc_start();
  SC_REPORT_INFO("sc_main", "End Simulation.");

  return EXIT_SUCCESS;
}
