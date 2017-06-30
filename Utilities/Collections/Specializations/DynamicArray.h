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

        template<typename T>
        class Array<T>: public IArray<T>
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in the array. </summary>
                virtual uint Count()        const override { return _count; }
                /// <summary> Gets a reference to the first data element in the array. </summary>
                virtual T& First()          { return _values[0]; }
                /// <summary> Gets a reference to the last data element in the array. </summary>
                virtual T& Last()           { return _values[Count() - 1]; }
                /// <summary> Gets the number of dimensions occupied by the array. </summary>
                /// <remarks> Vectors are always one-dimensional arrays. Thus, this method always returns a value of 1. </remarks>
                virtual uint Rank()         const override { return _rank; }



                 /** CONSTRUCTORS & DESTRUCTOR **/
                Array():
                    _count(0),
                    _rank(0),
                    _size(nullptr),
                    _values(nullptr)
                {

                }
                template<typename ... U> Array(U ... dimensions):
                    _count(Math::Product(dimensions...)),
                    _rank(sizeof...(U)),
                    _size(nullptr),
                    _values(nullptr)
                {
                    _size   = (new Array<uint, sizeof...(U)>{ uint(dimensions)... })->begin();
                    _values = new T[_count];
                }
                /// <summary> Constructs an array by transferring the contents of another array object. </summary>
                Array(Array&& other)     noexcept:
                    _count(other._count),
                    _rank(other._rank),
                    _size(other._size),
                    _values(other._values)
                {
                    other._count    = 0;
                    other._rank     = 0;
                    other._size     = nullptr;
                    other._values   = nullptr;
                }
                /// <summary> Constructs an array by copying the contents of another array object. </summary>
		        Array(const Array& other):
			        _count(other._count),
                    _rank(other._rank),
                    _size(new uint[other._rank]),
			        _values(new T[other._count])
		        {
                    for (uint a = 0; a < Rank(); a++)
                        _size[a] = other._size[a];
                    for (uint a = 0; a < Count(); a++)
                        _values[a] = other(a);
		        }
                /// <summary> Constructs a new vector by copying a subset of another collection. </summary>
                /// <param name="other"> The collection of data from which values will be copied. </param>
                /// <param name="index"> The index of the first element to be copied. </param>
                /// <param name="count"> The number of data elements to copy. </param>
                Array(const ICollection<T>& other, uint index, uint count):
                    _count(count),
                    _rank(1),
                    _size(new uint[1]),
                    _values(new T[count])
                {
                    _size[0] = _count;
                    for (uint a = index; a < index + count; a++)
                        _values[a - index] = other(a);
                }
                /// <summary> Constructs an array by copying values contained in an initializer list. </summary>
		        Array(const InitialList<T>& values):
			        _count(values.size()),
                    _rank(1),
                    _size(new uint[1]),
			        _values(new T[values.size()])
		        {
                    _size[0] = _count;
                    for (uint a = 0; a < _count; a++)
                        _values[a] = *(values.begin() + a);
		        }
                /// <summary> Destroys the underlying native storage for this array. </summary>
		        ~Array()
		        {
                    if (_size)      { delete[] _size; }
			        if (_values)    { delete[] _values; }
		        }



                /** UTILITIES **/
                virtual uint Count(uint dimension)                      const
                {
                    uint count = Size(0);
                    for (uint a = 1; a <= dimension; a++)
                        count *= Size(a);
                    return count;
                }
                /// <summary> Removes all data elements from the vector and leaves it in an empty state. </summary>
                virtual void Clear()
                {
                    if (_size)      { delete[] _size; }
                    if (_values)    { delete[] _values; }

                    _count  = 0;
                    _rank   = 0;
                    _size   = nullptr;
                    _values = nullptr;
                }
                /// <summary> Sets each element of the array to a single uniform value. </summary>
                /// <param name="value"> The value to which each element of the array should be set. </param>
                virtual void Fill(const T& value)
                {
                    for (uint a = 0; a < Count(); a++)
                        _values[a] = value;
                }

                virtual uint Size(uint dimension)                       const 
                {
                    if (_rank == 0) { return 0; }
                    return (dimension >= _rank) ? 1 : _size[dimension];
                }

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
                template<typename ... U>
                uint IndexOf(U ... subscripts)                          const 
                { 
                    return IndexOf( Array<uint, sizeof...(U)>{ uint(subscripts)... } );
                }
                template<uint N>
                uint IndexOf(const Array<uint, N>& subscripts)          const
                {
                    uint rank = Math::Min(N, _rank);
                    uint idx = subscripts(0);
                    for (uint a = 1; a < rank; a++)
                        idx += subscripts(a) * Count(a - 1);
                    return idx;
                }
                /// <summary> Exchanges the values of two separate vector elements. </summary>
                /// <param name="idxFirst"> The position of the first element to be swapped. </param>
                /// <param name="idxSecond"> The position of the second element to be swapped. </param>
                virtual void Swap(uint idxFirst, uint idxSecond)
                {
                    //if (idxFirst >= Count() || idxSecond >= Count()) { return; }
                    std::swap(_values[idxFirst], _values[idxSecond]);
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
                /// <summary> Performs linear array-like indexing of the data elements stored within the array. </summary>
                /// <returns> A reference to the data element stored at the inputted index. </returns>
                /// <param name="idx"> The numeric position of the desired data element within the array. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
		        virtual T& operator ()(uint idx)			            { return _values[idx]; }
                /// <summary> Performs linear array-like indexing of the data elements stored within the vector. </summary>
                /// <returns> An immutable reference to the data element stored at the inputted index. </returns>
                /// <param name="idx"> The numeric position of the desired data element within the vector. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
		        virtual const T& operator ()(uint idx)	                const override { return _values[idx]; }

                template<typename ... U>
                T& operator ()(U ... subscripts)                        { return _values[IndexOf(subscripts...)]; }
                template<typename ... U>
                const T& operator ()(U ... subscripts)                  const { return _values[IndexOf(subscripts...)]; }

                /// <summary> Clears the vector of any stored data and transfers the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the tranferred contents of the old one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Array& operator =(Array&& other)             noexcept
		        {
                    std::swap(_count,   other._count);
                    std::swap(_rank,    other._rank);
                    std::swap(_size,    other._size);
                    std::swap(_values,  other._values);
			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the other one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Array& operator =(const Array& other)
		        {
                    Reallocate(other.Count());
                    _rank = other._rank;

                    for (uint a = 0; a < Rank(); a++)
                        _size[a] = other._size[a];
			        for (uint a = 0; a < Count(); a++)
				        _values[a] = other._values[a];

			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of an initializer list into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the initialization list. </returns>
                /// <param name="values"> An initialization list of data elements. </param>
                virtual Array& operator =(const InitialList<T>& values)
                {
                    uint count = Math::Min(Count(), values.size());
                    for (uint a = 0; a < count; a++)
                        _values[a] = *(values.begin() + a);
                    return *this;
                }


                virtual bool operator ==(const Array& other)            const
                {
                    if (this == &other)                                             { return true; }
                    else if ( Count() != other.Count() || Rank() != other.Rank() )  { return false; }

                    for (uint a = 0; a < _rank; a++)
                        if (_size[a] != other._size[a]) { return false; }

                    for (uint a = 0; a < _count; a++)
                        if (_values[a] != other(a)) { return false; }

                    return true;
                }
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
                    for (uint a = 0; a < Count(); a++)
                        newData[a] = _values[a];

                    Clear();
                    _count  = n;
                    _values = newData;
                }

            private:

                uint    _count;
                uint    _rank;
                uint*   _size;
                T*      _values;
        };
    }
}
