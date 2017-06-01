/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "TypeDefinitions.h"
#include "Meta/Primitives.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            template<typename T>
            constexpr Boolean<true> IsBaseOf(const T*) { return { }; }
            template<typename T>
            constexpr Boolean<false> IsBaseOf(const void*) { return { }; }



            /// <summary> Returns one of two types depending on whether the inputted Boolean expression evaluates to true. </summary>
            /// <typeparam name="S"> A Boolean expression that resolves to either <c>true</c> or <c>false</c> at compile time. </typeparam>
            /// <typeparam name="T"> A type to be returned if the expression in <see cref="S"/> resolves to <c>true</c>. </typeparam>
            /// <typeparam name="U"> A type to be returned if the expression in <see cref="S"/> resolves to <c>false</c>. </typeparam>
            template<bool S, typename T, typename U> 
            struct Conditional                                  : public T { };
        
            template<typename T, typename U>
            struct Conditional<false, T, U>                     : public U { };

            /// <summary> Determines whether two types are equivalent. </summary>
            template<typename T, typename U> struct IsEqual     : Boolean<false> { };
            /// <summary> Determines whether two types are equivalent. </summary>
            template<typename T> struct IsEqual<T, T>           : Boolean<true> { };

            /// <summary> Removes constant, pointer, and reference symbols from a type. </summary>
            template<typename T> struct Dereference             : Class<T> { };
            template<typename T> struct Dereference<T*>         : Dereference<T> { };
            template<typename T> struct Dereference<const T*>   : Dereference<T> { };
            template<typename T> struct Dereference<T&>         : Dereference<T> { };
            template<typename T> struct Dereference<const T&>   : Dereference<T> { };

            /// <summary> Determines whether the input is constant qualified. </summary>
            template<typename T> struct IsConstant              : Boolean<false> { };
            template<typename T> struct IsConstant<const T*>    : Boolean<true> { };
            template<typename T> struct IsConstant<const T&>    : Boolean<true> { };

            template<typename T, typename U> struct IsDerived:  decltype(IsBaseOf<U>(std::declval<T*>())) { };
            template<typename T> struct IsDerived<T, T>:        Boolean<true> { };

            /// <summary> Determines whether the input represents a pointer type. </summary>
            template<typename T> struct IsPointer               : Boolean<false> { };
            template<typename T> struct IsPointer<T*>           : Boolean<true> { };
            template<typename T> struct IsPointer<const T*>     : Boolean<true> { };

            /// <summary> Determines whether the input represents a referential type. </summary>
            template<typename T> struct IsReference             : Boolean<false> { };
            template<typename T> struct IsReference<T&>         : Boolean<true> { };
            template<typename T> struct IsReference<const T&>   : Boolean<true> { };

            template<typename T> struct IsVolatile              : Boolean<false> { };
            template<typename T> struct IsVolatile<volatile T>  : Boolean<true> { };

            /// <summary> Determines whether the input represents the void type. </summary>
            template<typename T> struct IsVoid                  : IsEqual<T, void> { };

            /// <summary> Gets the number of bytes required to store instances of a specific type. </summary>
            /// <remarks> Unlike the <see cref="sizeof"/> operator, this function is safe to use with the <see cref="void"/> type. </remarks>
            template<typename T> struct SizeOf                  : Integer32U<sizeof(T)> { };
            template<> struct SizeOf<void>                      : Integer32U<0> { };


            template<typename T, typename ... U>
            constexpr auto ReturnType(T function, U ... arguments) -> decltype(function(U))
            {

            }


            


            template<typename T, typename U>
            constexpr bool TypeEquals(T x, U y)                 { return IsEqual<T, U>(); }

            template<typename T, typename U>
            constexpr bool TypeEquals(U x)                      { return IsEqual<T, U>(); }

        }
    }
}
