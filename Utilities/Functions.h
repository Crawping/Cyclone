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
        /// <summary> An alias that represents a general parameterized function pointer with one return argument. </summary>
        /// <typeparam name="T"> The function's output argument class. </typeparam>
        /// <typeparam name="U"> A listing of the function's input argument classes. </typeparam>
        template<typename T, typename ... U>
        using FunctionPointer = T(*)(U ... arguments);

        /// <summary> An alias that represents a general parameterized class method pointer with no return argument. </summary>
        /// <typeparam name="T"> The class to which the method belongs. </typeparam>
        /// <typeparam name="U"> A listing of the method's input argument classes. </typeparam>
        template<typename T, typename ... U>
        using MethodPointer = void (T::*)(U ... arguments);

        /// <summary> An alias that represents a general parameterized procedure pointer with no output arguments. </summary>
        /// <typeparam name="T"> A listing of the procedure's input argument classes. </typeparam>
        template<typename ... T>
        using ProcedurePointer = void(*)(T ... arguments);



        /** FUNCTIONS **/
        /// <summary> An interface that represents a parameterized callback procedure. </summary>
        template<typename ... T>
        struct ICallback
        {
            virtual ~ICallback() { }

            virtual void Invoke(T ... arguments)                    const = 0;

            virtual bool operator ==(const ICallback<T...>& other)  const = 0;
            virtual bool operator !=(const ICallback<T...>& other)  const { return !(operator ==(other)); }
        };

        /// <summary> A structure that represents a pointer to an ordinary function. </summary>
        template<typename T, typename ... U>
        struct Function
        {
            private:
                /// <summary> A pointer to the function that can be invoked through this structure. </summary>
                FunctionPointer<T, U...>    _function;

            public:

                /// <summary> Constructs a new function object that refers to a specific function pointer. </summary>
                /// <param name="function"> The specific function to be stored. </param>
                Function(FunctionPointer<T, U...> function) : 
                    _function(function)
                {

                }

                T Invoke(U ... arguments)   const { return _function(arguments...); }
        };

        /// <summary> A structure that represents a pointer to a class method. </summary>
        template<typename T, typename ... U>
        struct Method : public ICallback<U...>
        {
            private:
                /// <summary> A pointer to the object instance needed to succesfully call a class method. </summary>
                T*                         _object;
                /// <summary> A pointer to the method function that will eventually be called. </summary>
                MethodPointer<T, U...>     _method;

            public:

                /// <summary> Constructs a new method object referring to a specific class instance function. </summary>
                /// <param name="object"> An instance of the class on which the method will be called. </param>
                /// <param name="method"> A specific class method to be called on the object. </param>
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

        /// <summary> A structure that represents a pointer to an ordinary procedure. </summary>
        template<typename ... T>
        struct Procedure : public ICallback<T...>
        {
            private:

                /// <summary> A pointer to the procedure that can be invoked through this class. </summary>
                ProcedurePointer<T...> _procedure;

            public:

                /// <summary> Constructs a new procedure object referring to a specific function pointer. </summary>
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
