/* CHANGELOG
 * Written by Josh Grooms on 20170107
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {

        /** ALIASES **/
        /// <summary> An alias that represents a general parameterized function pointer with no return argument. </summary>
        template<typename T, typename ... U>
        using FunctionPointer = T(*)(U ... arguments);

        /// <summary> An alias that represents a general parameterized class method pointer with no return argument. </summary>
        template<typename T, typename ... U>
        using MethodPointer = void (T::*)(U ... arguments);

        template<typename ... T>
        using ProcedurePointer = void(*)(T ... arguments);



        /// <summary> An interface that represents a parameterized callback procedure. </summary>
        template<typename ... T>
        struct ICallback
        {
            virtual ~ICallback() { }

            virtual void Invoke(T ... arguments)                    const = 0;

            virtual bool operator ==(const ICallback<T...>& other)  const = 0;
            virtual bool operator !=(const ICallback<T...>& other)  const { return !(operator ==(other)); }
        };

        template<typename T, typename ... U>
        struct Function
        {
            private:

                FunctionPointer<T, U...>    _function;

            public:
                
                Function(FunctionPointer<T, U...> function) : 
                    _function(function)
                {

                }

                T Invoke(U ... arguments)   const { return _function(arguments...); }
        };

        /// <summary> A structure representing a pointer to an object method. </summary>
        template<typename T, typename ... U>
        struct Method : public ICallback<U...>
        {
            private:
                /// <summary> A pointer to the object instance needed to succesfully call a class method. </summary>
                T*                         _object;
                /// <summary> A pointer to the method function that will eventually be called. </summary>
                MethodPointer<T, U...>     _method;

            public:

                Method(T* object, MethodPointer<T, U...> method) :
                    _object(object),
                    _method(method)
                {

                }

                void Invoke(U ... arguments)                    const override { (_object->*_method)(arguments...); }

                bool operator ==(const ICallback<U...>& other)  const override
                {
                    const auto* mtd = dynamic_cast<const Method<T, U...>*>(&other);
                    return mtd ? (_object == mtd->_object) && (_method == mtd->_method) : false;
                }
        };

        /// <summary> A structure representing an ordinary procedure pointer. </summary>
        template<typename ... T>
        struct Procedure : public ICallback<T...>
        {
            private:

                /// <summary> A pointer to the procedure that can be invoked through this class. </summary>
                ProcedurePointer<T...> _procedure;

            public:

                /// <summary> Constructs a new function object referring to a specific function pointer. </summary>
                /// <param name="fcn"></param>
                Procedure(ProcedurePointer<T...> fcn) : _procedure(fcn) { }

                void Invoke(T ... arguments)                    const override { _procedure(arguments...); }

                bool operator ==(const ICallback<T...>& other)  const override
                {
                    const auto* fcn = dynamic_cast<const Procedure<T...>*>(&other);
                    return fcn ? (_procedure == fcn->_procedure) : false;
                }
        };

    }
}
