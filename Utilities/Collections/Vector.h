/* CHANGELOG 
 * Written by Josh Grooms on 20160913
 */

#pragma once
#include "Utilities.h"
#include "Math/Math.h"
#include "Interfaces/IArray.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents a one-dimensional stack-allocated array of contiguous data elements. </summary>
        /// <typeparam name="T"> The type name of the data elements stored within the vector. </typeparam>
        /// <typeparam name="U"> The number of data elements that can be stored within the vector. </typeparam>
        template<typename T, uint U = 0>
        struct Vector: public IArray<T>
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
                Vector(const ICollection<T>& other, uint offset, uint count)
                {
                    count = Math::Min(other.Count() - offset, count, U);
                    for (uint a = 0; a < count; a++)
                        Data[a] = other(a + offset);
                }
                /// <summary> Constructs a new vector of data using the contents of an initializer list. </summary>
                /// <param name="values"> An initialization list containing values to be copied into the new vector. </param>
                Vector(std::initializer_list<T> values)
                {
                    int idx = 0;
                    for (const T& v : values)
                        Data[idx++] = v;
                }



                /** UTILITIES **/
                virtual void Fill(const T& value)
                {
                    for (uint a = 0; a < U; a++) { Data[a] = value; }
                }
                virtual void Set(uint index, const ICollection<T>& values, uint offset = 0, uint count = 1)
                {
                    index = Math::Clamp(index, 0U, U - 1); 
                    offset = Math::Clamp(offset, 0U, values.Count() - 1);
                    count = Math::Min(U - index + 1, count, values.Count() - offset);
                    for (uint a = 0; a < count; a++)
                        Data[index + a] = values(offset + a);
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
    }
}



/** SPECIALIZATIONS **/
#include "Specializations/DynamicVector.h"