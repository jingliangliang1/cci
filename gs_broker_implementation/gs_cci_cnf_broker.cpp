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
// The contents of this file are subject to the licensing terms specified
// in the file LICENSE. Please consult this file for restrictions and
// limitations that may apply.
// 
// ENDLICENSETEXT


#include "gs_cci_cnf_broker.h"

// TODO DEBUG
/*static void show_accessor_map(std::map<std::string, cci::cnf::cci_base_param*> mmap) {
  std::cout << mmap.size() << " accessors: " << std::endl;
  std::map<std::string, cci::cnf::cci_base_param*>::iterator iter;
  for( iter = mmap.begin(); iter != mmap.end(); iter++ ) {
    std::cout << iter->first << std::endl;
  }
}*/

cci::cnf::gs_cci_cnf_broker::gs_cci_cnf_broker(const std::string& name) 
: gs::cnf::GCnf_Api(name.c_str()) 
, m_name(name)
{ 
  assert (name.length() > 0 && "Name must not be empty");
  std::cout << "Created new broker \""<<name<<"\" and GCnf_Api \""<< getName() << "\"" << std::endl;
}

cci::cnf::gs_cci_cnf_broker::~gs_cci_cnf_broker() { 
}

void cci::cnf::gs_cci_cnf_broker::set_init_value(const std::string &parname, const std::string &json_value, const std::string& originator) {
  // TODO: use JSON
  if ( !gs::cnf::GCnf_Api::setInitValue(parname, json_value, originator) ) {
    CCI_THROW_ERROR(cci_report::set_param_failed().get_type(), "Setting initial value failed.");
  }
}
void cci::cnf::gs_cci_cnf_broker::set_init_value(const std::string &parname, const std::string &json_value, sc_core::sc_object* originator) {
  assert(originator);
  set_init_value(parname, json_value, originator->name());
}

void cci::cnf::gs_cci_cnf_broker::lock_init_value(const std::string &parname, const std::string& originator) {
  if ( !gs::cnf::GCnf_Api::lockInitValue(parname) ) {
    CCI_THROW_ERROR(cci_report::set_param_failed().get_type(), "Locking initial value failed.");
  }
}
void cci::cnf::gs_cci_cnf_broker::lock_init_value(const std::string &parname, sc_core::sc_object* originator) {
  assert(originator);
  lock_init_value(parname, originator->name());
}

const std::string cci::cnf::gs_cci_cnf_broker::get_json_string(const std::string &parname, const std::string& originator) {
  // TODO: use JSON
  return gs::cnf::GCnf_Api::getValue(parname);
}
const std::string cci::cnf::gs_cci_cnf_broker::get_json_string(const std::string &parname, sc_core::sc_object* originator) {
  assert(originator);
  return get_json_string(parname, originator->name());
}

const std::string cci::cnf::gs_cci_cnf_broker::get_json_string_keep_unused(const std::string &parname, const std::string& originator) {
  // TODO: use JSON
  return gs::cnf::GCnf_Api::getValue(parname, "", true);
}
const std::string cci::cnf::gs_cci_cnf_broker::get_json_string_keep_unused(const std::string &parname, sc_core::sc_object* originator) {
  assert(originator);
  return get_json_string_keep_unused(parname, originator->name());
}


cci::cnf::cci_base_param* cci::cnf::gs_cci_cnf_broker::get_param(const std::string &parname, const std::string& originator) {
  //std::cout << name() << " (gs_cci_cnf_broker) get param " << parname << std::endl;
  std::map<std::string,cci_base_param*>::iterator iter = m_mirrored_registry.find(parname);
  if( iter != m_mirrored_registry.end() ) {
    cci::cnf::cci_base_param* ret = dynamic_cast<cci::cnf::cci_base_param*>(iter->second);
    assert(ret != NULL && "This param shall be a cci::cnf::cci_base_param!");
    return ret;
  }
  else return NULL;
  /*gs::gs_param_base* p = gs::cnf::GCnf_Api::getPar(parname);
   cci_base_param* cp = dynamic_cast<cci_base_param*> (p);
   assert(((p == NULL && cp == NULL) || (p != NULL && cp != NULL)) && "There shall only be cci params in the gs database!");
   if (cp != NULL) return cp;
   else return NULL;*/
}
cci::cnf::cci_base_param* cci::cnf::gs_cci_cnf_broker::get_param(const std::string &parname, sc_core::sc_object* originator) {
  assert(originator);
  return get_param(parname, originator->name());
}

bool cci::cnf::gs_cci_cnf_broker::exists_param(const std::string &parname, const std::string& originator) {
  return gs::cnf::GCnf_Api::existsParam(parname);
}
bool cci::cnf::gs_cci_cnf_broker::exists_param(const std::string &parname, sc_core::sc_object* originator) {
  assert(originator);
  return exists_param(parname, originator->name());
}

bool cci::cnf::gs_cci_cnf_broker::is_used(const std::string &parname, const std::string& originator) {
  return gs::cnf::GCnf_Api::is_used(parname);
}
bool cci::cnf::gs_cci_cnf_broker::is_used(const std::string &parname, sc_core::sc_object* originator) {
  assert(originator);
  return is_used(parname, originator->name());
}

const std::vector<std::string> cci::cnf::gs_cci_cnf_broker::get_param_list(const std::string& originator) {
  return gs::cnf::GCnf_Api::getParamList();
}
const std::vector<std::string> cci::cnf::gs_cci_cnf_broker::get_param_list(sc_core::sc_object* originator) {
  assert(originator);
  return get_param_list(originator->name());
}

cci::shared_ptr<cci::cnf::callb_adapt_b> cci::cnf::gs_cci_cnf_broker::register_callback(const std::string& parname, const callback_type type, cci::shared_ptr<cci::cnf::callb_adapt_b> callb, const std::string& originator) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return callb;
}
cci::shared_ptr<cci::cnf::callb_adapt_b> cci::cnf::gs_cci_cnf_broker::register_callback(const std::string& parname, const callback_type type, cci::shared_ptr<cci::cnf::callb_adapt_b> callb, sc_core::sc_object* originator) {
  assert(originator);
  return register_callback(parname, type, callb, originator->name());
}

void cci::cnf::gs_cci_cnf_broker::unregister_all_callbacks(void* observer, const std::string& originator) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
}
void cci::cnf::gs_cci_cnf_broker::unregister_all_callbacks(void* observer, sc_core::sc_object* originator) {
  assert(originator);
  unregister_all_callbacks(observer, originator->name());
}

bool cci::cnf::gs_cci_cnf_broker::unregister_param_callback(callb_adapt_b* callb, const std::string& originator) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}
bool cci::cnf::gs_cci_cnf_broker::unregister_param_callback(callb_adapt_b* callb, sc_core::sc_object* originator) {
  assert(originator);
  return unregister_param_callback(callb, originator->name());
}

bool cci::cnf::gs_cci_cnf_broker::has_callbacks(const std::string& parname, const std::string& originator) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}
bool cci::cnf::gs_cci_cnf_broker::has_callbacks(const std::string& parname, sc_core::sc_object* originator) {
  assert(originator);
  return has_callbacks(parname, originator->name());
}

void cci::cnf::gs_cci_cnf_broker::add_param(cci_base_param* par, const std::string& originator) {
  bool new_element = m_mirrored_registry.insert(std::pair<std::string, cci_base_param*>(par->get_name(), par)).second;
  //std::cout << name() << " (gs_cci_cnf_broker) add param " << par->get_name() << std::endl;
  assert(new_element && "The same parameter had been added twice!!");
  /*gs::gs_param_base* p = dynamic_cast<gs::gs_param_base*> (par);
   assert(p != NULL && "This demo example implementation only works with the gs parameter implementation (TODO: internally to be changed!)");
   gs::cnf::GCnf_Api::addPar(p);*/
}
void cci::cnf::gs_cci_cnf_broker::add_param(cci_base_param* par, sc_core::sc_object* originator) {
  assert(originator);
  add_param(par, originator->name());
}

void cci::cnf::gs_cci_cnf_broker::remove_param(cci_base_param* par, const std::string& originator) {
  m_mirrored_registry.erase(par->get_name());
  /*gs::gs_param_base* p = dynamic_cast<gs::gs_param_base*> (par);
   assert(p != NULL && "This demo example implementation only works with the gs parameter implementation (TODO: internally to be changed!)");
   gs::cnf::GCnf_Api::removePar(p);*/
}
void cci::cnf::gs_cci_cnf_broker::remove_param(cci_base_param* par, sc_core::sc_object* originator) {
  assert(originator);
  remove_param(par, originator->name());
}

const std::vector<std::string> cci::cnf::gs_cci_cnf_broker::get_param_list(const std::string& pattern, const std::string& originator) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "pattern limited to GreenConfig capabilities");
  return gs::cnf::GCnf_Api::getParamList(pattern);
}
const std::vector<std::string> cci::cnf::gs_cci_cnf_broker::get_param_list(const std::string& pattern, sc_core::sc_object* originator) {
  assert(originator);
  return get_param_list(pattern, originator->name());
}

const std::vector<cci::cnf::cci_base_param*> cci::cnf::gs_cci_cnf_broker::get_params(const std::string& pattern, const std::string& originator) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "pattern limited to GreenConfig capabilities");
  std::vector<cci::cnf::cci_base_param*> parvec;
  std::vector<std::string> strvec;
  strvec = get_param_list(pattern);
  std::vector<std::string>::iterator striter;
  for (striter = strvec.begin(); striter != strvec.end(); striter++) {
    cci::cnf::cci_base_param* p = get_param(*striter, originator);
    if (p) parvec.push_back(p);
  }
  return parvec;
}
const std::vector<cci::cnf::cci_base_param*> cci::cnf::gs_cci_cnf_broker::get_params(const std::string& pattern, sc_core::sc_object* originator) {
  assert(originator);
  return get_params(pattern, originator->name());
}

gs::cnf::cnf_api_if* cci::cnf::gs_cci_cnf_broker::get_gs_cnf_api() {
  return this;
}