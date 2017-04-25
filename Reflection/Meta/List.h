/* CHANGELOG
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "Meta/Primitives.h"



namespace Cyclone
{
    namespace Reflection
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

                /** STATIC PROPERTIES **/
                using Count                                     = Integer32U<sizeof...(T)>;
                using First                                     = Node<0, T...>;
                using IsEmpty                                   = Boolean<false>;
                using Last                                      = Node<sizeof...(T) - 1, T...>;


                /** STATIC UTILITIES **/
                template<typename ... U> using Concatenate      = List<T..., U...>;
                using Discard                                   = Sublist<T...>;
                template<uint N> using Get                      = Node<N, T...>;

                template<uint N, typename S>
                constexpr static auto Cast(S x) -> decltype((Get<N>::Type)x)
                {
                    return (Get<N>::Type)x;
                }
            };
        }
    }
}
