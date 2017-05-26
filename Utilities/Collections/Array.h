/* CHANGELOG
 * Written by Josh Grooms on 20170513
 */

#pragma once
#include "Collections/Vector.h"
#include "Meta/Array.h"



namespace Cyclone
{
    namespace Utilities
    {

        /// <summary> A class that represents a multidimensional array of data elements. </summary>
        template<typename T, uint ... U>
        class Array
        {
            private:

                /** STATIC DATA **/
                constexpr static uint _rank                     = sizeof...(U);
                constexpr static uint _count                    = Meta::Product(U...);
                constexpr static uint _size[_rank]              = { U... };



                /** DATA **/
                T _values[_count];

            public:

                /** STATIC PROPERTIES **/
                /// <summary> Gets the number of elements present in the array. </summary>
                constexpr static uint Count()                   { return _count; }
                /// <summary> Gets the number of dimensions present in the array. </summary>
                constexpr static uint Rank()                    { return _rank; }
                /// <summary> Gets the size of all array dimensions. </summary>
                constexpr static Array<uint, _rank> Size()      { return Array<uint, _rank>(_size); }



                /** PROPERTIES **/
                constexpr const T& First()                      const { return _values[0]; }
                constexpr const T& Last()                       const { return _values[Count() - 1]; }



                /** CONSTRUCTORS **/
                /// <summary> Constructs a new multidimensional array of values. </summary>
                constexpr Array():
                    _values{ 0 }
                {

                }
                constexpr Array(const T& value):
                    _values{ }
                {
                    for (uint a = 0; a < _count; a++)
                        _values[a] = value;
                }
                constexpr Array(const T values[_count]):
                    _values{ }
                {
                    for (uint a = 0; a < _count; a++)
                        _values[a] = values[a];
                }
                constexpr Array(const std::initializer_list<T>& values):
                    _values{ }
                {
                    for (uint a = 0; a < values.size(); a++)
                        _values[a] = *(values.begin() + a);
                }

                template<uint N, uint ... V>
                constexpr Array(const Array<T, V...>& values, const Array<T, N>& indices):
                    _values{ }
                {
                    for (uint a = 0; a < indices.Count(); a++)
                        _values[a] = values(indices(a));
                }



                /** UTILITIES **/
                /// <summary> Gets the total number of elements present in a specific dimension of the array. </summary>
                /// <param name="dimension"> The array dimension through which elements are to be counted. </param>
                /// <returns> The cumulative element count up through the inputted array dimension. </returns>
                constexpr static uint Count(uint dimension)
                {
                    uint count = Size(0);
                    for (uint a = 1; a <= dimension; a++)
                        count *= Size(a);
                    return count;
                }
                /// <summary> Converts the array into an equivalent one-dimensional vector of values. </summary>
                /// <returns> A flattened array of values copied from the multidimensional array. </returns>
                constexpr Array<T, _count> Flatten()                            const { return { _values }; }
                /// <summary> Gets the size of the array across a specific dimension. </summary>
                /// <param name="dimension"> A single array dimension. </param>
                /// <returns> The size of the array along the inputted dimension. </returns>
                constexpr static uint Size(uint dimension)
                {
                    return (dimension >= _rank) ? 1 : _size[dimension];
                }
                constexpr static Array<uint, _rank> SubscriptsOf(uint index)
                {

                }

                template<typename ... V>
                constexpr static uint IndexOf(V ... indices)
                { 
                    return IndexOf( Array<uint, sizeof...(V)>{ uint(indices)... } );
                }
                template<uint N>
                constexpr static uint IndexOf(const Array<uint, N>& indices)
                {
                    uint idx = indices(0U);
                    for (uint a = 1; a < indices.Count(); a++)
                        idx += indices(a) * Count(a - 1);
                    return idx;
                }

                template<uint ... V>
                constexpr Array<T, V...> Reshape()                              const
                {
                    StaticAssert< Meta::Product
                }



                /** OPERATORS **/
                constexpr const T* begin()                                      const { return &_values[0]; }
                constexpr const T* end()                                        const { return begin() + Count(); }
                virtual T& operator ()(uint index)                              { return _values[index]; }
                constexpr const T& operator ()(uint index)                      const { return _values[index]; }

                template<typename ... V>
                constexpr const T& operator ()(V ... indices)                   const { return _values[IndexOf(indices...)]; }
                template<uint N>
                constexpr Array<T, N> operator ()(const Array<T, N>& indices)   const { return Array<T, N>(*this, indices); }
                
        };

    }
}



/** SPECIALIZATIONS **/
#include "Specializations/DynamicArray.h"
#include "Specializations/NumericArray.h"
