/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "TypeDefinitions.h"
#include "Meta/Primitives.h"



namespace Cyclone
{
    namespace Reflection
    {
        namespace Meta
        {

            template<bool S, typename T, typename U> 
            struct Conditional                                  : public T { };
        
            template<typename T, typename U>
            struct Conditional<false, T, U>                     : public U { };

            /// <summary> Determines whether two types are equivalent. </summary>
            template<typename T, typename U> struct IsEqual     : Boolean<false> { };
            /// <summary> Determines whether two types are equivalent. </summary>
            template<typename T> struct IsEqual<T, T>           : Boolean<true> { };

            template<typename T> struct Dereference             : Class<T> { };
            template<typename T> struct Dereference<T*>         : Dereference<T> { };
            template<typename T> struct Dereference<const T*>   : Dereference<T> { };
            template<typename T> struct Dereference<T&>         : Dereference<T> { };
            template<typename T> struct Dereference<const T&>   : Dereference<T> { };

            template<typename T> struct IsPointer               : Boolean<false> { };
            template<typename T> struct IsPointer<T*>           : Boolean<true> { };
            template<typename T> struct IsPointer<const T*>     : Boolean<true> { };

            template<typename T> struct IsReference             : Boolean<false> { };
            template<typename T> struct IsReference<T&>         : Boolean<true> { };
            template<typename T> struct IsReference<const T&>   : Boolean<true> { };

            template<typename T> struct IsVoid                  : IsEqual<T, void> { };

            template<typename T> struct SizeOf                  : Primitive<uint, sizeof( Dereference<T>::Type )> { };
            template<> struct SizeOf<void>                      : Primitive<uint, 0> { };


            template<typename T> 
            constexpr Class<T> TypeOf(T value)                  { return Class<T>() }

            template<typename T, typename U>
            constexpr bool TypeEquals(T x, U y)                 { return IsEqual<T, U>(); }

            template<typename T, typename U>
            constexpr bool TypeEquals(U x)                      { return IsEqual<T, U>(); }

        }
    }
}
