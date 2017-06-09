/* CHANGELOG
 * Written by Josh Grooms on 20170608
 */

#pragma once
#include "Meta/Function.h"



namespace Cyclone
{
    namespace Utilities
    {
        template<typename T, typename U>
        struct Property<T, U, void>: public Member<T, U>
        {
            private:

                Member<T, U>*   _get;

            public:

                Property(U* object, MethodPointer<T, U> get):
                    Member<T, U>(object),
                    _get(new Method<T, U>(object, get))
                {

                }
                Property(U* object, ConstMethodPointer<T, U> get):
                    Member<T, U>(object),
                    _get(new ConstMethod<T, U>(object, get))
                {

                }
                Property(U* object, const Member<T, U>* get):
                    Member<T, U>(object),
                    _get(get->Copy())
                {

                }
                ~Property() { if (_get) { delete _get; } }


                Property* Copy()                                        const override { return new Property(_object, _get); }
                T Invoke()                                              const override { return _get->Invoke(); }

                T operator ()()                                         const override { return Invoke(); }
                bool operator ==(const ICallback<T>& other)             const override
                {
                    const auto* fcn = dynamic_cast<const Property*>(&other);
                    return (fcn != nullptr) && (_object == fcn->_object) && (_get == fcn->_get);
                }
        };

        template<typename T, typename U>
        struct Property<void, T, U>: public Member<void, T, U>
        {
            private:
                
                Member<T&, T, U>* _set;

            public:

                Property(U* object, MethodPointer<T&, T, U> set):
                    Member<T&, T, U>(object),
                    _set(new Method<T&, T, U>(object, set))
                {

                }
                Property(U* object, ConstMethodPointer<T&, T, U> set):
                    Member<T&, T, U>(object),
                    _set(new ConstMethod<T&, T, U>(object, set))
                {

                }
                Property(U* object, const Member<T&, T, U>* set):
                    Member<T&, T, U>(object),
                    _set(set->Copy())
                {

                }
                ~Property()
                {
                    if (_set) { delete _set; }
                }


                Property* Copy()                                    const override { return new Property(_object, _set); }
                T& Invoke(U argument)                               const override { return _set->Invoke(argument); }

                T& operator ()(U argument)                          const override { }
        };

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
        struct Accessor<MemberPointer<T, U>>:
            public Functor<MemberPointer<T, U>>
        {
            using Functor::Functor;
            T operator ()(U* object, T value)                   const { return (object->*_value) = value; }
            T operator ()(U& object, T value)                   const { return (object.*_value) = value; }
        };
        template<typename T, typename U, typename ... V>
        struct Accessor<ConstMethodPointer<T, U, V...>>:        public Functor<ConstMethodPointer<T, U, V...>>
        {
            using Functor::Functor;
            T operator ()(U* object, V ... arguments)           const { return (object->*_value)(arguments...); }
            T operator ()(U& object, V ... arguments)           const { return (object.*_value)(arguments...); }
        };
        template<typename T, typename U, typename ... V>
        struct Accessor<MethodPointer<T, U, V...>>:             public Functor<MethodPointer<T, U, V...>>
        {
            using Functor::Functor;
            T operator ()(U* object, V ... arguments)           const { return (object->*_value)(arguments...); }
            T operator ()(U& object, V ... arguments)           const { return (object.*_value)(arguments...); }
        };



        template<typename T, typename U, typename V> struct Property2
        {
            using ValueType = typename Meta::Functor<U>::Output;

            private:

                Property2<void, U, V>   _accessors;
                T*                      _object;

            public:
                
                Property2(T* object, U get, V set): 
                    _accessors(get, set),
                    _object(object)
                {

                }
                Property2(T* object, Property2<void, U, V> accessors):
                    _accessors(accessors),
                    _object(object)
                {

                }



                template<typename ... W>
                auto operator ()(W ... arguments)               const { return _accessors(_object, arguments...); }


                operator ValueType() const { return operator ()(); }
                Property2 operator =(ValueType value)           { _accessors(_object, value); return *this; }

        };

        template<typename U, typename V> struct Property2<void, U, V>
        {
            private:
                Accessor<U> _get;
                Accessor<V> _set;

            public:
                
                Property2(Accessor<U> get, Accessor<V> set): 
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


    }
}
