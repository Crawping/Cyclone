/* CHANGELOG
 * Written by Josh Grooms on 20170609
 */

#pragma once
#include "IO/Members.h"



namespace Cyclone
{
    namespace Utilities
    {
        
        //template<typename T, typename U> struct FreeProperty;
        template<typename T, typename ... U> struct PropertyBase { };

        template<typename T, typename U, typename V> 
        struct PropertyBase<T, U, V>
        {
            using OutputType = typename Meta::Functor<U>::Output;
            using InputType = typename Meta::Functor<V>::Inputs::First::Type;

            private:

                PropertyBase<void, U, V>    _accessors;
                T*                          _object;

            public:
                
                PropertyBase(T* object, U get, V set):
                    _accessors(get, set),
                    _object(object)
                {

                }
                PropertyBase(T* object, PropertyBase<void, U, V> accessors):
                    _accessors(accessors),
                    _object(object)
                {

                }



                /** UTILITIES **/
                PropertyBase<void, U, V> Unbind()               const { return _accessors; }


                template<typename ... W>
                auto operator ()(W ... arguments)               const { return _accessors(_object, arguments...); }


                operator OutputType()                           const { return _accessors(_object); }
                PropertyBase& operator =(InputType value)       { _accessors(_object, value); return *this; }

                template<typename W, typename ... X>
                PropertyBase& operator =(PropertyBase<W, X...> value)
                {
                    using Other = PropertyBase<W, X...>;
                    static_assert(Meta::IsA< Other::OutputType, InputType >(),
                        "Types must agree.");

                    _accessors(_object, value());
                    return *this;
                }


                bool operator ==(OutputType value)              const { return (_accessors(_object) == value); }
                bool operator !=(OutputType value)              const { return !operator ==(value); }

        };

        template<typename T, typename U> 
        struct PropertyBase<void, T, U>
        {
            using OutputType = typename Meta::Functor<T>::Output;
            using InputType = typename Meta::Functor<U>::Inputs::First::Type;

            private:

                Accessor<T> _get;
                Accessor<U> _set;

            public:
                
                PropertyBase(Accessor<T> get, Accessor<U> set): 
                    _get(get), 
                    _set(set) 
                {

                }



                /** UTILITIES **/
                template<typename V>
                PropertyBase<V, T, U> Bind(T* object)           const { return PropertyBase<V, T, U>(object, *this); }



                /** OPERATORS **/
                template<typename W>
                auto operator ()(W& object)                     const { return _get(object); }

                template<typename W>
                auto operator ()(W* object)                     const { return _get(object); }

                template<typename W, typename ... X>
                void operator ()(W& object, X ... values)       const { _set(object, values...); }

                template<typename W, typename ... X>
                void operator ()(W* object, X ... values)       const { _set(object, values...); }


                bool operator ==(const PropertyBase& other)     const { return (_get == other._get) && (_set == other._set); }
                bool operator !=(const PropertyBase& other)     const { return !operator ==(other); }
        };

        template<typename T, typename ... U>
        struct Property { };

        template<typename T, typename U>
        struct Property<T, U>:              public PropertyBase< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, U> > 
        { 
            using PropertyBase::PropertyBase; 
            using PropertyBase::operator =;
        };

        template<typename T, typename U, typename V>
        struct Property<T, U, V>:           public PropertyBase< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, V> >
        {
            using PropertyBase::PropertyBase;
            using PropertyBase::operator =;
        };



        template<typename T, typename ... U> struct Attribute { };

        template<typename T, typename U>
        struct Attribute<T, U>:             public PropertyBase< void, ConstMethodPointer<U, T>, MethodPointer<T&, T, U> > 
        {
            using PropertyBase::PropertyBase;
        };

        template<typename T, typename U, typename V>
        struct Attribute<T, U, V>:          public PropertyBase< void, ConstMethodPointer<U, T>, MethodPointer<T&, T, V> >
        {
            using PropertyBase::PropertyBase;
        };

    }
}