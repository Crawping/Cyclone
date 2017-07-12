/* CHANGELOG
 * Written by Josh Grooms on 20170712
 */

#pragma once
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            namespace Queries
            {
                template<typename> struct Valid:        Boolean<true> { };
                struct Invalid:                         Boolean<false> { };

                template<typename T, typename U>
                static auto IsAddable(int)              -> Valid< decltype(Declare<T>() + Declare<U>(), void()) >;

                template<typename T, typename U>
                static auto IsAddable(long)             -> Invalid;

                template<typename T, typename U>
                static auto IsDivisible(int)            -> Valid< decltype(Declare<T>() / Declare<U>(), void()) >;

                template<typename T, typename U>
                static auto IsDivisible(long)           -> Invalid;

                template<typename T, typename U>
                static auto IsEquatable(int)            -> Valid< decltype(Declare<T>() == Declare<U>(), void()) >;

                template<typename T, typename U>
                static auto IsEquatable(long)           -> Invalid;

                template<typename T, typename U>
                static auto IsMultiplicable(int)        -> Valid< decltype(Declare<T>() * Declare<U>(), void()) >;

                template<typename T, typename U>
                static auto IsMultiplicable(long)       -> Invalid;

                template<typename T, typename U>
                static auto IsSubtractable(int)         -> Valid< decltype(Declare<T>() - Declare<U>(), void()) >;

                template<typename T, typename U>
                static auto IsSubtractable(long)        -> Invalid;

            }


            template<typename T, typename U = T>
            struct IsAddable:                           decltype(Queries::IsAddable<T, U>(0)) { };

            template<typename T, typename U = T>
            struct IsDivisible:                         decltype(Queries::IsDivisible<T, U>(0)) { };

            template<typename T, typename U = T>
            struct IsEquatable:                         decltype(Queries::IsEquatable<T, U>(0)) { };

            template<typename T, typename U = T>
            struct IsMultiplicable:                     decltype(Queries::IsMultiplicable<T, U>(0)) { };

            template<typename T, typename U = T>
            struct IsSubtractable:                      decltype(Queries::IsSubtractable<T, U>(0)) { };

        }

    }
}