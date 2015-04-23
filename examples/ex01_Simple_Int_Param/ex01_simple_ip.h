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
 *  @file   simple_ip.h
 *  @brief  A simple IP that has a mutable integer parameter
 *  @author R. Swaminathan, TI
 */

#ifndef EXAMPLES_EX01_SIMPLE_INT_PARAM_EX01_SIMPLE_IP_H_
#define EXAMPLES_EX01_SIMPLE_INT_PARAM_EX01_SIMPLE_IP_H_

#include <cci>
#include "xreport.hpp"

/**
 *  @class  ex01_simple_ip
 *  @brief  A simple IP which owns a CCI param.
 */
SC_MODULE(ex01_simple_ip) {
 public:

  /**
   *  @fn     void ex01_simple_ip()
   *  @brief  The constructor for the class.
   *  @return void
   */
  SC_CTOR(ex01_simple_ip)
  // Initialize int_param with 0
      : int_param("int_param", 0) {
    SC_THREAD(execute);
    XREPORT("Ctor: Default value of " << int_param.get_name() << " is "
            << int_param);
  }

  /**
   *  @fn     void ~ex01_simple_ip()
   *  @brief  The destructor for the class.
   *  @return void
   */
  ~ex01_simple_ip() {
    XREPORT_PLAIN("Dtor: Current value of " << int_param.get_name() << " is "
                  << int_param);
  }

  /**
   *  @fn     void execute()
   *  @brief  The main execution block (no real functionality)
   *  @return void
   */
  void execute() {
    // Wait for 10ns to allow config_ip to update int_param value
    wait(10, sc_core::SC_NS);

    // Update int_param value to 1
    XREPORT("execute: Set value of int_param to 1");
    int_param = 1;
    XREPORT("execute: Current value of int_param is "<< int_param);
  }

 private:
  cci::cnf::cci_param<int> int_param; ///< CCI param to hold buffer size
};
// ex01_simple_ip

#endif  // EXAMPLES_EX01_SIMPLE_INT_PARAM_EX01_SIMPLE_IP_H_

