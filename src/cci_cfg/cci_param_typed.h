/*****************************************************************************
  Copyright 2006-2015 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2006-2014 OFFIS Institute for Information Technology
  All rights reserved.

  Copyright 2006-2015 Intel Corporation
  All rights reserved.

  Copyright 2016 Ericsson
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

#ifndef CCI_CCI_PARAM_TYPED_H_INCLUDED_
#define CCI_CCI_PARAM_TYPED_H_INCLUDED_

#include "cci_cfg/cci_param_untyped.h"
#include "cci_cfg/cci_param_untyped_handle.h"
#include "cci_cfg/cci_report_handler.h"

/**
 * @author Enrico Galli, Intel
 */
CCI_OPEN_NAMESPACE_

// Convenient name
#define cci_param cci_param_typed

/// Parameter class, internally forwarding calls to the implementation
/**
 * The implementation is in file cci_param_typed.hpp, which has to be included
 * in the headers as well because the class is a template class.
 *
 * Documentation for the undocumented functions can be found in
 * cci_param_if
 */
template<typename T, param_mutable_type TM = mutable_param>
class cci_param_typed : public cci_param_untyped
{
public:
    /// The parameter's value type.
    typedef T value_type;

    ///Assigns parameter a new value from another parameter
    /**
     * @param rhs New value to assign
     * @return reference to this object
     */
    cci_param_typed& operator= (const cci_param_typed & rhs);

    ///Assigns parameter a new value from another legacy parameter
    /**
     * @param rhs New value to assign
     * @return reference to this object
     */
    cci_param_typed& operator= (const cci_param_if & rhs);

    ///Assigns parameter a new value from another parameter handle
    /**
     * @param rhs New value to assign
     * @return reference to this object
     */
    cci_param_typed& operator= (
            const cci_param_typed_handle<value_type> & rhs);

    ///Assigns parameter a new value from another untyped parameter handle
    /**
     * @param rhs New value to assign
     * @return reference to this object
     */
    cci_param_typed& operator= (const cci_param_untyped_handle & rhs);

    ///Assigns parameter a new value
    /**
     * @param rhs New value to assign
     * @return reference to this object
     */
    cci_param_typed& operator= (const value_type & rhs);

    ///Conversion operator to be able use cci_param_typed as a regular object
    operator const value_type& () const;
    
    ///Sets the stored value to a new value 
    /**
     * @param value new value to assign
     */
    void set(const value_type& value);
    ///Sets the stored value to a new value 
    /**
     * @param value new value to assign
     * @param pwd Password needed to unlock the param, ideally any pointer address known only by the locking entity, default = NULL
     */
    void set(const value_type & value, const void * pwd);

    ///Get the value passed in via constructor
    const value_type & get_default_value();

    /// Get a pointer to the stored value.
    /**
     * @return Pointer to type-punned value
     */
    const void* get_raw_value() const;

    ///Conversion operator to be able use cci_param_typed as a regular object
    const value_type& get_value() const;

    /// Get a pointer to the default value (passed in via constructor).
    /**
     * @return Pointer to type-punned default value
     */
    const void* get_default_value_raw() const;

    /// Sets the value via type-punned argument.
    /**
     * @param vp pointer to type-punned value
     * @pre Type of vp must be equal to the internal type
     */
    void set_raw_value(const void* vp);

    /// Sets the value via type-punned argument.
    /**
     * @param vp pointer to type-punned value
     * @param originator reference to the originator
     * @pre Type of vp must be equal to the internal type
     */
    void set_raw_value(const void* vp, const cci_originator& originator);

    /// Sets the value via type-punned argument.
    /**
     * @param vp pointer to type-punned value
     * @param pwd Password needed to unlock the param, ideally any pointer address known only by the locking entity, default = NULL
     * @pre Type of vp must be equal to the internal type
     */
    void set_raw_value(const void* vp, const void* pwd);

    /// Sets the value via type-punned argument.
    /**
     * @param vp pointer to type-punned value
     * @param pwd Password needed to unlock the param, ideally any pointer address known only by the locking entity, default = NULL
     * @param originator reference to the originator
     * @pre Type of vp must be equal to the internal type
     */
    void set_raw_value(const void* vp, const void* pwd, const cci_originator& originator);

    ///@name Type-punned value operations
    ///@{

    /// Compare parameter handle values.
    /**
     * @param rhs reference to another cci_param_untyped_handle implementation
     * @return True if both values are equal and of the same data type
     */
    bool equals(const cci_param_untyped_handle& rhs) const;

    /// Compare parameter values.
    /**
     * @param rhs reference to another cci_param_if implementation
     * @return True if both values are equal and of the same data type
     */
    bool equals(const cci_param_if& rhs) const;

    /// Returns a basic type this parameter can be converted to or from (which is not necessarily the actual parameter type).
    /**
     * @return Type
     */
    basic_param_type get_basic_type() const;

    /// Returns the type information of the parameter
    /**
     * @return Type information
     */
    const std::type_info& get_type_info() const;

    ///@}

    ///@name CCI value Data Type and access
    ///@{

    /// Set the parameter's value to the given one.
    /**
     * @exception cci_exception_set_param Setting value failed
     * @param val This value is either (in the case of a pure basic param) converted into a JSON string and stored in the base param or (in the case of a typed parameter) into the actual data type
     */
    void set_cci_value(const cci_value& val);

    /// Set the parameter's value to the given one.
    /**
     * @exception cci_exception_set_param Setting value failed
     * @param val This value is either (in the case of a pure basic param) converted into a JSON string and stored in the base param or (in the case of a typed parameter) into the actual data type
     * @param originator reference to the originator
     */
    void set_cci_value(const cci_value& val, const cci_originator& originator);

    /// Get the parameter's value.
    /**
     * @exception cci_exception_get_param Getting value failed
     * @return This value is either (in the case of a pure basic param) converted from the JSON string or (in the case of a typed parameter) from the actual data type
     */
    cci_value get_cci_value() const;

    ///@}

    /// @name Post write callback handling
    /// @{

    // Untyped callbacks

    /// @copydoc cci_param_untyped::register_post_write_callback(const cci_param_post_write_callback_untyped, cci_untyped_tag)
    cci_callback_untyped_handle register_post_write_callback(
            const cci_param_post_write_callback_untyped &cb,
            cci_untyped_tag);

    /// @copydoc cci_param_untyped::register_post_write_callback(cci_param_post_write_callback_untyped::signature, C*, cci_untyped_tag)
    template<typename C>
    cci_callback_untyped_handle register_post_write_callback(
            cci_param_post_write_callback_untyped::signature (C::*cb), C* obj,
            cci_untyped_tag);

    // Typed callbacks

    /// Typed write callback type
    typedef typename cci_param_post_write_callback<value_type>::type
            cci_param_post_write_callback_typed;

    /// Register a typed write callback.
    /**
     * @param cb Typed write callback
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    cci_callback_untyped_handle register_post_write_callback(
            const cci_param_post_write_callback_typed &cb,
            cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// Register a typed write callback with a method as callback
    /**
     * @param cb Typed write callback method
     * @param obj Associated object instance pointer
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    template<typename C>
    cci_callback_untyped_handle register_post_write_callback(
            typename cci_param_post_write_callback_typed::signature (C::*cb),
            C* obj, cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// @}

    /// @name Pre write callback handling
    /// @{

    // Untyped callbacks

    /// @copydoc cci_param_untyped::register_pre_write_callback(const cci_param_pre_write_callback_untyped, cci_untyped_tag)
    cci_callback_untyped_handle register_pre_write_callback(
            const cci_param_pre_write_callback_untyped &cb,
            cci_untyped_tag);

    /// @copydoc cci_param_untyped::register_pre_write_callback(cci_param_pre_write_callback_untyped::signature, C*, cci_untyped_tag)
    template<typename C>
    cci_callback_untyped_handle register_pre_write_callback(
            cci_param_pre_write_callback_untyped::signature (C::*cb),
            C* obj, cci_untyped_tag);

    // Typed callbacks

    /// Typed pre write callback type
    typedef typename cci_param_pre_write_callback<value_type>::type
            cci_param_pre_write_callback_typed;

    /// Register a typed pre write callback.
    /**
     * @param cb Typed pre write callback
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    cci_callback_untyped_handle register_pre_write_callback(
            const cci_param_pre_write_callback_typed &cb,
            cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// Register a typed pre write callback with a method as callback
    /**
     * @param cb Typed pre write callback method
     * @param obj Associated object instance pointer
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    template<typename C>
    cci_callback_untyped_handle register_pre_write_callback(
            typename cci_param_pre_write_callback_typed::signature
            (C::*cb), C* obj,
            cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// @}

    /// @name Pre read callback handling
    /// @{

    // Untyped callbacks

    /// @copydoc cci_param_untyped::register_pre_read_callback(const cci_param_pre_read_callback_untyped, cci_untyped_tag)
    cci_callback_untyped_handle register_pre_read_callback(
            const cci_param_pre_read_callback_untyped &cb,
            cci_untyped_tag);

    /// @copydoc cci_param_untyped::register_pre_read_callback(cci_param_pre_read_callback_untyped::signature, C*, cci_untyped_tag)
    template<typename C>
    cci_callback_untyped_handle register_pre_read_callback(
            cci_param_pre_read_callback_untyped::signature (C::*cb), C* obj,
            cci_untyped_tag);

    // Typed callbacks

    /// Typed read callback type
    typedef typename cci_param_pre_read_callback<value_type>::type
            cci_param_pre_read_callback_typed;

    /// Register a typed read callback.
    /**
     * @param cb Typed read callback
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    cci_callback_untyped_handle register_pre_read_callback(
            const cci_param_pre_read_callback_typed &cb,
            cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// Register a typed read callback with a method as callback
    /**
     * @param cb Typed read callback method
     * @param obj Associated object instance pointer
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    template<typename C>
    cci_callback_untyped_handle register_pre_read_callback(
            typename cci_param_pre_read_callback_typed::signature (C::*cb), C* obj,
            cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// @}

    /// @name Post read callback handling
    /// @{

    // Untyped callbacks

    /// @copydoc cci_param_untyped::register_post_read_callback(const cci_param_post_read_callback_untyped, cci_untyped_tag)
    cci_callback_untyped_handle register_post_read_callback(
            const cci_param_post_read_callback_untyped &cb,
            cci_untyped_tag);

    /// @copydoc cci_param_untyped::register_post_read_callback(cci_param_post_read_callback_untyped::signature, C*, cci_untyped_tag)
    template<typename C>
    cci_callback_untyped_handle register_post_read_callback(
            cci_param_post_read_callback_untyped::signature (C::*cb), C* obj,
            cci_untyped_tag);

    // Typed callbacks

    /// Typed read callback type
    typedef typename cci_param_post_read_callback<value_type>::type
            cci_param_post_read_callback_typed;

    /// Register a typed post read callback.
    /**
     * @param cb Typed post read callback
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    cci_callback_untyped_handle register_post_read_callback(
            const cci_param_post_read_callback_typed &cb,
            cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// Register a typed post read callback with a method as callback
    /**
     * @param cb Typed post read callback method
     * @param obj Associated object instance pointer
     * @param cci_typed_tag Typed tag to avoid compiler ambiguity
     *
     * @return Untyped callback handle
     */
    template<typename C>
    cci_callback_untyped_handle register_post_read_callback(
            typename cci_param_post_read_callback_typed::signature (C::*cb), C* obj,
            cci_typed_tag<value_type> = cci_typed_tag<value_type>());

    /// @}

    /// Free resources attached to parameter.
    void destroy();

    ///Creates a parameter handle object holding the originator information and pointing to the same parameter
    /**
     * This shall be used by the broker when returning a not yet created parameter handle.
     *
     * @param originator  Originator object the returned parameter handle shall represent
     * @return  A newed copy pointing to the same implementation parameter.
     *          Memory management has to be done by the caller!
     */
    cci_param_untyped_handle create_param_handle(const cci_originator& originator);

    /**
     * Constructor with (local/hierarchical) name, default value,
     * description and originator.
     *
     * @param name Name of the parameter
     * @param default_value Default value of the parameter (Typed value)
     * @param desc Description of the parameter
     * @param name_type Either the name should be absolute or relative
     * @param originator Originator of the parameter
     */
    cci_param_typed(const std::string& name, const value_type& default_value,
                    const std::string& desc = "",
                    cci_name_type name_type = CCI_RELATIVE_NAME,
                    const cci_originator& originator = cci_originator());

    /**
     * Constructor with (local/hierarchical) name, default value,
     * description and originator.
     *
     * @param name Name of the parameter
     * @param default_value Default value of the parameter (CCI value)
     * @param desc Description of the parameter
     * @param name_type Either the name should be absolute or relative
     * @param originator Originator of the parameter
     */
    cci_param_typed(const std::string& name, const cci_value& default_value,
                    const std::string& desc = "",
                    cci_name_type name_type = CCI_RELATIVE_NAME,
                    const cci_originator& originator = cci_originator());

    /**
     * Constructor with (local/hierarchical) name, default value,
     * private broker, description, name type and originator.
     *
     * @param name Name of the parameter
     * @param default_value Default value of the parameter (Typed value)
     * @param private_broker Associated private broker
     * @param desc Description of the parameter
     * @param name_type Either the name should be absolute or relative
     * @param originator Originator of the parameter
     */
    cci_param_typed(const std::string& name, const value_type& default_value,
                    cci_broker_if& private_broker,
                    const std::string& desc = "",
                    cci_name_type name_type = CCI_RELATIVE_NAME,
                    const cci_originator& originator = cci_originator());

    /**
     * Constructor with (local/hierarchical) name, default value,
     * private broker, description, name type and originator.
     *
     * @param name Name of the parameter
     * @param default_value Default value of the parameter (CCI value)
     * @param private_broker Associated private broker
     * @param desc Description of the parameter
     * @param name_type Either the name should be absolute or relative
     * @param originator Originator of the parameter
     */
    cci_param_typed(const std::string& name, const cci_value& default_value,
                    cci_broker_if& private_broker,
                    const std::string& desc = "",
                    cci_name_type name_type = CCI_RELATIVE_NAME,
                    const cci_originator& originator = cci_originator());

protected:
    /// GS Parameter internal
    gs::gs_param<value_type>* m_gs_param;

private:
    /// Constructor to create handles with a giver originator
    cci_param_typed(cci_param_typed<value_type, TM> & copy, const cci_originator& originator);

    /// Verify kernel phase for elaboration time parameters
    /**
     * Before setValue is called for elaboration parameter updates,
     * this function is called to determine whether the value updates
     * shall be rejected or not
     */
    bool isScElabPhase() {
        if (sc_core::sc_get_status() & (sc_core::SC_BEFORE_END_OF_ELABORATION |
                                        sc_core::SC_ELABORATION |
                                        sc_core::SC_END_OF_ELABORATION)) {
            return true;
        } else {
            return false;
        }
    }

    /// Check whether value update is allowed
    bool set_cci_value_allowed()
    {
        if (TM == elaboration_time_param) {
            if(!isScElabPhase()) {
                cci_report_handler::set_param_failed("Attempt to set elaboration parameter during simulation.");
                return false;
            }
        } else if (TM == immutable_param) {
            cci_report_handler::set_param_failed("Parameter is immutable.");
            return false;
        }
        return true;
    }

    /// Pre write callback
    bool
    pre_write_callback(value_type value,
                       const cci_originator &originator) const
    {
        bool result = true;

        // Write callback payload
        cci_param_write_event <value_type> ev(m_gs_param->getValue(),
                                              value,
                                              originator);

        // Validate write callbacks
        for (unsigned i = 0; i < m_pre_write_callbacks.size(); ++i) {
            typename cci_param_pre_write_callback_handle<value_type>::type
                    typed_pre_write_cb(
                    m_pre_write_callbacks[i].callback);
            if (!typed_pre_write_cb.invoke(
                    static_cast<
                            const cci_param_write_event <value_type> >(ev))) {
                // Write denied
                cci_report_handler::set_param_failed(
                        "Value rejected by callback.");
                result = false;
            }
        }
        return result;
    }

    /// Post write callback
    void post_write_callback(const value_type& old_value,
                             const value_type& new_value,
                             const cci_originator &originator) const
    {
        // Write callback payload
        const cci_param_write_event <value_type> ev(old_value,
                                                    new_value,
                                                    originator);

        // Write callbacks
        for (unsigned i = 0; i < m_post_write_callbacks.size(); ++i) {
            typename cci_param_post_write_callback_handle<value_type>::type
                    typed_post_write_cb(m_post_write_callbacks[i].callback);
            if (typed_post_write_cb.valid()) {
                typed_post_write_cb.invoke(ev);
            }
        }
    }

    /// Pre read callback
    void pre_read_callback(const value_type& value) const
    {
        // Read callback payload
        const cci_param_read_event <value_type> ev(value, get_originator());

        // Read callbacks
        for (unsigned i = 0; i < m_pre_read_callbacks.size(); ++i) {
            typename cci_param_pre_read_callback_handle<value_type>::type
                    typed_pre_read_cb(m_pre_read_callbacks[i].callback);
            if (typed_pre_read_cb.valid()) {
                typed_pre_read_cb.invoke(ev);
            }
        }
    }

    /// Pre read callback
    void post_read_callback(const value_type& value) const
    {
        // Read callback payload
        const cci_param_read_event <value_type> ev(value, get_originator());

        // Read callbacks
        for (unsigned i = 0; i < m_post_read_callbacks.size(); ++i) {
            typename cci_param_post_read_callback_handle<value_type>::type
                    typed_pre_read_cb(m_post_read_callbacks[i].callback);
            if (typed_pre_read_cb.valid()) {
                typed_pre_read_cb.invoke(ev);
            }
        }
    }
};

template <typename T, param_mutable_type TM>
cci_param_typed<typename cci_param_typed<T, TM>::value_type, TM>&
cci_param_typed<T, TM>::operator=(const cci_param_typed<T,
        TM>& rhs)
{
    set(rhs.get_value());
    return *this;
}

template <typename T, param_mutable_type TM>
cci_param_typed<typename cci_param_typed<T, TM>::value_type, TM>&
cci_param_typed<T, TM>::operator=(const cci_param_if& rhs)
{
    set_cci_value(rhs.get_cci_value());
    return *this;
}

template <typename T, param_mutable_type TM>
cci_param_typed<typename cci_param_typed<T, TM>::value_type, TM>&
cci_param_typed<T, TM>::operator=(
        const cci_param_typed_handle<T>& rhs)
{
    set(rhs.get_value());
    return *this;
}

template <typename T, param_mutable_type TM>
cci_param_typed<typename cci_param_typed<T, TM>::value_type, TM>&
cci_param_typed<T, TM>::operator=(const cci_param_untyped_handle& rhs)
{
    set_cci_value(rhs.get_cci_value());
    return *this;
}

template <typename T, param_mutable_type TM>
cci_param_typed<typename cci_param_typed<T, TM>::value_type, TM>&
cci_param_typed<T, TM>::operator=(const T& rhs)
{
    set(rhs);
    return *this;
}

template <typename T, param_mutable_type TM>
cci_param_typed<T, TM>::operator const T&() const
{
    return get_value();
}

template <typename T, param_mutable_type TM>
const T& cci_param_typed<T, TM>::get_value() const
{
    pre_read_callback(m_gs_param->getValue());
    post_read_callback(m_gs_param->getValue());
    return m_gs_param->getValue();
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set_raw_value(const void* value)
{
    set_raw_value(value, get_originator());
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set_raw_value(
        const void* value, const cci_originator& originator)
{
    set_raw_value(value, NULL, originator);
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set_raw_value(const void* value,
                                                    const void *pwd)
{
    set_raw_value(value, pwd, get_originator());
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set_raw_value(const void* value,
                                           const void *pwd,
                                           const cci_originator& originator)
{
    value_type old_value = m_gs_param->getValue();
    value_type new_value = *static_cast<const value_type*>(value);

    if(!pwd) {
        if (m_gs_param->locked()) {
            cci_report_handler::set_param_failed("Parameter locked.");
            return;
        }
    } else {
        if (!m_gs_param->check_pwd(pwd)) {
            cci_report_handler::set_param_failed("Wrong key.");
            return;
        }
    }

    if (set_cci_value_allowed() && pre_write_callback(new_value, originator)) {
        bool actual_write_result = false;

        // Actual write
        if(!pwd) {
            // TODO: remove dependency
            actual_write_result = m_gs_param->setValue(new_value);
        } else {
            // TODO: remove dependency
            actual_write_result = m_gs_param->setValue(new_value, pwd);
        }
        if (!actual_write_result) {
            cci_report_handler::set_param_failed("Bad value.");
            return;
        } else {
            // Write callback(s)
            post_write_callback(old_value, new_value, originator);

            // Update latest write originator
            update_latest_write_originator(originator);
        }
    }
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set(const T& value)
{
    set_raw_value(&value);
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set(const T& value,
                                          const void *pwd)
{
    set_raw_value(&value, pwd);
}

template <typename T, param_mutable_type TM>
const void* cci_param_typed<T, TM>::get_raw_value() const
{
    const value_type& value = get_value();
    pre_read_callback(value);
    post_read_callback(value);
    return static_cast<const void*>(&value);
}

template <typename T, param_mutable_type TM>
bool cci_param_typed<T, TM>::equals(
        const cci_param_untyped_handle& rhs) const
{
    return rhs.equals(*this);
}

template <typename T, param_mutable_type TM>
bool cci_param_typed<T, TM>::equals(const cci_param_if& rhs) const
{
    const cci_param_typed<value_type, TM>* other =
            dynamic_cast<const cci_param_typed<value_type, TM>*>(&rhs);
    if (other)
    {
        return other->m_gs_param->getValue() == this->m_gs_param->getValue();
    }
    return false;
}

template <typename T, param_mutable_type TM>
basic_param_type cci_param_typed<T, TM>::get_basic_type() const
{
    return get_cci_value().basic_type();
}

template <typename T, param_mutable_type TM>
const std::type_info& cci_param_typed<T, TM>::get_type_info() const
{
    return typeid(value_type);
}

template <typename T, param_mutable_type TM>
const void* cci_param_typed<T, TM>::get_default_value_raw() const {
    if (!this->m_gs_param->has_default_value()) // TODO: remove dependency and check (all cci_param have a default value)
        cci_report_handler::get_param_failed(
                "Param has no default value.");
    return &this->m_gs_param->get_default_value();
}

template <typename T, param_mutable_type TM>
const typename cci_param_typed<T, TM>::value_type&
cci_param_typed<T, TM>::get_default_value()
{
    return *static_cast<const value_type *>(get_default_value_raw());
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set_cci_value(const cci_value& val)
{
    set_cci_value(val, get_originator());
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::set_cci_value(const cci_value& val,
                               const cci_originator& originator)
{
    value_type v = val.get<value_type>();
    set_raw_value(&v, originator);
}

template <typename T, param_mutable_type TM>
cci_value cci_param_typed<T, TM>::get_cci_value() const {
    const value_type& value = this->m_gs_param->getValue();
    pre_read_callback(value);
    post_read_callback(value);
    return cci_value(value);
}

// Callbacks

#define CCI_PARAM_TYPED_CALLBACK_IMPL_(name)                                   \
template <typename T, param_mutable_type TM>                                   \
cci_callback_untyped_handle                                                    \
cci_param_typed<T, TM>::register_##name##_callback(                            \
        const cci_param_##name##_callback_untyped &cb,                         \
        cci_untyped_tag)                                                       \
{                                                                              \
    return cci_param_untyped::register_##name##_callback(cb);                  \
}                                                                              \
                                                                               \
template <typename T, param_mutable_type TM>                                   \
template<typename C>                                                           \
cci_callback_untyped_handle                                                    \
cci_param_typed<T, TM>::register_##name##_callback(                            \
        cci_param_##name##_callback_untyped::signature (C::*cb), C* obj,       \
        cci_untyped_tag)                                                       \
{                                                                              \
    return cci_param_untyped::register_##name##_callback(cb, obj);             \
}                                                                              \
                                                                               \
template <typename T, param_mutable_type TM>                                   \
cci_callback_untyped_handle                                                    \
cci_param_typed<T, TM>::register_##name##_callback(                            \
        const cci_param_##name##_callback_typed &cb, cci_typed_tag<T>)         \
{                                                                              \
    return cci_param_untyped::register_##name##_callback(cb, m_originator);    \
}                                                                              \
                                                                               \
template <typename T, param_mutable_type TM>                                   \
template <typename C>                                                          \
cci_callback_untyped_handle                                                    \
cci_param_typed<T, TM>::register_##name##_callback(                            \
        typename cci_param_##name##_callback_typed::signature (C::*cb),        \
        C* obj, cci_typed_tag<T>)                                              \
{                                                                              \
    return register_##name##_callback(sc_bind(cb, obj, sc_unnamed::_1));       \
}

// Pre write callback
CCI_PARAM_TYPED_CALLBACK_IMPL_(pre_write)

// Post write callback
CCI_PARAM_TYPED_CALLBACK_IMPL_(post_write)

// Pre read callback
CCI_PARAM_TYPED_CALLBACK_IMPL_(pre_read)

// Post read callback
CCI_PARAM_TYPED_CALLBACK_IMPL_(post_read)

template <typename T, param_mutable_type TM>
cci_param_untyped_handle cci_param_typed<T, TM>::create_param_handle(
        const cci_originator& originator)
{
    return cci_param_typed_handle<value_type>(*this, originator);
}

template <typename T, param_mutable_type TM>
void cci_param_typed<T, TM>::destroy()
{
    delete this;
}

/// Constructors

#define CCI_PARAM_CONSTRUCTOR_CCI_VALUE_IMPL(signature, broker)                \
template <typename T, param_mutable_type TM>                                   \
cci_param_typed<T, TM>::cci_param_typed signature                              \
: cci_param_untyped((name_type == CCI_RELATIVE_NAME) ? false : true, &broker,  \
                    desc, originator),                                         \
  m_gs_param(new gs::gs_param<T>(name, "", NULL,                               \
             (name_type == CCI_RELATIVE_NAME) ? false : true, true))           \
{                                                                              \
    m_gs_param->setString(default_value.to_json());                            \
    cci_param_untyped::m_gs_param_base = m_gs_param;                           \
    broker.add_param(this);                                                    \
    this->init();                                                              \
}

#define CCI_PARAM_CONSTRUCTOR_IMPL(signature, broker)                          \
template <typename T, param_mutable_type TM>                                   \
cci_param_typed<T, TM>::cci_param_typed signature                              \
: cci_param_untyped((name_type == CCI_RELATIVE_NAME) ? false : true, &broker,  \
                    desc, originator),                                         \
  m_gs_param(new gs::gs_param<T>(name, default_value,                          \
             (name_type == CCI_RELATIVE_NAME) ? false : true))                 \
{                                                                              \
    cci_param_untyped::m_gs_param_base = m_gs_param;                           \
    cci_value init_value = broker.get_initial_cci_value(get_name());           \
    if(!init_value.is_null()) {                                                \
        m_gs_param->setString(init_value.to_json());                           \
    }                                                                          \
    broker.add_param(this);                                                    \
    this->init();                                                              \
}

/// Constructor with (local/hierarchical) name, default value, description,
/// name type and originator.
CCI_PARAM_CONSTRUCTOR_IMPL((const std::string& name,
                            const value_type& default_value,
                            const std::string& desc,
                            cci_name_type name_type,
                            const cci_originator& originator),
                            cci_broker_manager::get_current_broker(
                                originator))

/// Constructor with (local/hierarchical) name, default value, description,
/// name type and originator.
CCI_PARAM_CONSTRUCTOR_CCI_VALUE_IMPL((const std::string& name,
                                      const cci_value& default_value,
                                      const std::string& desc,
                                      cci_name_type name_type,
                                      const cci_originator& originator),
                                      cci_broker_manager::get_current_broker(
                                          originator))

/// Constructor with (local/hierarchical) name, default value, private broker,
/// description, name type and originator.
CCI_PARAM_CONSTRUCTOR_IMPL((const std::string& name,
                            const value_type& default_value,
                            cci_broker_if& private_broker,
                            const std::string& desc,
                            cci_name_type name_type,
                            const cci_originator& originator),
                            private_broker)

/// Constructor with (local/hierarchical) name, default value, private broker,
/// description, name type and originator.
CCI_PARAM_CONSTRUCTOR_CCI_VALUE_IMPL((const std::string& name,
                                      const cci_value& default_value,
                                      cci_broker_if& private_broker,
                                      const std::string& desc,
                                      cci_name_type name_type,
                                      const cci_originator& originator),
                                      private_broker)

#undef CCI_PARAM_CONSTRUCTOR_IMPL
#undef CCI_PARAM_CONSTRUCTOR_CCI_VALUE_IMPL
#undef CCI_PARAM_TYPED_CALLBACK_IMPL_

template <typename T, param_mutable_type TM>
cci_param_typed<T, TM>::cci_param_typed(cci_param_typed<T, TM>& copy, const cci_originator& originator)
: cci_param_untyped(copy, originator),
  m_gs_param(copy.m_gs_param)
{
    cci_param_untyped::m_gs_param_base = m_gs_param;
}

CCI_CLOSE_NAMESPACE_

#endif //CCI_CNF_CCI_PARAM_H_INCLUDED_