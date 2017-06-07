/* CHANGELOG
 * Written by Josh Grooms on 20170605
 */

#pragma once

#include "IO/Functions.h"



namespace Cyclone
{
    namespace OpenGL
    {
        using namespace Utilities;

        template<typename T>
        struct Resource
        {
            friend class ResourceLibrary2;
            private:

                string  _name;
                T*      _value;

            public:

                /** PROPERTIES **/
                bool IsNull()                               const { return _value == nullptr; }
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
                T* operator ->()                            { return _value; }
                const T* operator ->()                      const { return _value; }

                bool operator ==(const Resource& other)     const
                {
                    return (_name == other._name) && _value == other._value;
                }
                template<typename U>
                bool operator ==(const Resource<U>& other)  const { return false; }

                template<typename U>
                bool operator !=(const Resource<U>& other)  const { return !(operator ==(other)); }
        };


        



    }
}