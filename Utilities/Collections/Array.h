/* CHANGELOG
 * Written by Josh Grooms on 20170513
 */

#pragma once
#include "TypeDefinitions.h"
#include "Math/Math.h"



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
                constexpr static uint _count                    = Math::Product(U...);
                constexpr static uint _rank                     = sizeof...(U);
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
                /// <summary> Gets the first element present in the array. </summary>
                constexpr const T& First()                      const { return _values[0]; }
                /// <summary> Gets the last element present inthe array. </summary>
                constexpr const T& Last()                       const { return _values[Count() - 1]; }



                /** CONSTRUCTORS **/
                /// <summary> Constructs a new multidimensional array of values. </summary>
                constexpr Array():
                    _values{ 0 }
                {

                }
                /// <summary> Constructs a new multidimensional array whose elements are initialized to a uniform value. </summary>
                /// <param name="value"> The value to which all array elements will be initialized. </param>
                constexpr Array(const T& value):
                    _values{ }
                {
                    for (uint a = 0; a < _count; a++)
                        _values[a] = value;
                }
                /// <summary> Constructs a new multidimensional array by copying a native array of values. </summary>
                /// <param name="values"> A native array of values to be copied into the newly constructed one. </param>
                constexpr Array(const T values[_count]):
                    _values{ }
                {
                    for (uint a = 0; a < _count; a++)
                        _values[a] = values[a];
                }
                /// <summary> Constructs a new multidimensional array whose elements are initialized to specific values. </summary>
                /// <param name="values"> An initial list of values to copied into the new array. </param>
                constexpr Array(const InitialList<T>& values):
                    _values{ }
                {
                    for (uint a = 0; a < values.size(); a++)
                        _values[a] = *(values.begin() + a);
                }
                /// <summary> Constructs a new multidimensional array by copying a specific set of elements from another array. </summary>
                template<uint ... V>
                constexpr Array(const Array<T, V...>& values, const Array<T, _count>& indices):
                    _values{ }
                {
                    for (uint a = 0; a < _count; a++)
                        _values[a] = values(indices(a));
                }



                /** UTILITIES **/
                /// <summary> Gets the total number of elements present in a specific dimension of the array. </summary>
                /// <returns> The cumulative element count up through the inputted array dimension. </returns>
                /// <param name="dimension"> The array dimension through which elements are to be counted. </param>
                constexpr static uint Count(uint dimension)
                {
                    uint count = Size(0);
                    for (uint a = 1; a <= dimension; a++)
                        count *= Size(a);
                    return count;
                }
                /// <summary> Converts the array into an equivalent one-dimensional vector of values. </summary>
                /// <returns> A flattened array of values copied from the multidimensional array. </returns>
                constexpr Array<T, _count> Flatten()                                const { return { _values }; }
                /// <summary> Calculates a linear index that is equivalent to a set of array subscripts. </summary>
                /// <returns> A linear array index that references the same location as the inputted subscripts. </returns>
                /// <param name="subscripts"> Any number of unsigned integers representing the array subscripts to convert. </param>
                /// <remarks> Subscripts into dimensions higher than the rank of the array are ignored. </remarks>
                template<typename ... V>
                constexpr static uint IndexOf(V ... subscripts)
                { 
                    return IndexOf( Array<uint, sizeof...(V)>{ uint(subscripts)... } );
                }
                /// <summary> Calculates a linear index that is equivalent to a set of array subscripts. </summary>
                /// <returns> A linear array index that references the same location as the inputted subscripts. </returns>
                /// <param name="subscripts"> Any number of unsigned integers representing the array subscripts to convert. </param>
                /// <remarks> Subscripts into dimensions higher than the rank of the array are ignored. </remarks>
                template<uint N>
                constexpr static uint IndexOf(const Array<uint, N>& subscripts)
                {
                    constexpr uint rank = Math::Min(N, _rank);
                    uint idx = subscripts(0U);
                    for (uint a = 1; a < rank; a++)
                        idx += subscripts(a) * Count(a - 1);
                    return idx;
                }
                /// <summary> Copies the array into a new one with different dimensions. </summary>
                /// <typeparam name="V"> Any number of integers defining the size of the new array. </typeparam>
                /// <remarks> 
                ///     Note that reshaping operations require element counts to be preserved, and an exception 
                ///     will be thrown if the given dimensions would not contain the same number of elements that
                ///     are stored in the existing array.
                /// </remarks>
                template<uint ... V> constexpr Array<T, V...> Reshape()             const
                {
                    static_assert(Math::Product(V...) == _count,
                        "The number of elements in an array must not change during reshaping operations.");
                    return { _values };
                }
                /// <summary> Gets the size of the array across a specific dimension. </summary>
                /// <returns> The size of the array along the inputted dimension. </returns>
                /// <param name="dimension"> A single array dimension. </param>
                constexpr static uint Size(uint dimension)                          { return (dimension >= _rank) ? 1 : _size[dimension]; }
                /// <summary> Calculates a set of subscripts that is equivalent to a given linear array index. </summary>
                /// <returns> Array subscripts that reference the same location as the inputted linear index. </returns>
                /// <param name="index"> A single linear index into the array. </param>
                constexpr static Array<uint, _rank> SubscriptsOf(uint index)
                {
                    Array<uint, _rank> subs;
                    uint count = 0;
                    for (uint a = _rank - 1; a > 0; a--)
                    {
                        count = Count(a - 1);
                        subs(a) = index / count;
                        index %= count;
                    }
                    subs(0U) = index;
                    return subs;
                }



                /** OPERATORS **/
                /// <summary> Gets a pointer to the first element stored in the array. </summary>
                constexpr const T* begin()                                          const { return &_values[0]; }

                T* begin()                                                          { return &_values[0]; }
                /// <summary> Gets a pointer to a non-existent element just beyond the end of the array. </summary>
                /// <remarks> Like nearly all end-iterators, this value must never be dereferenced. </remarks>
                constexpr const T* end()                                            const { return begin() + Count(); }

                /// <summary> Creates a new array containing only the values found at the inputted indices. </summary>
                /// <returns> An array containing copies of the values found at the provided indices. </returns>
                /// <param name="indices"> An array containing the linear indices of the elements to be copied. </param>
                /// <remarks> 
                ///     The dimensions of the array returned by this method are the same as those of the provided 
                ///     <paramref name="indices"/> array.
                /// </remarks>
                template<uint ... V>
                constexpr auto operator [](const Array<uint, V...>& indices)        const
                {
                    return Array<T, V...>(*this, indices.Flatten());
                }

                /// <summary> Gets the value stored at a particular linear index within the array. </summary>
                /// <returns> A reference to the value found at the given index. </returns>
                /// <param name="index"> The linear array index at which the desired element is stored. </param>
                constexpr T& operator ()(uint index)                                { return _values[index]; }
                /// <summary> Gets the value stored at a particular linear index within the array. </summary>
                /// <returns> A reference to the value found at the given index. </returns>
                /// <param name="index"> The linear array index at which the desired element is stored. </param>
                constexpr const T& operator ()(uint index)                          const { return _values[index]; }
                /// <summary> Gets the value stored at a particular multidimensional index within the array. </summary>
                /// <returns> A reference to the value found at the given indices. </returns>
                /// <param name="indices"> A list of array subscripts at which the desired element is stored. </param>
                template<typename ... V>
                constexpr T& operator ()(V ... indices)                             { return _values[IndexOf(indices...)]; }
                /// <summary> Gets the value stored at a particular multidimensional index within the array. </summary>
                /// <returns> A reference to the value found at the given indices. </returns>
                /// <param name="indices"> A list of array subscripts at which the desired element is stored. </param>
                template<typename ... V>
                constexpr const T& operator ()(V ... indices)                       const { return _values[IndexOf(indices...)]; }

                /// <summary> Determines if two identically dimensioned arrays are equivalent. </summary>
                constexpr bool operator ==(const Array& other)                      const
                {
                    for (uint a = 0; a < _count; a++)
                        if (_values[a] != other(a)) return false;
                    return true;
                }
                template<typename V, uint ... W>
                constexpr bool operator ==(const Array<V, W...>& other)             const { return false; }
                /// <summary> Determines if two identically dimensioned arrays are not equivalent. </summary>
                template<typename V, uint ... W>
                constexpr bool operator !=(const Array<V, W...>& other)             const { return !operator ==(other); }
        };

    }
}



/** SPECIALIZATIONS **/
#include "Specializations/DynamicArray.h"
#include "Specializations/DynamicVector.h"
//#include "Specializations/NumericArray.h"
#include "Specializations/Matrix.h"
