/* CHANGELOG
 * Written by Josh Grooms on 20170608
 */

#pragma once
#include "IO/Functions.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, typename U, typename ... V>
        struct Member: public ICallback<T, V...>
        {
            protected:
                /// <summary> A pointer to the object instance needed to call a class member. </summary> 
                U* _object;

                Member(U* object): _object(object) { }

            public:

                Member* Copy()                                  const = 0;
        };

        template<typename T, typename U>
        struct Field: public Member<T, U>
        {
            private:
                
                MemberPointer<T, U>     _field;

            public:

                Field(U* object, MemberPointer<T, U> field):
                    Member(object),
                    _field(field)
                {

                }

                Field* Copy()                                   const override { return Field(_object, _field); }
                T Invoke()                                      const override { return (_object->*_field); }
                void Invoke(T value)                            { (_object->*_field) = value; }

                T operator ()()                                 const override { return Invoke(); }
                void operator ()(T value)                       { Invoke(value); }
                bool operator ==(const ICallback<T>& other)     const override
                {
                    return (dynamic_cast<Field<T, U>*>(&other) != nullptr);
                }
        };

        /// <summary> A structure that represents a pointer to a class method. </summary>
        /// <typeparam name="T"> The name of the class to which the method belongs. </typeparam>
        /// <typeparam name="U"> A list of types that match the class method's input argument signature. </typeparam>
        template<typename T, typename U, typename ... V>
        struct Method: public Member<T, U, V...>
        {
            private:
                
                /// <summary> A pointer to the method function that will eventually be called. </summary>
                MethodPointer<T, U, V...>   _method;

            public:

                /// <summary> Constructs a new method object referring to a specific class instance function. </summary>
                /// <param name="object"> An instance of the class on which the method will be called. </param>
                /// <param name="method"> A specific class method to be called on the object. </param>
                Method(U* object, MethodPointer<T, U, V...> method):
                    Member(object),
                    _method(method)
                {

                }

                Method* Copy()                                       const override { return new Method(_object, _method); }
                /// <summary> Executes the class method using the specified input arguments. </summary>
                /// <param name="arguments"> An argument list that matches the signature of the class method. </param>
                T Invoke(V ... arguments)                            const override { return (_object->*_method)(arguments...); }

                bool operator ==(const ICallback<T, V...>& other)    const override
                {
                    const auto* mtd = dynamic_cast<const Method<T, U, V...>*>(&other);
                    return mtd ? (_object == mtd->_object) && (_method == mtd->_method) : false;
                }
        };

        template<typename T, typename U, typename ... V>
        struct ConstMethod: public Member<T, U, V...>
        {
            private:

                ConstMethodPointer<T, U, V...>  _method;

            public:

                ConstMethod(U* object, ConstMethodPointer<T, U, V...> method):
                    Member(object)
                {

                }

                ConstMethod* Copy()                                 const override { return new ConstMethod(_object, _method); }
                T Invoke(V ... arguments)                           const override { return (_object->*_method)(arguments...); }

                bool operator ==(const ICallback<T, V...>& other)   const override
                {
                    const auto* fcn = dynamic_cast<const ConstMethod<T, U, V...>*>(&other);
                    return (fcn != nullptr) && (_object == fcn->_object) && (_method == fcn->_method);
                }
        };

        template<typename T, typename U, typename V>
        struct Property: public Member<T, U>
        {

            private:

                Member<T, U>*       _get;
                Member<U&, U, V>*   _set;

            public:

                Property(U* object, MethodPointer<T, U> get, MethodPointer<U&, U, V> set = nullptr):
                    //Property(object, Method<T, U>(object, get), Method<U&, U, V>(object, set))
                    Member(object),
                    _get(new Method<T, U>(object, get)),
                    _set(new Method<U&, U, V>(object, set))
                {

                }
                Property(U* object, ConstMethodPointer<T, U> get, MethodPointer<U&, U, V> set = nullptr):
                    Member(object),
                    _get(new ConstMethod<T, U>(object, get)),
                    _set(new Method<U&, U, V>(object, set))
                {

                }
                Property(U* object, const Member<T, U>* get, const Member<U&, U, V>* set):
                    Member(object),
                    _get(get->Copy()),
                    _set(set->Copy())
                {

                }

                //Property(U* object, Method<T, U> get, Method<U&, U, V> set):
                //    Member(object),
                //    _get(get),
                //    _set(set)
                //{

                //}
                ~Property()
                {
                    if (_get) { delete _get; }
                    if (_set) { delete _set; }
                }

                Property* Copy()                                        const override { return new Property(_object, _get, _set); }
                T Invoke()                                              const override { return _get->Invoke(); }
                U& Invoke(V argument)                                   { return _set->Invoke(argument); }

                T operator ()()                                         const override { return Invoke(); }
                U& operator ()(V argument)                              { return Invoke(argument); }
                bool operator ==(const ICallback<T>& other)             const override
                {
                    const auto* fcn = dynamic_cast<const Property*>(&other);
                    return (fcn != nullptr) && (fcn->_get == _get) && (fcn->_set == _set);
                }

        };
    }
}
