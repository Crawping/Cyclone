/* CHANGELOG
 * Written by Josh Grooms on 20160913
 */

#pragma once
#include "Meta/Expressions.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents a one-dimensional heap-allocated array of contiguous data elements. </summary>
        /// <typeparam name="T"> The type name of the data elements stored within the vector. </typeparam>
        template<typename T> 
        struct Array<T, 0> : public IArray<T>
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in this array. </summary>
                virtual uint Count()        const override { return _count; }
                /// <summary> Gets a reference to the first data element in the vector. </summary>
                virtual T& First()          const { return _data[0]; }
                /// <summary> Gets a reference to the last data element in the vector. </summary>
                virtual T& Last()           const { return _data[Count() - 1]; }
                /// <summary> Gets the number of dimensions occupied by the array. </summary>
                /// <remarks> Vectors are always one-dimensional arrays. Thus, this method always returns a value of 1. </remarks>
                virtual uint Rank()         const override { return 1; }



                 /** CONSTRUCTORS & DESTRUCTOR **/
		        /// <summary> Constructs a new one-dimensional array object with a designated number of elements. </summary>
                /// <param name="n"> The desired number of elements to be stored within the new array. </param>
                Array(uint n = 0):
			        _count(0),
			        _data(nullptr)
		        {
                    Reallocate(n);
                }
                /// <summary> Constructs an array by transferring the contents of another array object. </summary>
                Array(Array&& other):
                    _count(other.Count()),
                    _data(other._data)
                {
                    other._count = 0;
                    other._data = nullptr;
                }
                /// <summary> Constructs an array by copying the contents of another array object. </summary>
                Array(const Array& other):
			        _count(other.Count()),
			        _data(new T[other.Count()])
		        {
                    for (uint a = 0; a < Count(); a++)
                        _data[a] = other(a);
		        }
                /// <summary> Constructs a new vector by copying a subset of another collection. </summary>
                /// <param name="other"> The collection of data from which values will be copied. </param>
                /// <param name="index"> The index of the first element to be copied. </param>
                /// <param name="count"> The number of data elements to copy. </param>
                Array(const ICollection<T>& other, uint index, uint count):
                    _count(count),
                    _data(new T[count])
                {
                    for (uint a = index; a < index + count; a++)
                        _data[a - index] = other(a);
                }
                /// <summary> Constructs an array by copying values contained in an initializer list. </summary>
                Array(const InitialList<T>& values):
			        _count(values.size()),
			        _data(new T[values.size()])
		        {
			        int idx = 0;
			        for (const T& v : values)
				        _data[idx++] = v;
		        }

                template<uint ... N>
                explicit Array(const Array<T, N...>& other):
                    _count(other.Count()),
                    _data(new T[other.Count()])
                {
                    for (uint a = 0; a < _count; a++)
                        _data[a] = other(a);
                }
                /// <summary> Destroys the underlying native storage for this array. </summary>
		        ~Array()
		        {
			        if (_data) { delete[] _data; }
		        }



                /** UTILITIES **/
                /// <summary> Removes all data elements from the vector and leaves it in an empty state. </summary>
                virtual Array& Clear()
                {
                    if (_data) { delete[] _data; }
                    _count = 0;
                    _data = nullptr;
                    return *this;
                }
                /// <summary> Adds a new data element to the end of the vector. </summary>
                /// <param name="value"> A single data element to be copied and appended to the vector. </param>
                //virtual Array& Concatenate(const T& value)
                //{
                //    Reallocate(Count() + 1);
                //    _data[Count() - 1] = value;
                //    return *this;
                //}
                template<typename ... U, Meta::DisableRelatives<ICollection<T>, U...> = 0> 
                Array& Concatenate(U&& ... values)
                {
                    constexpr uint N = sizeof...(U);
                    Reallocate(Count() + N);

                    uint idx = Count();
                    Meta::Expand( Set(--idx, std::forward<U>(values))... );
                    return *this;
                }
                /// <summary> Adds the contents of another collection to the end of the vector. </summary>
                /// <param name="values"> A collection of data elements to be copied and appended to the vector. </param>
                virtual Array& Concatenate(const ICollection<T>& values)
                {
                    if (values.IsEmpty()) { return *this; }

                    uint idx = Count();
                    Reallocate(idx + values.Count());
                    for (uint a = 0; a < values.Count(); a++)
                        _data[idx++] = values(a);
                    return *this;
                }
                /// <summary> Sets each element of the array to a single uniform value. </summary>
                /// <param name="value"> The value to which each element of the array should be set. </param>
                virtual Array& Fill(const T& value)
                {
                    for (uint a = 0; a < Count(); a++)
                        _data[a] = value;
                    return *this;
                }

                template<typename U> Array& Set(uint index, U&& value)
                {
                    _data[index] = std::forward<U>(value);
                    return *this;
                }
                /// <summary> Exchanges the values of two separate vector elements. </summary>
                /// <param name="idxA"> The position of the first element to be swapped. </param>
                /// <param name="idxB"> The position of the second element to be swapped. </param>
                virtual Array& Swap(uint idxA, uint idxB)
                {
                    if (idxA >= Count() || idxB >= Count()) { return *this; }
                    std::swap(_data[idxA], _data[idxB]);
                    return *this;
                }
                /// <summary> Gets a pointer to the underlying native storage for the array. </summary>
                /// <remarks> 
                ///     This method is provided for interoperability with low level API functions that read from 
                ///     or write to native arrays, such as those found throughout OpenGL. It should not be used 
                ///     in any newly designed systems for read/write operations.
                /// </remarks>
                virtual T* ToArray()                                    { return _data; }
                /// <summary> Gets a pointer to the underlying native storage for the array. </summary>
                /// <remarks> 
                ///     This method is provided for interoperability with low level API functions that read from 
                ///     or write to native arrays, such as those found throughout OpenGL. It should not be used 
                ///     in any newly designed systems for read/write operations.
                /// </remarks>
                virtual const T* ToArray()                              const { return _data; }



		        /** OPERATORS **/
                /// <summary> Gets an iterator that references the first element stored in the vector. </summary>
                virtual Iterator begin()                                { return Iterator(0, this); }
                /// <summary> Gets an iterator that represents the end of the vector. </summary>
                /// <remarks>
                ///     This iterator references a non-existent element that lies after the last data element 
                ///     stored in the vector. It is used in ranged for-loops and in similar situations to check 
                ///     whether the end of the vector has been reached, but should never be dereferenced because 
                ///     it points to an undefined array slot.
                /// </remarks>
                virtual Iterator end()                                  { return Iterator(Count(), this); }
                /// <summary> Performs linear array-like indexing of the data elements stored within the vector. </summary>
                /// <returns> A reference to the data element stored at the inputted index. </returns>
                /// <param name="idx"> The numeric position of the desired data element within the vector. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
		        virtual T& operator ()(uint idx)			            { return _data[idx]; }
                /// <summary> Performs linear array-like indexing of the data elements stored within the vector. </summary>
                /// <returns> An immutable reference to the data element stored at the inputted index. </returns>
                /// <param name="idx"> The numeric position of the desired data element within the vector. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
		        virtual const T& operator ()(uint idx)	                const override { return _data[idx]; }

                /// <summary> Clears the vector of any stored data and transfers the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the tranferred contents of the old one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Array& operator =(Array&& other)
		        {
                    std::swap(_count, other._count);
                    std::swap(_data, other._data);
			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the other one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Array& operator =(const Array& other)
		        {
                    Reallocate(other.Count());
			        for (uint a = 0; a < Count(); a++)
				        _data[a] = other._data[a];
			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of an initializer list into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the initialization list. </returns>
                /// <param name="values"> An initialization list of data elements. </param>
                virtual Array& operator =(const InitialList<T>& values)
                {
                    Reallocate(values.size());
                    uint idx = 0;
                    for (const T& v : values)
                        _data[idx++] = v;
                    return *this;
                }

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
                    _count = n;
                    _data = newData;
                }

            private:

                uint    _count;
                T*      _data;
                

        };

        template<typename T, uint N = 0> using Vector = Array<T, N>;

        template<uint N> constexpr Array<uint, N> Accumulate(const Array<uint, N>& values)
        {
            Array<uint, N> output(values);
            for (uint a = 1; a < N; a++)
                output(a) = (output(a - 1) + output(a));
            return output;
        }
        template<typename ... T> constexpr auto Accumulate(T ... values)
        {
            return Accumulate(Array<uint, sizeof...(T)>({ values... }));
        }

    }
}
