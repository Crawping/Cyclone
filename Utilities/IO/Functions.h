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

        template<typename T, typename ... U>
        struct Constructor: public ICallback<T, U...>
        {
            /** UTILITIES **/
            Constructor* Copy()                                         const override { return new Constructor(); }
            T Invoke(U ... arguments)                                   const override { return T(arguments...); }

            bool operator ==(const ICallback<T, U...>& other)           const override 
            { 
                return ( dynamic_cast<const Constructor<T, U...>*>(&other) != nullptr );
            }
        };

        /// <summary> A structure that represents a pointer to an ordinary function. </summary>
        /// <typeparam name="T"> The type of the function's output argument. </typeparam>
        /// <typeparam name="U"> A list of types that match the function's input argument signature. </typeparam>
        template<typename T, typename ... U>
        struct Function: public ICallback<T, U...>
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

                Function* Copy()                                        const override { return new Function(_function); }
                /// <summary> Executes the function using the specified input arguments. </summary>
                /// <param name="arguments"> An argument list that matches the signature of the function. </param>
                /// <returns></returns>
                T Invoke(U ... arguments)                               const override { return _function(arguments...); }


                bool operator ==(const ICallback<T, U...>& other)       const override
                {
                    const auto* fcn = dynamic_cast<const Function<T, U...>*>(&other);
                    return fcn ? (_function == fcn->_function) : false;
                }
        };

        /// <summary> A structure that represents a pointer to an ordinary procedure. </summary>
        /// <typeparam name="T"> A list of types that match the procedure's input argument signature. </typeparam>
        template<typename ... T>
        struct Procedure: public ICallback<void, T...>
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

                Procedure* Copy()                                       const override { return new Procedure(_procedure); }
                /// <summary> Executes the procedure using the specified input arguments. </summary>
                /// <param name="arguments"> An argument list that matches the signature of the procedure. </param>
                void Invoke(T ... arguments)                            const override { _procedure(arguments...); }

                bool operator ==(const ICallback<void, T...>& other)    const override
                {
                    const auto* fcn = dynamic_cast<const Procedure*>(&other);
                    return fcn ? (_procedure == fcn->_procedure) : false;
                }
        };

    }
}
