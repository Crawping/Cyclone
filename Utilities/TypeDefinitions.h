/* CHANGELOG
 * Written by Josh Grooms on 20160517
 */

#pragma once
#include <string>



namespace Cyclone
{
    namespace Utilities
    {

        /** PRIMITIVE NUMERIC TYPES **/
        typedef int8_t      byte;
        typedef uint8_t     ubyte;
        typedef uint32_t    uint;
        typedef uint64_t    ulong;
        typedef uint16_t    ushort;

        typedef ulong       Window;

        using std::string;



        /** ALIASES **/
        /// <summary> An alias that represents a general parameterized function pointer. </summary>
        /// <typeparam name="T"> The type of the function's output argument. </typeparam>
        /// <typeparam name="U"> A list of the function's input argument types. </typeparam>
        template<typename T, typename ... U>
        using FunctionPointer = T(*)(U ... arguments);

        /// <summary> An alias that represents a general class data member pointer. </summary>
        /// <typeparam name="T"> The type of the data stored by the class member. </typeparam>
        /// <typeparam name="U"> The class to which the data member belongs. </typeparam>
        template<typename T, typename U>
        using MemberPointer = T(U::*);

        /// <summary> An alias that represents a general parameterized class method pointer. </summary>
        /// <typeparam name="T"> The type of the method's output argument. </typeparam>
        /// <typeparam name="U"> The class to which the method belongs. </typeparam>
        /// <typeparam name="V"> A list of the method's input argument types. </typeparam>
        template<typename T, typename U, typename ... V>
        using MethodPointer = T(U::*)(V ... arguments);

        /// <summary> An alias that represents a constant-qualified class method pointer. </summary>
        /// <typeparam name="T"> The type of the method's output argument. </typeparam>
        /// <typeparam name="U"> The class to which the method belongs. </typeparam>
        /// <typeparam name="V"> A list of the method's input argument types. </typeparam>
        template<typename T, typename U, typename ... V>
        using ConstMethodPointer = T(U::*)(V ... arguments) const;

        /// <summary> An alias that represents a general parameterized procedure pointer with no output arguments. </summary>
        /// <typeparam name="T"> A list of the procedure's input argument types. </typeparam>
        template<typename ... T>
        using ProcedurePointer = void(*)(T ... arguments);



        /** STANDARD LIBRARY ALIASES **/
        /// <summary> An alias for the C++ standard library's initializer list collection. </summary>
        /// <typeparam name="T"> The type of the elements found within the initializer list. </typeparam>
        template<typename T> using InitialList = std::initializer_list<T>;

    }
}



