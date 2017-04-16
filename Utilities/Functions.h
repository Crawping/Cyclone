/* CHANGELOG
 * Written by Josh Grooms on 20170107
 */

#pragma once
#include "TypeDefinitions.h"
#include "Interfaces/ICallback.h"



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
        template<typename T, typename U, typename ... V>
        using MethodPointer = T(U::*)(V ... arguments);

        /// <summary> An alias that represents a general parameterized procedure pointer with no output arguments. </summary>
        /// <typeparam name="T"> A listing of the procedure's input argument classes. </typeparam>
        template<typename ... T>
        using ProcedurePointer = void(*)(T ... arguments);



        /** FUNCTIONS **/
        /// <summary> A structure that represents a pointer to an ordinary function. </summary>
        /// <typeparam name="T"> The type of the function's output argument. </typeparam>
        /// <typeparam name="U"> A list of types that match the function's input argument signature. </typeparam>
        template<typename T, typename ... U>
        struct Function : public ICallback<T, U...>
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

                /// <summary> Executes the function using the specified input arguments. </summary>
                /// <param name="arguments"> An argument list that matches the signature of the function. </param>
                /// <returns></returns>
                T Invoke(U ... arguments)   const override { return _function(arguments...); }


                bool operator ==(const ICallback<T, U...>& other) const
                {
                    const auto* fcn = dynamic_cast<const Function<T, U...>*>(&other);
                    return fcn ? (_function == fcn->_function) : false;
                }
        };

        /// <summary> A structure that represents a pointer to a class method. </summary>
        /// <typeparam name="T"> The name of the class to which the method belongs. </typeparam>
        /// <typeparam name="U"> A list of types that match the class method's input argument signature. </typeparam>
        template<typename T, typename U, typename ... V>
        struct Method : public ICallback<T, V...>
        {
            private:
                /// <summary> A pointer to the object instance needed to succesfully call a class method. </summary>
                U*                          _object;
                /// <summary> A pointer to the method function that will eventually be called. </summary>
                MethodPointer<T, U, V...>   _method;

            public:

                /// <summary> Constructs a new method object referring to a specific class instance function. </summary>
                /// <param name="object"> An instance of the class on which the method will be called. </param>
                /// <param name="method"> A specific class method to be called on the object. </param>
                Method(U* object, MethodPointer<T, U, V...> method) :
                    _object(object),
                    _method(method)
                {

                }

                /// <summary> Executes the class method using the specified input arguments. </summary>
                /// <param name="arguments"> An argument list that matches the signature of the class method. </param>
                T Invoke(V ... arguments)                            const override { return (_object->*_method)(arguments...); }

                bool operator ==(const ICallback<T, V...>& other)    const override
                {
                    const auto* mtd = dynamic_cast<const Method<T, U, V...>*>(&other);
                    return mtd ? (_object == mtd->_object) && (_method == mtd->_method) : false;
                }
        };

        /// <summary> A structure that represents a pointer to an ordinary procedure. </summary>
        /// <typeparam name="T"> A list of types that match the procedure's input argument signature. </typeparam>
        template<typename ... T>
        struct Procedure : public ICallback<void, T...>
        {
            private:

                /// <summary> A pointer to the procedure that can be invoked through this class. </summary>
                ProcedurePointer<T...> _procedure;

            public:

                /// <summary> Constructs a new procedure object referring to a specific function pointer. </summary>
                /// <param name="fcn"></param>
                Procedure(ProcedurePointer<T...> fcn) : 
                    _procedure(fcn) 
                { 
                
                }

                /// <summary> Executes the procedure using the specified input arguments. </summary>
                /// <param name="arguments"> An argument list that matches the signature of the procedure. </param>
                void Invoke(T ... arguments)                            const override { _procedure(arguments...); }

                bool operator ==(const ICallback<void, T...>& other)    const override
                {
                    const auto* fcn = dynamic_cast<const Procedure<T...>*>(&other);
                    return fcn ? (_procedure == fcn->_procedure) : false;
                }
        };

    }
}
