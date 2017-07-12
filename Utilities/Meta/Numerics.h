/* CHANGELOG
 * Written by Josh Grooms on 20170629
 */

#pragma once
#include "Collections/Array.h"
#include <limits>



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            /// <summary> The smallest possible difference between two sequential numbers of the given type. </summary>
            template<typename T> constexpr T Epsilon            = std::numeric_limits<T>::epsilon();

            template<typename T> constexpr bool IsIntegral      = std::numeric_limits<T>::is_integer;
            /// <summary> Determines whether a value is a native C++ numeric type. </summary>
            template<typename T> constexpr bool IsNative        = std::numeric_limits<T>::is_specialized;
            /// <summary> Determines whether a value is a signed numeric type. </summary>
            template<typename T> constexpr bool IsSigned        = std::numeric_limits<T>::is_signed();
            /// <summary> The maximum possible value of a numeric type. </summary>
            /// <typeparam name="T"> The type whose maximum value is to be returned. </typeparam>
            template<typename T> constexpr T Maximum            = std::numeric_limits<T>::max();
            /// <summary> The minimum possible value of a numeric type. </summary>
            /// <typeparam name="T"> The type whose minimum value is to be returned. </typeparam>
            template<typename T> constexpr T Minimum            = std::numeric_limits<T>::min();
            /// <summary> The full dynamic range of a numeric type. </summary>
            /// <returns> A two-element array containing the (minimum, maximum) values of the given type. </returns>
            /// <typeparam name="T"> The type whose minimum and maximum values are to be returned. </typeparam>
            template<typename T> constexpr auto Limits          = Array<T, 2>{ Minimum, Maximum };

        }
    }
}
