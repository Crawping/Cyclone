/* CHANGELOG 
 * Written by Josh Grooms on 20160913
 */

#pragma once
#include "Interfaces/IArray.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents a one-dimensional stack-allocated array of contiguous data elements. </summary>
        /// <typeparam name="T"> The type name of the data elements stored within the vector. </typeparam>
        /// <typeparam name="U"> The number of data elements that can be stored within the vector. </typeparam>
        template<typename T, uint U = 0>
        struct Vector : public IArray<T>
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of data elements present in the vector. </summary>
                virtual uint Count()                    const override { return U; }
                /// <summary> Gets the number of array dimensions present in the vector. </summary>
                virtual uint Rank()                     const override { return 1; }



                /** CONSTRUCTORS **/
                /// <summary> Constructs a new vector of data filled with a single uniform value. </summary>
                /// <param name="value"> The value used to initialize all data elements of the array. </param>
                Vector(const T& value = T())
                {
                    for (uint a = 0; a < Count(); a++)
                        Data[a] = value;
                }
                /// <summary> Constructs a new vector of data using the contents of an initializer list. </summary>
                /// <param name="values"> An initialization list containing values to be copied into the new vector. </param>
                Vector(std::initializer_list<T> values)
                {
                    int idx = 0;
                    for (const T& v : values)
                        Data[idx++] = v;
                }



                /** OPERATORS **/
                /// <summary> Gets an iterator that references the first element stored in the vector. </summary>
                virtual Iterator begin()                    { return Iterator(0, this); }
                /// <summary> Gets an iterator that represents the end of the vector. </summary>
                /// <remarks>
                ///     This iterator references a non-existent element that lies after the last data element 
                ///     stored in the vector. It is used in ranged for-loops and in similar situations to check 
                ///     whether the end of the vector has been reached, but should never be dereferenced because 
                ///     it points to an undefined array slot.
                /// </remarks>
                virtual Iterator end()                      { return Iterator(Count(), this); }
                /// <summary> Performs linear array-like indexing of the data elements stored within the vector. </summary>
                /// <returns> A reference to the data element stored at the inputted index. </returns>
                /// <param name="idx"> The numeric position of the desired data element within the vector. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
                virtual T& operator ()(uint idx)            { return Data[idx]; }
                /// <summary> Performs linear array-like indexing of the data elements stored within the vector. </summary>
                /// <returns> An immutable reference to the data element stored at the inputted index. </returns>
                /// <param name="idx"> The numeric position of the desired data element within the vector. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
                virtual const T& operator ()(uint idx)      const { return Data[idx]; }

                /// <summary> Determines whether two vectors of data are equivalent. </summary>
                /// <returns> A Boolean <c>true</c> if the two vectors are equivalent, or <c>false</c> otherwise. </returns>
                /// <param name="other"> Another vector of data to be tested for equivalency. </param>
                virtual bool operator ==(const Vector<T, U>& other) const
                {
                    for (uint a = 0; a < U; a++)
                        if (Data[a] != other.Data[a])
                            return false;
                    return true;
                }

            private:

                T Data[U];

        };


        /// <summary> A class that represents a one-dimensional heap-allocated array of contiguous data elements. </summary>
        /// <typeparam name="T"> The type name of the data elements stored within the vector. </typeparam>
        template<typename T> 
        struct Vector<T, 0> : public IArray<T>
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in this array. </summary>
                virtual uint Count()        const override { return _count; }
                /// <summary> Gets a reference to the first data element in the vector. </summary>
                virtual T& First()          const { return Data[0]; }
                /// <summary> Gets a reference to the last data element in the vector. </summary>
                virtual T& Last()           const { return Data[Count() - 1]; }
                /// <summary> Gets the number of dimensions occupied by the array. </summary>
                /// <remarks> Vectors are always one-dimensional arrays. Thus, this method always returns a value of 1. </remarks>
                virtual uint Rank()         const override { return 1; }



                 /** CONSTRUCTORS & DESTRUCTOR **/
		        /// <summary> Constructs a new one-dimensional array object with a designated number of elements. </summary>
                /// <param name="n"> The desired number of elements to be stored within the new array. </param>
                Vector(uint n = 0) :
			        _count(0),
			        Data(nullptr)
		        {
                    Reallocate(n);
                }
                /// <summary> Constructs an array by transferring the contents of another array object. </summary>
                Vector(Vector<T>&& other) :
                    _count(other.Count()),
                    Data(other.Data)
                {
                    other._count = 0;
                    other.Data = nullptr;
                }
                /// <summary> Constructs an array by copying the contents of another array object. </summary>
		        Vector(const Vector<T>& other) :
			        _count(other.Count()),
			        Data(new T[other.Count()])
		        {
                    for (uint a = 0; a < Count(); a++)
                        Data[a] = other(a);
		        }
                /// <summary> Constructs a new vector by copying a subset of another collection. </summary>
                /// <param name="other"> The collection of data from which values will be copied. </param>
                /// <param name="index"> The index of the first element to be copied. </param>
                /// <param name="count"> The number of data elements to copy. </param>
                Vector(const ICollection<T>& other, uint index, uint count) :
                    _count(count),
                    Data(new T[count])
                {
                    for (uint a = index; a < index + count; a++)
                        Data[a - index] = other(a);
                }
                /// <summary> Constructs an array by copying values contained in an initializer list. </summary>
		        Vector(std::initializer_list<T> values) :
			        _count(values.size()),
			        Data(new T[values.size()])
		        {
			        int idx = 0;
			        for (const T& v : values)
				        Data[idx++] = v;
		        }
                /// <summary> Destroys the underlying native storage for this array. </summary>
		        ~Vector()
		        {
			        if (Data) { delete[] Data; }
		        }



                /** UTILITIES **/
                /// <summary> Removes all data elements from the vector and leaves it in an empty state. </summary>
                virtual void Clear()
                {
                    if (Data) { delete[] Data; }
                    _count = 0;
                    Data = nullptr;
                }
                /// <summary> Adds a new data element to the end of the vector. </summary>
                /// <param name="value"> A single data element to be copied and appended to the vector. </param>
                virtual void Concatenate(const T& value)
                {
                    Reallocate(Count() + 1);
                    Data[Count() - 1] = value;
                }
                /// <summary> Adds the contents of another collection to the end of the vector. </summary>
                /// <param name="values"> A collection of data elements to be copied and appended to the vector. </param>
                virtual void Concatenate(const ICollection<T>& values)
                {
                    if (values.IsEmpty()) { return; }

                    uint idx = Count();
                    Reallocate(idx + values.Count());
                    for (uint a = 0; a < values.Count(); a++)
                        Data[idx++] = values(a);
                }
                /// <summary> Sets each element of the array to a single uniform value. </summary>
                /// <param name="value"> The value to which each element of the array should be set. </param>
                virtual void Fill(const T& value)
                {
                    for (uint a = 0; a < Count(); a++)
                        Data[a] = value;
                }
                /// <summary> Exchanges the values of two separate vector elements. </summary>
                /// <param name="idxFirst"> The position of the first element to be swapped. </param>
                /// <param name="idxSecond"> The position of the second element to be swapped. </param>
                virtual void Swap(uint idxFirst, uint idxSecond)
                {
                    if (idxFirst >= Count() || idxSecond >= Count()) { return; }
                    std::swap(Data[idxFirst], Data[idxSecond]);
                }
                /// <summary> Gets a pointer to the underlying native storage for the array. </summary>
                virtual const T* ToArray() const { return Data; }



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
		        virtual T& operator ()(uint idx)			            { return Data[idx]; }
                /// <summary> Performs linear array-like indexing of the data elements stored within the vector. </summary>
                /// <returns> An immutable reference to the data element stored at the inputted index. </returns>
                /// <param name="idx"> The numeric position of the desired data element within the vector. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
		        virtual const T& operator ()(uint idx)	                const override { return Data[idx]; }

                /// <summary> Clears the vector of any stored data and transfers the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the tranferred contents of the old one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Vector& operator =(Vector<T>&& other)
		        {
                    Clear();

                    _count = other._count;
                    other._count = 0;
                    Data = other.Data;
                    other.Data = nullptr;
			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of another vector into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the other one. </returns>
                /// <param name="other"> Another generic vector of data elements. </param>
		        virtual Vector& operator =(const Vector<T>& other)
		        {
                    Reallocate(other.Count());
			        for (uint a = 0; a < Count(); a++)
				        Data[a] = other.Data[a];
			        return *this;
		        }
                /// <summary> Clears the vector of any stored data and copies the contents of an initializer list into it. </summary>
                /// <returns> A reference to the new data vector containing the copied contents of the initialization list. </returns>
                /// <param name="values"> An initialization list of data elements. </param>
                virtual Vector& operator =(std::initializer_list<T> values)
                {
                    Reallocate(values.size());
                    int idx = 0;
                    for (const T& v : values)
                        Data[idx++] = v;
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
                    for (uint a = 0; a < Count(); a++)
                        newData[a] = Data[a];

                    Clear();
                    _count = n;
                    Data = newData;
                }

            private:

                uint    _count;
                T*      Data;
                
        };



    }
}