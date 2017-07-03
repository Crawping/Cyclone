/* CHANGELOG
 * Written by Josh Grooms on 20170702
 */

#pragma once
#include "Graphs/Node.h"



namespace Cyclone
{
    namespace Utilities
    {
        template<typename T, uint ... N>
        struct Graph
        {

            /** STATIC DATA **/
            constexpr const static uint Degree  = Math::Product(N...);
            constexpr const static uint Rank    = sizeof...(N);

            private:

                Node<T, N...> _root;

            public:

                constexpr Graph()
                { 

                }
                template<typename U> constexpr Graph(U&& root):
                    _root(std::forward<U>(root))
                {

                }



                /** UTILITIES **/
                template<typename U> Graph& Set(const Array<uint, Rank>& subscripts, U&& value)
                {
                    if (_root(subscripts))
                        _root(subscripts)->Value(std::forward<U>(value));
                    else
                        _root(subscripts) = new Node<T, N...>(std::forward<U>(value));
                    return *this;
                }



                /** OPERATORS **/
                template<typename ... U>
                constexpr auto& operator ()(U ... subscripts)                           { return _root(subscripts...); }
                template<typename ... U>
                constexpr const auto& operator ()(U ... subscripts)                     const { return _root(subscripts...); }

                constexpr auto& operator ()(const Array<uint, Rank>& subscripts)        { return _root(subscripts); }
                constexpr const auto& operator ()(const Array<uint, Rank>& subscripts)  const { return _root(subscripts); }

        };
    }
}



/** SPECIALIZATIONS **/
#include "Graphs/Specializations/DynamicGraph.h"