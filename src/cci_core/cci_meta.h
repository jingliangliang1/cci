/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 ****************************************************************************/
/**
 * \file   cci_meta.h
 * \author Philipp A. Hartmann, Intel
 * \brief  Some template meta-programming helpers
 *
 * \note Only \ref cci::cci_tag<T> et.al. are part of the standard.
 */
#ifndef CCI_CORE_CCI_META_H_INCLUDED_
#define CCI_CORE_CCI_META_H_INCLUDED_

#include <cci_core/systemc.h>
#include <cci_core/cci_cmnhdr.h>

CCI_OPEN_NAMESPACE_

/// Typed tag class
template<typename T> struct cci_tag { typedef T type; };

/// Explicitly typed tag class
template<typename T> struct cci_typed_tag : cci_tag<T> {};

/// Tag alias for an untyped tag
typedef cci_tag<void> cci_untyped_tag;

namespace detail {

using sc_boost::enable_if;
using sc_boost::disable_if;

/// C++03 implementation of std::void_t
template<typename T> struct always_void { typedef void type; };

/// A type encoding for an integral value
template<typename IntegralType, IntegralType V> struct integral_constant
{
  typedef IntegralType value_type;
  typedef integral_constant type;
  static const value_type value = V;
};

typedef integral_constant<bool,true>  true_type;
typedef integral_constant<bool,false> false_type;

template<typename T, typename U> struct is_same : false_type {};
template<typename T> struct is_same<T,T> : true_type {};

template<typename T> struct remove_reference { typedef T type; };
template<typename T> struct remove_reference<T&> { typedef T type; };

} // namespace detail
CCI_CLOSE_NAMESPACE_

#endif // CCI_CORE_CCI_META_H_INCLUDED_
