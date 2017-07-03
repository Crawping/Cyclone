/* CHANGELOG
 * Written by Josh Grooms on 20170701
 */

#pragma once
#include "Collections/Array.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, uint ... N> struct Node
        {

            /** STATIC DATA **/
            constexpr const static uint Degree  = Math::Product(N...);
            constexpr const static uint Rank    = sizeof...(N);

            private:
                
                Array<Node*, N...>  _adjacencies;
                T                   _value;

            public:

                /** PROPERTIES **/
                constexpr const T& Value()      const { return _value; }
                template<typename U> Node& Value(U&& value)
                {
                    _value = std::forward<U>(value);
                    return *this;
                }



                /** CONSTRUCTORS **/
                constexpr Node():
                    _adjacencies { nullptr },
                    _value()
                {

                }
                template<typename U> constexpr Node(U&& value):
                    _adjacencies { nullptr },
                    _value(std::forward<U>(value))
                {

                }
                ~Node()
                {
                    for (Node* n : _adjacencies)
                        delete n;
                }



                /** OPERATORS **/
                //constexpr T* operator ->()                              { return std::addressof(_value); }
                //constexpr const T* operator ->()                        const { return std::addressof(_value); }

                template<typename ... U>
                constexpr auto& operator ()(U ... subscripts)           { return _adjacencies(subscripts...); }
                template<typename ... U>
                constexpr const auto& operator ()(U ... subscripts)     const { return _adjacencies(subscripts...); }

                constexpr auto& operator ()(const Array<uint, Rank>& subscripts)
                {
                    return _adjacencies( _adjacencies.IndexOf(subscripts) );
                }
                constexpr const auto& operator ()(const Array<uint, Rank>& subscripts) const
                {
                    return _adjacencies( _adjacencies.IndexOf(subscripts) );
                }

        };


        


        template<typename T> struct BinaryNode:     public Node<T, 2>
        {
            using Node::Node;

            constexpr Node*& Left()                     { return operator ()(0); }
            constexpr const Node*& Left()               const { return operator ()(0); }
            constexpr Node*& Right()                    { return operator ()(1); }
            constexpr const Node*& Right()              const { return operator ()(1); }
        };




    }
}



/** SPECIALIZATIONS **/
#include "Graphs/Specializations/DynamicNode.h"