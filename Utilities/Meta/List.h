/* CHANGELOG
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "Meta/Primitives.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {
            template<typename ... T> struct List;

            template<uint N, typename T, typename ... U> struct Node        : public Node<N - 1, U...> { };
            template<typename T, typename ... U> struct Node<0, T, U...>    : public Class<T> { };
            template<typename T, typename ... U> struct Sublist             : public List<U...> { };

            template<typename ... T>
            struct List
            {

                /** PROPERTIES **/
                /// <summary> Gets the number of types present in the list. </summary>
                using Count                                     = Integer32U<sizeof...(T)>;
                /// <summary> Gets the first type present in the list. </summary>
                using First                                     = Node<0, T...>;
                /// <summary> Gets whether the list has any stored types. </summary>
                using IsEmpty                                   = Boolean<false>;
                /// <summary> Gets the last type present in the list. </summary>
                using Last                                      = Node<sizeof...(T) - 1, T...>;


                /** UTILITIES **/
                template<typename ... U> using Concatenate      = List<T..., U...>;
                using Discard                                   = Sublist<T...>;
                template<uint N> using Get                      = Node<N, T...>;

                template<uint N, typename S>
                constexpr static auto Cast(S x)
                {
                    return (Get<N>::Type)x;
                }
            };
        }
    }
}
