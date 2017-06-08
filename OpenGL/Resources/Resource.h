/* CHANGELOG
 * Written by Josh Grooms on 20170605
 */

#pragma once

#include "IO/Members.h"



namespace Cyclone
{
    namespace OpenGL
    {
        using namespace Utilities;

        /// <summary> A data structure that serves as a handle to a particular graphics resource. </summary>
        template<typename T> struct Resource
        {
            friend class ResourceLibrary2;
            private:

                /** DATA **/
                string  _name;
                T*      _value;

            public:

                /** PROPERTIES **/
                /// <summary> Gets whether the resource has a null value. </summary>
                bool IsNull()                               const { return _value == nullptr; }
                /// <summary> Gets the string identifier of the resource. </summary>
                const string& Name()                        const { return _name; }



                /** CONSTRUCTOR **/
                Resource(const string& name = "", T* value = nullptr):
                    _name(name),
                    _value(value)
                {

                }



                /** UTILITIES **/
                template<typename U, typename V = T>
                U Get(MethodPointer<U, V> accessor)                         { return (_value->*accessor)(); }
                template<typename U, typename V = T>
                U Get(ConstMethodPointer<U, V> accessor)                    const { return (_value->*accessor)(); }
                template<typename U, typename V, typename W>
                U Set(MethodPointer<U, V, W> accessor, W arguments)         { return (_value->*accessor)(arguments); }
                template<typename U, typename V, typename W>
                U Set(ConstMethodPointer<U, V, W> accessor, W argument)     const { return (_value->*accessor)(argument); }



                /** OPERATORS **/
                T& operator *()                                             { return *_value; }
                T* operator ->()                                            { return _value; }
                const T* operator ->()                                      const { return _value; }

                bool operator ==(const Resource& other)                     const
                {
                    return (_name == other._name) && _value == other._value;
                }
                template<typename U>
                bool operator ==(const Resource<U>& other)                  const { return false; }

                template<typename U>
                bool operator !=(const Resource<U>& other)                  const { return !(operator ==(other)); }
        };

    }
}