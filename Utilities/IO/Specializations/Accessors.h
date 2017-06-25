/* CHANGELOG
 * Written by Josh Grooms on 20170608
 */

#pragma once
#include "Meta/Function.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T> struct Functor
        {
            protected:
                T _value;

            public:
                Functor(T value):                               _value(value) { }
        };

        template<typename T> struct Accessor { };

        template<typename T, typename ... U>
        struct Accessor<FunctionPointer<T, U...>>:
            public Functor<FunctionPointer<T>>
        {
            using Functor::Functor;
            T operator ()(void* object, U ... arguments)        const { return (_value)(arguments...); }
        };

        template<typename T, typename U>
        struct Accessor<MemberPointer<T, U>>:                   public Functor<MemberPointer<T, U>>
        {
            using Functor::Functor;

            T operator ()(U* object)                            const { return (object->*_value); }
            T operator ()(U& object)                            const { return (object.*_value); }
            T operator ()(const U* object)                      const { return (object->*_value); }
            T operator ()(const U& object)                      const { return (object.*_value); }

            T operator ()(U* object, T value)                   const { return (object->*_value) = value; }
            T operator ()(U& object, T value)                   const { return (object.*_value) = value; }
        };

        template<typename T, typename U, typename ... V>
        struct Accessor<ConstMethodPointer<T, U, V...>>:        public Functor<ConstMethodPointer<T, U, V...>>
        {
            using Functor::Functor;
            T operator ()(const U* object, V ... arguments)     const { return (object->*_value)(arguments...); }
            T operator ()(const U& object, V ... arguments)     const { return (object.*_value)(arguments...); }
        };

        template<typename T, typename U, typename ... V>
        struct Accessor<MethodPointer<T, U, V...>>:             public Functor<MethodPointer<T, U, V...>>
        {
            using Functor::Functor;
            T operator ()(U* object, V ... arguments)           const { return (object->*_value)(arguments...); }
            T operator ()(U& object, V ... arguments)           const { return (object.*_value)(arguments...); }
        };



        template<typename T, typename U>
        struct Field:                                           public Accessor< MemberPointer<T, U> > 
        {
            using Accessor::Accessor;
        };



        template<typename T, typename U>
        struct Getter:                                          public Accessor< MethodPointer<T, U> >
        {
            using Accessor::Accessor;
        };
        template<typename T, typename U>
        struct Getter<T, const U>:                              public Accessor< ConstMethodPointer<T, U> >
        {
            using Accessor::Accessor;
        };
    }
}
