/* CHANGELOG 
 * Written by Josh Grooms on 20160913
 */

#pragma once
#include "Interfaces/IArray.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, uint U = 0>
        struct Vector : public IArray<T>
        {
            public:
                template<typename T, uint U> struct Iterator;



                /** PROPERTIES **/
                virtual uint Count()                    const override { return U; }
                virtual uint Rank()                     const override { return 1; }



                /** CONSTRUCTORS **/
                Vector(const T& value)
                {
                    for (uint a = 0; a < Count(); a++)
                        Data[a] = value;
                }
                Vector(std::initializer_list<T> values)
                {
                    int idx = 0;
                    for (const T& v : values)
                        Data[idx++] = v;
                }



                /** OPERATORS **/
                virtual Iterator<T, U> begin()                    { return Iterator<T, U>(0, this); }
                virtual Iterator<T, U> end()                      { return Iterator<T, U>(Count(), this); }
                virtual T& operator ()(uint idx)                  { return Data[idx]; }
                virtual const T& operator ()(uint idx)      const { return Data[idx]; }

            private:
                T Data[U];


                template<typename T, uint U>
                struct Iterator : public ICollectionIterator<T>
                {
                    public:

                        /** PROPERTIES **/
                        uint Index() const override { return _index; }

                        /** CONSTRUCTOR **/
                        Iterator(uint idx, Vector<T, U>* collection) :
                            _index(idx),
                            Collection(collection)
                        {

                        }

                        /** OPERATORS **/
                        bool operator ==(const ICollectionIterator<T>& other)   const override
                        {
                            if (auto node = dynamic_cast<const Iterator<T, U>*>(&other))
                                return (Index() == node->Index()) && (Collection == node->Collection);
                            else
                                return false;
                        }
                        const T& operator *()                                   const override { return (*Collection)(Index()); }
                        Iterator& operator ++()                                 override { _index++; return *this; }

                    private:
                        uint            _index;
                        Vector<T, U>*   Collection;
                };
        };



        template<typename T> 
        struct Vector<T, 0> : public IArray<T>
        {
            public:
                template<typename T> struct Iterator;


                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in this array. </summary>
                virtual uint Count()        const override { return _count; }
                virtual T& First()          const { return Data[0]; }
                virtual T& Last()           const { return Data[Count() - 1]; }
                virtual uint Rank()         const override { return 1; }



                 /** CONSTRUCTORS & DESTRUCTOR **/
		        /// <summary> Constructs a new one-dimensional array object with a designated number of elements. </summary>
                /// <param name="n"> The desired number of elements to be stored within the new array. </param>
                Vector(uint n = 0) :
			        _count(n),
			        Data(new T[n])
		        {

                }
                /// <summary> Constructs an array by transferring the contents of another array object. </summary>
                Vector(Vector<T>&& other) :
                    _count(other.Count()),
                    Data(other.Data)
                {
                    other.Data = nullptr;
                }
                /// <summary> Constructs an array by copying the contents of another array object. </summary>
		        Vector(const Vector<T>& other) :
			        _count(other.Count()),
			        Data(new T[other.Count()])
		        {
                    for (uint a = 0; a < Count(); a++)
                        Data[a] = other.Data[a];
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
			        if (Data)
				        delete[] Data;
		        }



                /** UTILITIES **/
                Vector& Append(const T& value)
                {
                    uint newCount = Count() + 1;
                    T* newData = new T[newCount];

                    for (uint a = 0; a < Count(); a++)
                        newData[a] = Data[a];

                    newData[Count()] = value;

                    Clear();
                    _count = newCount;
                    Data = newData;
                    return *this;
                }
                Vector& Append(const IArray<T>& values)
                {
                    if (values.IsEmpty()) { return *this; }

                    uint newCount = Count() + values.Count();
                    T* newData = new T[newCount];

                    for (uint a = 0; a < Count(); a++)
                        newData[a] = Data[a];

                    for (uint a = Count(); a < newCount; a++)
                        newData[a] = values(a - Count());

                    Clear();
                    _count = newCount;
                    Data = newData;
                    return *this;
                }
                Vector& Clear()
                {
                    if (Data)
                        delete[] Data;

                    _count = 0;
                    Data = nullptr;
                    return *this;
                }
                /// <summary> Sets each element of the array to a single uniform value. </summary>
                /// <returns> A reference to the modified array for chaining together operations. </returns>
                /// <param name="value"> The value to which each element of the array should be set. </param>
                Vector& Fill(const T& value)
                {
                    for (int a = 0; a < Count(); a++)
                        Data[a] = value;
                    return *this;
                }
                /// <summary> Gets a pointer to the underlying native storage for the array. </summary>
                const T* ToArray() const { return Data; }



		        /** OPERATORS **/
                Iterator<T> begin()                             { return Iterator<T>(0, this); }
                Iterator<T> end()                               { return Iterator<T>(Count(), this); }
		        T& operator ()(uint idx)			            { return Data[idx]; }

		        const T& operator ()(uint idx)	                const override { return Data[idx]; }

		        Vector& operator =(const Vector<T>& other)
		        {
			        if (Data)
				        delete[] Data;

                    _count = other.Count();
			        Data = new T[Count()];
			        for (uint a = 0; a < Count(); a++)
				        Data[a] = other.Data[a];

			        return *this;
		        }

                Vector& operator =(std::initializer_list<T> values)
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

		        Vector& operator =(Vector<T>&& other)
		        {
			        std::swap(_count, other._count);
			        std::swap(Data, other.Data);
			        return *this;
		        }


                bool operator ==(const Vector<T>& other) const
                {
                    if (this == (const Vector<T>*)&other)
                        return true;
                    else if (other.Count() != Count())
                        return false;

                    for (int a = 0; a < Count(); a++)
                        if (Data[a] != other(a))
                            return false;

                    return true;
                }
                bool operator !=(const Vector<T>& other) const
                {
                    return !(operator==(other));
                }

            private:

                uint _count;
                T* Data;




                template<typename T>
                struct Iterator : public ICollectionIterator<T>
                {
                    public:
                        
                        /** PROPERTIES **/
                        uint Index() const override { return _index; }

                        /** CONSTRUCTOR **/
                        Iterator(uint idx, Vector<T>* collection) : 
                            _index(idx),
                            Collection(collection)
                        {

                        }

                        /** OPERATORS **/
                        bool operator ==(const ICollectionIterator<T>& other)   const override
                        {                            
                            if ( auto node = dynamic_cast<const Iterator<T>*>(&other) )
                                return (Index() == node->Index()) && (Collection == node->Collection);
                            else
                                return false;
                        }
                        const T& operator *()                                   const override { return (*Collection)(Index()); }
                        Iterator& operator ++()                                 override { _index++; return *this; }

                    private:
                        uint        _index;
                        Vector<T>*  Collection;
                };
                
        };



    }
}