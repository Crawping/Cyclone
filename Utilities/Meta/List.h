/* CHANGELOG
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "Math/Math.h"
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {
            template<typename ... T> struct List;

            template<uint N, typename T, typename ... U> struct Node:                   public Node<N - 1, U...> { };
            template<typename T, typename ... U> struct Node<0, T, U...>:               public Class<T> { };

            template<uint N, typename T, typename ... U> struct Sublist:                public Sublist<N - 1, U...> { };
            template<typename T, typename ... U> struct Sublist<0, T, U...>:            public List<T, U...> { };

            /// <summary> A metaclass that stores and manages a collection of heterogeneous types. </summary>
            template<typename ... T>
            struct List
            {

                /** PROPERTIES **/
                /// <summary> Gets the number of types present in the list. </summary>
                constexpr const static uint Count               = sizeof...(T);
                /// <summary> Gets the first type present in the list. </summary>
                using First                                     = Node<0, T...>;
                /// <summary> Gets whether the list has any stored types. </summary>
                using IsEmpty                                   = Boolean<false>;
                /// <summary> Gets the last type present in the list. </summary>
                using Last                                      = Node<sizeof...(T) - 1, T...>;
                /// <summary> Gets the total number of bytes required to store an instance of every type in the list. </summary>
                constexpr const static uint Size                = Math::Sum(sizeof(T)...);
                /// <summary> A vector containing the byte sizes of each type stored in the list. </summary>
                constexpr const static uint Sizes[]             = { sizeof(T)... };



                /** UTILITIES **/
                /// <summary> Appends additional types to the list. </summary>
                /// <typeparam name="U"> Any number of additional types to be added to the end of the list. </typeparam>
                template<typename ... U> using Concatenate      = List<T..., U...>;
                /// <summary> Removes the first type stored in the list. </summary>
                using Discard                                   = Sublist<1, T...>;
                /// <summary> Retrieves the type stored at a particular index in the list. </summary>
                template<uint N> using Get                      = typename Node<N, T...>::Type;

                /// <summary> Determines whether a given type is related to a specific type stored in the list. </summary>
                /// <returns> A Boolean <c>true</c> if the inputted type is related to the stored one, or <c>false</c> otherwise. </returns>
                /// <typeparam name="U"> A type to be tested against the one stored at the inputted index. </typeparam>
                /// <param name="index"> The linear array index of the stored type. </param>
                template<typename U> constexpr static bool IsA(uint index)
                {
                    return index ? Discard::IsA<U>(index - 1) : Meta::IsA<U, Get<0>>();
                }
                /// <summary> Determines whether a given type is equivalent to a specific type stored in the list. s</summary>
                /// <returns> A Boolean <c>true</c> if the inputted type is equal to the stored one, or <c>false</c> otherwise. </returns>
                /// <typeparam name="U"> A type to be tested against the one stored at the inputted index. </typeparam>
                /// <param name="index"> The linear array index of the stored type. </param>
                template<typename U> constexpr static bool IsEqual(uint index)
                {
                    return index ? Discard::IsEqual<U>(index - 1) : Meta::IsEqual<U, Get<0>>();
                }

            };
        }
    }
}



/** SPECIALIZATIONS **/
#include "Meta/Specializations/EmptyList.h"