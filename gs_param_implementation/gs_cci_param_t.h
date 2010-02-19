// LICENSETEXT
//
//   Copyright (C) 2009-2010 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//    Mark Burton, mark@greensocs.com
//
//
//   This program is free software.
// 
//   If you have no applicable agreement with GreenSocs Ltd, this software
//   is licensed to you, and you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   If you have a applicable agreement with GreenSocs Ltd, the terms of that
//   agreement prevail.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301  USA 
// 
// ENDLICENSETEXT


#ifndef __GS_CCI_PARAM_T_H__
#define __GS_CCI_PARAM_T_H__

#ifndef __INCLUDE_ONLY_FROM_MAIN_INCLUDE_CHECK__
#error "failed include check"
#else
#undef __INCLUDE_ONLY_FROM_MAIN_INCLUDE_CHECK__
#endif

#include <string>
#include <iostream>
#include <map>
#include <set>
#include <boost/shared_ptr.hpp>

#include "cci.h"
#include "greencontrol/config.h"

namespace cci {
  
  // TODO: remove
  using std::cout;
  using std::endl;
  
  template <typename T, param_mutable_type TM>
  class gs_cci_param_t
  : public cci_base_param,
    public cci_param_if<T, TM>
  {
  protected:
    /// Typedef for the value.
    typedef T val_type;
    /// Typedef for the param itself.
    typedef gs_cci_param_t<T, TM> my_type;
    /// Typedef for the owned gs_param
    typedef gs::gs_param<T> gs_param_type;

  public:

    //using cci_param<T,TM>::operator=;

    explicit gs_cci_param_t(const std::string& n
                            , const std::string &val
                            , bool force_top_level_name /*= false*/
                            , bool register_at_db /*= true*/
                            , bool has_default_value ) // if there is a default value
    : m_gs_param(n, val, NULL, force_top_level_name, register_at_db) 
    , cci_base_param(m_gs_param, force_top_level_name, register_at_db, has_default_value)
    {
    }
    
    explicit gs_cci_param_t(const std::string& n 
                            , const val_type &val
                            , bool force_top_level_name /*= false*/
                            , bool register_at_db /*= true*/ ) 
    : m_gs_param((const std::string&)n, val, force_top_level_name) 
    , cci_base_param(m_gs_param, force_top_level_name, register_at_db, true)
    {
      assert(register_at_db && "Not supported with gs_param?");
    }
    
    ~gs_cci_param_t() {
    }
    
    virtual const basic_param_type get_basic_type() const { return partype_not_available; }
   
    virtual my_type& operator = (const my_type& v) { 
      set(v.get());
      return *this;
    }
     
    virtual my_type& operator = (const val_type& v) { 
      set(v);
      return *this;
    }
    

    virtual operator const val_type& () const {
      return get(); 
    }
    
    virtual void set(const val_type& val) {
      if (!m_gs_param.setValue(val))
        CCI_THROW_ERROR(cci_report_types::type().set_param_failed, "Bad value.");
    }
    
    virtual const val_type& get() const {
      return m_gs_param.getValue();
    }
    
    virtual void set(const val_type& val, void* lock_pwd) {
      // TODO: if (TODO)
        set(val);
    }
    
  protected:

    gs_param_type m_gs_param;
    
  };


} // namespace cci

#endif