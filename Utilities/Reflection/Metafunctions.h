/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            template<typename T, T U> struct Primitive          { constexpr operator T() const { return U; } };
            template<bool value> struct Boolean                 : Primitive<bool, value> { };


            template<bool S, typename T, typename U> 
            struct Conditional                                  { using Result = T; };
        
            template<typename T, typename U>
            struct Conditional<false, T, U>                     { using Result = U; };


            template<typename T, typename U> struct IsEqual     : Boolean<false> { };
            template<typename T> struct IsEqual<T, T>           : Boolean<true> { };

            template<typename T> struct Dereference             { using Class = T; };
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

            template<typename T> struct IsVoid                  : IsEqual<void, T> { };

            template<typename T> struct SizeOf                  : Primitive<uint, sizeof( Dereference<T>::Class )> { };
            template<> struct SizeOf<void>                      : Primitive<uint, 0> { };

        }
    }
}
