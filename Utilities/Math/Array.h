/* CHANGELOG
 * Written by Josh Grooms on 20160706
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone::Utilities
{
    template<typename T>
    struct Array
    {
	    public:
		    /** PROPERTIES **/
            /// <summary> Gets the total number of elements present in this array. </summary>
		    uint Count()		const { return _count; }

		

		    /** CONSTRUCTORS & DESTRUCTOR **/
		    Array(uint n) :
			    _count(n),
			    Data(new T[n])
		    {

		    }

		    Array(const Array<T>& other) :
			    _count(other.Count()),
			    Data(new T[other.Count()])
		    {
			    std::memcpy(Data, other.Data, Count() * sizeof(T));
		    }

		    Array(Array<T>&& other) :
			    _count(other.Count()),
			    Data(other.Data)
		    {
			    other.Data = nullptr;
		    }

		    Array(std::initializer_list<T> values) :
			    _count(values.size()),
			    Data(new T[values.size()])
		    {
			    int idx = 0;
			    for (const T& v : values)
				    Data[idx++] = v;
		    }

		    ~Array() 
		    { 
			    if (Data) 
				    delete[] Data;
		    }


            /** UTILITIES **/
            Array& Fill(const T& value)
            {
                for (int a = 0; a < Count(); a++)
                    Data[a] = value;
                return *this;
            }


		    /** OPERATORS **/
		    T& operator ()(uint idx)			  { return Data[idx]; }

		    const T& operator ()(uint idx)	const { return Data[idx]; }
		
		    Array<T>& operator =(Array<T>& other)
		    {
			    if (Data)
				    delete[] Data;

                _count = other.Count();
			    Data = new T[Count()];
			    for (int a = 0; a < Count(); a++)
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