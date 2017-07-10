/* CHANGELOG
 * Written by Josh Grooms on 20170708
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A structure that represents a generic graph node. </summary>
        /// <typeparam name="T"> The type of the data element held by the node. </typeparam>
        /// <typeparam name="N"> A list of integers that define the dimensionality and degree of the node's adjacency array. </typeparam>
        template<typename T> struct Node<T, 2>
        {

            /** STATIC DATA **/
            /// <summary> The number of connections that could be formed with other nodes. </summary>
            constexpr const static uint Degree  = 2;
            /// <summary> The number of dimensions present in the array that holds adjacent nodes. </summary>
            constexpr const static uint Rank    = 1;

            private:
                
                Array<Node*, 2> _adjacencies;
                T               _value;

            public:

                /** PROPERTIES **/
                constexpr Node*& Left()         { return operator ()(0); }
                constexpr const Node*& Left()   const { return operator ()(0); }
                constexpr Node*& Right()        { return operator ()(1); }
                constexpr const Node*& Right()  const { return operator ()(1); }
                constexpr T& Value()            { return _value; }
                /// <summary> Gets the value of the data element stored within the node. </summary>
                constexpr const T& Value()      const { return _value; }

                /// <summary> Sets the value of the data element stored within the node. </summary>
                template<typename U> Node& Value(U&& value)
                {
                    _value = std::forward<U>(value);
                    return *this;
                }



                /** CONSTRUCTORS **/
                /// <summary> Constructs a new empty graph node. </summary>
                constexpr Node():
                    _adjacencies { nullptr },
                    _value()
                {

                }
                /// <summary> Constructs a new graph node containing a particular data value. </summary>
                /// <param name="value"> The data value to be stored in the node. </param>
                template<typename U> constexpr Node(U&& value):
                    _adjacencies { nullptr },
                    _value(std::forward<U>(value))
                {

                }



                /** OPERATORS **/
                /// <summary> Gets the adjacent node stored at a particular index. </summary>
                /// <typeparam name="U"> A list of unsigned 32-bit integers. </typeparam>
                /// <param name="subscripts"> A single linear index, or a list of array subscripts. </param>
                template<typename ... U>
                constexpr auto& operator ()(U ... subscripts)           { return _adjacencies(subscripts...); }
                /// <summary> Gets the adjacent node stored at a particular index. </summary>
                /// <typeparam name="U"> A list of unsigned 32-bit integers. </typeparam>
                /// <param name="subscripts"> A single linear index, or a list of array subscripts. </param>
                template<typename ... U>
                constexpr const auto& operator ()(U ... subscripts)     const { return _adjacencies(subscripts...); }

                /// <summary> Gets the adjacent node stored at a particular multidimensional index. </summary>
                /// <param name="subscripts"> An array of subscripts that index into the node. </param>
                constexpr auto& operator ()(const Array<uint, Rank>& subscripts)
                {
                    return _adjacencies( _adjacencies.IndexOf(subscripts) );
                }
                constexpr const auto& operator ()(const Array<uint, Rank>& subscripts) const
                {
                    return _adjacencies( _adjacencies.IndexOf(subscripts) );
                }

        };

        template<typename T> using BinaryNode = Node<T, 2>;

    }
}
