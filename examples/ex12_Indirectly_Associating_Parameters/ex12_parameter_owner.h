/*******************************************************************************
 * The following code is derived, directly or indirectly, from the SystemC
 * source code Copyright (c) 1996-2010 by all Contributors.
 * All Rights reserved.
 * 
 * The contents of this file are subject to the restrictions and limitations
 * set forth in the SystemC Open Source License Version 2.2.0 (the "License");
 * One may not use this file except in compliance with such restrictions and
 * limitations.  One may obtain instructions on how to receive a copy of the
 * License at http://www.systemc.org/.  Software distributed by Contributors
 * under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing rights and limitations under the License.
 * *******************************************************************************/

/**
 * @file      parameter_owner.h
 * @brief     This file contains the code which defines the OWNER module and its contents.
 *            The owner module is instantiated by the TOP_MODULE
 * @author    P V S Phaneendra, CircuitSutra Technologies   <pvs@circuitsutra.com>
 * @date      9th June, 2011 (Thursday)
 */

#ifndef EXAMPLES_EX12_INDIRECTLY_ASSOCIATING_PARAMETERS_EX12_PARAMETER_OWNER_H_
#define EXAMPLES_EX12_INDIRECTLY_ASSOCIATING_PARAMETERS_EX12_PARAMETER_OWNER_H_

#include <cci>
#include <string>
#include "xreport.hpp"

/// This module declares the cci_parameters and the are  created based on the
/// names passed from the top module
SC_MODULE(ex12_parameter_owner) {
 public:
  SC_HAS_PROCESS(ex12_parameter_owner);

  ex12_parameter_owner(sc_module_name _name,
                       std::string _param_name = "clock_speed_KHz",
                       float _freq = 10.0)
      : sc_module(_name) {
    clk = new cci::cnf::cci_param<float>(_param_name.c_str(), _freq);

    XREPORT("[OWNER C_TOR] : Parameter Name   : " << clk->get_name()
            << "\tParameter Value : " << clk->get());
  }

 private:
  // Declare an instance of mutable CCI parameter of type 'float'
  cci::cnf::cci_param<float>* clk;
};
// ex12_parameter_owner

#endif  // EXAMPLES_EX12_INDIRECTLY_ASSOCIATING_PARAMETERS_EX12_PARAMETER_OWNER_H_
