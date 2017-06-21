/* CHANGELOG
 * Written by Josh Grooms on 20170621
 */

#pragma once
#include "IO/Console.h"
#include "IO/Members.h"
#include "IO/Property.h"
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace OpenGL
    {
        using namespace Utilities;

        /// <summary> A data structure that serves as a handle to a particular graphics resource. </summary>
        /// <typeparam name="T"> The type of the resource referred to by this handle. </typeparam>
        template<typename T> struct Resource<T, true>
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
                Resource(const string& name = "Null", T* value = nullptr):
                    _name(name),
                    _value(value)
                {

                }
                Resource(Resource&& other) = default;
                //    Resource()
                //{
                //    std::swap(_name, other._name);
                //    std::swap(_value, other._value);
                //    other._value = nullptr;
                //}
                //Resource(const Resource&)
                //{
                //    Console::WriteLine("Copy Constructor");
                //}
                ~Resource()                                                 { if (_value) { delete _value; } }
                    



                /** UTILITIES **/
                template<typename U, typename ... V>
                auto Get(Attribute<U, V...> property)                       const { return property(_value); }
                template<typename U, typename V>
                U Get(Getter<U, V> accessor)                                const { return accessor(_value); }
                template<typename U, typename V = T>
                U Get(ConstMethodPointer<U, V> accessor)                    const { return (_value->*accessor)(); }

                template<typename U, typename V>
                void Set(Attribute<U, V> property, U value)                 const { property(_value, value); }
                template<typename U, typename V, typename W>
                void Set(Attribute<U, V, W> property, W value)              const { property(_value, value); }

                template<typename U, typename V, typename W>
                U Set(MethodPointer<U, V, W> accessor, W arguments)         { return (_value->*accessor)(arguments); }



                /** OPERATORS **/
                template<typename U, typename V>
                Property<U, V> operator [](Attribute<U, V> property)        const { return Property<U, V>(_value, property); }


                template<typename U> operator Resource<U, false>()          const
                {
                    static_assert(Meta::IsA<T, U>() || Meta::IsA<U, T>(), "Invalid casting operation attempted.");
                    return Resource<U, false>(_name, dynamic_cast<U*>(_value));
                }
                operator Resource<T, false>()                               const
                {
                    return Component<T>(_name, _value);
                }

                T& operator *()                                             { return *_value; }
                const T& operator *()                                       const { return *_value; }
                T* operator ->()                                            { return _value; }
                const T* operator ->()                                      const { return _value; }

                Resource& operator =(const Resource&)
                {
                    return *this;
                }
                Resource& operator =(Resource&& other) = default;
                //{
                //    std::swap(_name, other._name);
                //    std::swap(_value, other._value);
                //    return *this;
                //}

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
