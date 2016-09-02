/* CHANGELOG
 * Written by Josh Grooms on 20160706
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T>
        struct Array
        {
	        public:
		        /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in this array. </summary>
		        uint Count()		const { return _count; }
                /// <summary> Gets whether the array has any elements stored. </summary>
                bool IsEmpty()      const { return Count() == 0; }



		        /** CONSTRUCTORS & DESTRUCTOR **/
		        /// <summary> Constructs a new one-dimensional array object with a designated number of elements. </summary>
                /// <param name="n"> The desired number of elements to be stored within the new array. </param>
                Array(uint n = 0) :
			        _count(n),
			        Data(new T[n])
		        {

                }
                /// <summary> Constructs an array by transferring the contents of another array object. </summary>
                Array(Array<T>&& other) :
                    _count(other.Count()),
                    Data(other.Data)
                {
                    other.Data = nullptr;
                }
                /// <summary> Constructs an array by copying the contents of another array object. </summary>
		        Array(const Array<T>& other) :
			        _count(other.Count()),
			        Data(new T[other.Count()])
		        {
                    for (uint a = 0; a < Count(); a++)
                        Data[a] = other.Data[a];
		        }
                /// <summary> Constructs an array by copying values contained in an initializer list. </summary>
		        Array(std::initializer_list<T> values) :
			        _count(values.size()),
			        Data(new T[values.size()])
		        {
			        int idx = 0;
			        for (const T& v : values)
				        Data[idx++] = v;
		        }
                /// <summary> Destroys the underlying native storage for this array. </summary>
		        ~Array()
		        {
			        if (Data)
				        delete[] Data;
		        }



                /** UTILITIES **/
                /// <summary> Sets each element of the array to a single uniform value. </summary>
                /// <returns> A reference to the modified array for chaining together operations. </returns>
                /// <param name="value"> The value to which each element of the array should be set. </param>
                Array& Fill(const T& value)
                {
                    for (int a = 0; a < Count(); a++)
                        Data[a] = value;
                    return *this;
                }
                /// <summary> Gets a pointer to the underlying native storage for the array. </summary>
                const T* ToArray() const { return Data; }



		        /** OPERATORS **/
		        T& operator ()(uint idx)			  { return Data[idx]; }

		        const T& operator ()(uint idx)	const { return Data[idx]; }

		        Array<T>& operator =(const Array<T>& other)
		        {
			        if (Data)
				        delete[] Data;

                    _count = other.Count();
			        Data = new T[Count()];
			        for (uint a = 0; a < Count(); a++)
				        Data[a] = other.Data[a];

			        return *this;
		        }

                Array<T>& operator =(std::initializer_list<T> values)
                {
                    if (values.size() != Count())
                    {
                        if (Data)
                            delete[] Data;
                        _count = values.size();
                        Data = new T[Count()];
                    }

                    int idx = 0;
                    for (const T& v : values)
                        Data[idx++] = v;

                    return *this;
                }

		        Array<T>& operator =(Array<T>&& other)
		        {
			        std::swap(_count, other._count);
			        std::swap(Data, other.Data);
			        return *this;
		        }


                bool operator ==(const Array<T>& other) const
                {
                    if (this == (const Array<T>*)&other)
                        return true;
                    else if (other.Count() != Count())
                        return false;

                    for (int a = 0; a < Count(); a++)
                        if (Data[a] != other(a))
                            return false;

                    return true;
                }
                bool operator !=(const Array<T>& other) const
                {
                    return !(operator==(other));
                }

	        private:

		        uint	_count;
		        T*		Data;

        };
    }
}
