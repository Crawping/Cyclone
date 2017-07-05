/* CHANGELOG
 * Written by Josh Grooms on 20170525
 */

#pragma once
#include "Interfaces/IArray.h"
#include "Math/Math.h"



namespace Cyclone
{
    namespace Utilities
    {

        /// <summary> A class that represents a multidimensional array of data elements. </summary>
        /// <typeparam name="T"> The type of the elements stored in the array. </typeparam>
        template<typename T>
        class Array<T>: public IArray<T>
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in the array. </summary>
                virtual uint Count()        const override { return _count; }
                /// <summary> Gets a reference to the first data element in the array. </summary>
                virtual T& First()          { return _data[0]; }
                /// <summary> Gets a reference to the last data element in the array. </summary>
                virtual T& Last()           { return _data[Count() - 1]; }
                /// <summary> Gets the number of dimensions occupied by the array. </summary>
                /// <remarks> Vectors are always one-dimensional arrays. Thus, this method always returns a value of 1. </remarks>
                virtual uint Rank()         const override { return _rank; }



                 /** CONSTRUCTORS & DESTRUCTOR **/
                 /// <summary> Constructs a new empty multidimensional array of values. </summary>
                Array():
                    _count(0),
                    _rank(0),
                    _size(nullptr),
                    _data(nullptr)
                {

                }
                /// <summary> Constructs a new empty multidimensional array of values. </summary>
                /// <param name="...dimensions"> Any number of integers defining the size of the array. </param>
                template<typename ... U> Array(U ... dimensions):
                    _count(Math::Product(dimensions...)),
                    _rank(sizeof...(U)),
                    _size(nullptr),
                    _data(nullptr)
                {
                    _size   = (new Array<uint, sizeof...(U)>{ uint(dimensions)... })->begin();
                    _data = new T[_count];
                }
                /// <summary> Constructs an array by transferring the contents of another array object. </summary>
                Array(Array&& other)     noexcept:
                    _count(other._count),
                    _rank(other._rank),
                    _size(other._size),
                    _data(other._data)
                {
                    other._count    = 0;
                    other._rank     = 0;
                    other._size     = nullptr;
                    other._data   = nullptr;
                }
                /// <summary> Constructs an array by copying the contents of another array object. </summary>
		        Array(const Array& other):
			        _count(other._count),
                    _rank(other._rank),
                    _size(new uint[other._rank]),
			        _data(new T[other._count])
		        {
                    for (uint a = 0; a < Rank(); a++)
                        _size[a] = other._size[a];
                    for (uint a = 0; a < Count(); a++)
                        _data[a] = other(a);
		        }
                /// <summary> Constructs a new vector by copying a subset of another collection. </summary>
                /// <param name="other"> The collection of data from which values will be copied. </param>
                /// <param name="index"> The index of the first element to be copied. </param>
                /// <param name="count"> The number of data elements to copy. </param>
                Array(const ICollection<T>& other, uint index, uint count):
                    _count(count),
                    _rank(1),
                    _size(new uint[1]),
                    _data(new T[count])
                {
                    _size[0] = _count;
                    for (uint a = index; a < index + count; a++)
                        _data[a - index] = other(a);
                }
                /// <summary> Constructs a new multidimensional array whose elements are initialized to specific values. </summary>
                /// <param name="values"> An initial list of values to copied into the new array. </param>
		        Array(const InitialList<T>& values):
			        _count(values.size()),
                    _rank(1),
                    _size(new uint[1]),
			        _data(new T[values.size()])
		        {
                    _size[0] = _count;
                    for (uint a = 0; a < _count; a++)
                        _data[a] = *(values.begin() + a);
		        }
                /// <summary> Destroys the underlying native storage for this array. </summary>
		        ~Array()
		        {
                    if (_size)      { delete[] _size; }
			        if (_data)    { delete[] _data; }
		        }



                /** UTILITIES **/
                /// <summary> Removes all data elements from the vector and leaves it in an empty state. </summary>
                virtual void Clear()
                {
                    if (_size)      { delete[] _size; }
                    if (_data)    { delete[] _data; }

                    _count  = 0;
                    _rank   = 0;
                    _size   = nullptr;
                    _data = nullptr;
                }
                /// <summary> Gets the total number of elements present in a specific dimension of the array. </summary>
                /// <returns> The cumulative element count up through the inputted array dimension. </returns>
                /// <param name="dimension"> The array dimension through which elements are to be counted. </param>
                virtual uint Count(uint dimension)                      const
                {
                    uint count = Size(0);
                    for (uint a = 1; a <= dimension; a++)
                        count *= Size(a);
                    return count;
                }
                /// <summary> Sets each element of the array to a single uniform value. </summary>
                /// <param name="value"> The value to which each element of the array should be set. </param>
                virtual void Fill(const T& value)
                {
                    for (uint a = 0; a < Count(); a++)
                        _data[a] = value;
                }
                /// <summary> Changes the dimensions of the array while preserving its element count. </summary>
                /// <param name="dimensions"> Any number of integers defining the new size of the array. </param>
                /// <remarks> 
                ///     Note that reshaping operations require element counts to be preserved, and an exception 
                ///     will be thrown if the given dimensions would not contain the same number of elements that 
                ///     are stored in the existing array.
                /// </remarks>
                template<typename ... U>
                Array& Reshape(U ... dimensions)
                {
                    constexpr uint newRank = sizeof...(U);
                    if (Math::Product(dimensions...) != Count())
                        throw std::exception("The number of elements must remain constant during a reshaping operation.");
                    else if (_size && _rank != newRank)
                    { 
                        delete[] _size;
                        _size = nullptr;
                    }

                    _rank = newRank;
                    _size = (new Array<uint, newRank> { uint(dimensions)... })->begin();

                    return *this;
                }
                /// <summary> Calculates a linear index that is equivalent to a set of array subscripts. </summary>
                /// <returns> A linear array index that references the same location as the inputted subscripts. </returns>
                /// <param name="subscripts"> Any number of unsigned integers representing the array subscripts to convert. </param>
                /// <remarks> Subscripts into dimensions higher than the rank of the array are ignored. </remarks>
                template<typename ... U>
                uint IndexOf(U ... subscripts)                          const 
                { 
                    return IndexOf( Array<uint, sizeof...(U)>{ uint(subscripts)... } );
                }
                /// <summary> Calculates a linear index that is equivalent to a set of array subscripts. </summary>
                /// <returns> A linear array index that references the same location as the inputted subscripts. </returns>
                /// <param name="subscripts"> Any number of unsigned integers representing the array subscripts to convert. </param>
                /// <remarks> Subscripts into dimensions higher than the rank of the array are ignored. </remarks>
                template<uint N>
                uint IndexOf(const Array<uint, N>& subscripts)          const
                {
                    uint rank = Math::Min(N, _rank);
                    uint idx = subscripts(0);
                    for (uint a = 1; a < rank; a++)
                        idx += subscripts(a) * Count(a - 1);
                    return idx;
                }
                /// <summary> Gets the size of the array across a specific dimension. </summary>
                /// <returns> The size of the array along the inputted dimension. </returns>
                /// <param name="dimension"> A single array dimension. </param>
                virtual uint Size(uint dimension)                       const 
                {
                    if (_rank == 0) { return 0; }
                    return (dimension >= _rank) ? 1 : _size[dimension];
                }
                /// <summary> Exchanges the values of two separate vector elements. </summary>
                /// <param name="idxFirst"> The position of the first element to be swapped. </param>
                /// <param name="idxSecond"> The position of the second element to be swapped. </param>
                virtual void Swap(uint idxFirst, uint idxSecond)
                {
                    //if (idxFirst >= Count() || idxSecond >= Count()) { return; }
                    std::swap(_data[idxFirst], _data[idxSecond]);
                }



		        /** OPERATORS **/
                /// <summary> Gets an iterator that references the first element stored in the array. </summary>
                virtual Iterator begin()                                { return Iterator(0, this); }
                /// <summary> Gets an iterator that represents the end of the array. </summary>
                /// <remarks>
                ///     This iterator references a non-existent element that lies after the last data element 
                ///     stored in the array. It is used in ranged for-loops and in similar situations to check 
                ///     whether the end of the array has been reached, but should never be dereferenced because 
                ///     it points to an undefined array slot.
                /// </remarks>
                virtual Iterator end()                                  { return Iterator(Count(), this); }
                /// <summary> Gets the value stored at a particular linear index within the array. </summary>
                /// <returns> A reference to the value found at the given index. </returns>
                /// <param name="index"> The linear array index at which the desired element is stored. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
		        virtual T& operator ()(uint idx)			            { return _data[idx]; }
                /// <summary> Gets the value stored at a particular linear index within the array. </summary>
                /// <returns> A reference to the value found at the given index. </returns>
                /// <param name="index"> The linear array index at which the desired element is stored. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
		        virtual const T& operator ()(uint idx)	                const override { return _data[idx]; }
                /// <summary> Gets the value stored at a particular multidimensional index within the array. </summary>
                /// <returns> A reference to the value found at the given indices. </returns>
                /// <param name="indices"> A list of array subscripts at which the desired element is stored. </param>
                template<typename ... U>
                T& operator ()(U ... subscripts)                        { return _data[IndexOf(subscripts...)]; }
                /// <summary> Gets the value stored at a particular multidimensional index within the array. </summary>
                /// <returns> A reference to the value found at the given indices. </returns>
                /// <param name="indices"> A list of array subscripts at which the desired element is stored. </param>
                template<typename ... U>
                const T& operator ()(U ... subscripts)                  const { return _data[IndexOf(subscripts...)]; }

                /// <summary> Clears the vector of any stored data and transfers the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the tranferred contents of the old one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Array& operator =(Array&& other)             noexcept
		        {
                    std::swap(_count,   other._count);
                    std::swap(_rank,    other._rank);
                    std::swap(_size,    other._size);
                    std::swap(_data,  other._data);
			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the other one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Array& operator =(const Array& other)
		        {
                    Reallocate(other.Count());
                    _rank = other.Rank();

                    for (uint a = 0; a < _rank; a++)
                        _size[a] = other.Size(a);

                    for (uint a = 0; a < _count; a++)
                        _data[a] = other(a);

			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of an initializer list into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the initialization list. </returns>
                /// <param name="values"> An initialization list of data elements. </param>
                virtual Array& operator =(const InitialList<T>& values)
                {
                    Reallocate(values.size());
                    
                    uint count = Math::Min(Count(), values.size());
                    for (uint a = 0; a < count; a++)
                        _data[a] = *(values.begin() + a);
                    return *this;
                }

                /// <summary> Determines if two arrays are equivalent. </summary>
                virtual bool operator ==(const Array& other)            const
                {
                    if (this == &other)                                             { return true; }
                    else if ( Count() != other.Count() || Rank() != other.Rank() )  { return false; }

                    for (uint a = 0; a < _rank; a++)
                        if (_size[a] != other._size[a]) { return false; }

                    for (uint a = 0; a < _count; a++)
                        if (_data[a] != other(a)) { return false; }

                    return true;
                }
                /// <summary> Determines if two arrays are not equivalent. </summary>
                virtual bool operator !=(const Array& other)            const { return !operator ==(other); }

            protected:

                /// <summary> Destroys and recreates the underlying storage array for the vector. </summary>
                /// <param name="n"> The desired number of elements that can be stored in the new array. </param>
                /// <remarks> 
                ///     This method is used to resize the native array that holds the vector's data elements. Existing vector 
                ///     elements are copied into the new array before the old one is destroyed. 
                /// </remarks>
                virtual void Reallocate(uint n)
                {
                    if (n == Count())   { return; }
                    if (n == 0)         { Clear(); return; }

                    T* newData = new T[n];
                    for (uint a = 0; a < _count; a++)
                        newData[a] = _data[a];

                    Clear();
                    _count  = n;
                    _data = newData;
                }


            private:

                uint    _count;
                T*      _data;
                uint    _rank;
                uint*   _size;
        };
    }
}
