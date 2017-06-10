/* CHANGELOG
 * Written by Josh Grooms on 20170609
 */

#pragma once
#include "IO/Members.h"



namespace Cyclone
{
    namespace Utilities
    {
        
        template<typename T, typename U, typename ... V> struct Property { };

        template<typename T, typename U, typename V> 
        struct Property<T, U, V>
        {
            using OutputType = typename Meta::Functor<U>::Output;
            using InputType = typename Meta::Functor<V>::Inputs::First::Type;

            private:

                Property<void, U, V>    _accessors;
                T*                      _object;

            public:
                
                Property(T* object, U get, V set):
                    _accessors(get, set),
                    _object(object)
                {

                }
                Property(T* object, Property<void, U, V> accessors):
                    _accessors(accessors),
                    _object(object)
                {

                }



                /** UTILITIES **/
                Property<void, U, V> Unbind()                   const { return _accessors; }


                template<typename ... W>
                auto operator ()(W ... arguments)               const { return _accessors(_object, arguments...); }


                operator OutputType()                           const { return _accessors(_object); }
                Property& operator =(InputType value)           { _accessors(_object, value); return *this; }


                bool operator ==(OutputType value)              const { return (_accessors(_object) == value); }
                bool operator !=(OutputType value)              const { return !operator ==(value); }

        };

        template<typename U, typename V> struct Property<void, U, V>
        {
            private:

                Accessor<U> _get;
                Accessor<V> _set;

            public:
                
                Property(Accessor<U> get, Accessor<V> set): 
                    _get(get), 
                    _set(set) 
                {

                }



                /** UTILITIES **/
                template<typename T>
                Property<T, U, V> Bind(T* object)               const { return Property<T, U, V>(object, *this); }



                /** OPERATORS **/
                template<typename W>
                auto operator ()(W& object)                     const { return _get(object); }

                template<typename W>
                auto operator ()(W* object)                     const { return _get(object); }

                template<typename W, typename ... X>
                void operator ()(W& object, X ... values)       const { _set(object, values...); }

                template<typename W, typename ... X>
                void operator ()(W* object, X ... values)       const { _set(object, values...); }
        };


        template<typename T, typename ... U>
        struct property { };

        template<typename T, typename U>
        struct property<T, U>:              public Property< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, U> > 
        { 
            using Property::Property; 
            using Property::operator =;
        };

        template<typename T, typename U, typename V>
        struct property<T, U, V>:           public Property< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, V> >
        {
            using Property::Property;
            using Property::operator =;
        };

    }
}