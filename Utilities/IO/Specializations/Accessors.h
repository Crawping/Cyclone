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

        //template<typename T, typename U> using Getter = Property<T, U, void>;
        //template<typename T, typename U> using Setter = Property<void, T, U>;


        template<typename T>
        struct Getter: public ICallback< typename Meta::ReturnType<T>::Value >
        {
            using ReturnType = Meta::ReturnType<T>::Value;

            private:
                T _get;

            public:

                Getter(T get): _get(get) { }

                ReturnType Invoke()     const override { return _get(); }


        };


        //template<typename T, typename U>
        //struct Prop
        //{
        //    private:
        //        
        //        T _get;
        //        U _set;

        //    public:

        //        
        //}

    }
}
