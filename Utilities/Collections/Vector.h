/* CHANGELOG 
 * Written by Josh Grooms on 20160913
 */

#pragma once
#include "Interfaces/IArray.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents a one-dimensional array of contiguous data. </summary>
        template<typename T, uint U = 0>
        struct Vector : public IArray<T>
        {
            public:
                template<typename T, uint U> struct Iterator;

                /** PROPERTIES **/
                /// <summary> Gets the number of data elements present in the vector. </summary>
                virtual uint Count()                    const override { return U; }
                /// <summary> Gets the number of array dimensions present in the vector. </summary>
                virtual uint Rank()                     const override { return 1; }



                /** CONSTRUCTORS **/
                /// <summary> Constructs a new stack-allocated vector of data filled with a single uniform value. </summary>
                /// <param name="value"> The value used to initialize all data elements of the array. </param>
                Vector(const T& value = T())
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
                        T& operator *()                                         const override { return (*Collection)(Index()); }
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
                /// <summary> Gets a reference to the first data element in the vector. </summary>
                virtual T& First()          const { return Data[0]; }
                /// <summary> Gets a reference to the last data element in the vector. </summary>
                virtual T& Last()           const { return Data[Count() - 1]; }
                /// <summary> Gets the number of dimensions occupied by the array. </summary>
                /// <remarks> 
                ///     Vectors are always one-dimensional arrays. Thus, this method always returns a value 
                ///     of 1.
                /// </remarks>
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
                virtual Vector& Append(const T& value)
                {
                    Reallocate(Count() + 1);
                    Data[Count() - 1] = value;
                    return *this;
                }
                virtual Vector& Append(const ICollection<T>& values)
                {
                    if (values.IsEmpty()) { return *this; }

                    uint idx = Count();
                    Reallocate(idx + values.Count());
                    for (uint a = 0; a < values.Count(); a++)
                        Data[idx++] = values(a);

                    return *this;
                }
                /// <summary> Removes all data elements from the vector and leaves it in an empty state. </summary>
                virtual void Clear()
                {
                    if (Data) { delete[] Data; }
                    _count = 0;
                    Data = nullptr;
                }
                /// <summary> Sets each element of the array to a single uniform value. </summary>
                /// <returns> A reference to the modified array for chaining together operations. </returns>
                /// <param name="value"> The value to which each element of the array should be set. </param>
                virtual Vector& Fill(const T& value)
                {
                    for (int a = 0; a < Count(); a++)
                        Data[a] = value;
                    return *this;
                }
                /// <summary> Gets a pointer to the underlying native storage for the array. </summary>
                virtual const T* ToArray() const { return Data; }



		        /** OPERATORS **/
                virtual Iterator<T> begin()                             { return Iterator<T>(0, this); }
                virtual Iterator<T> end()                               { return Iterator<T>(Count(), this); }
		        virtual T& operator ()(uint idx)			            { return Data[idx]; }

		        virtual const T& operator ()(uint idx)	                const override { return Data[idx]; }

		        virtual Vector& operator =(const Vector<T>& other)
		        {
                    Reallocate(other.Count());
			        for (uint a = 0; a < Count(); a++)
				        Data[a] = other.Data[a];
			        return *this;
		        }
                virtual Vector& operator =(std::initializer_list<T> values)
                {
                    Reallocate(values.size());
                    int idx = 0;
                    for (const T& v : values)
                        Data[idx++] = v;
                    return *this;
                }
		        virtual Vector& operator =(Vector<T>&& other)
		        {
                    Clear();

                    _count = other._count;
                    other._count = 0;
                    Data = other.Data;
                    other.Data = nullptr;
			        return *this;
		        }

                virtual bool operator ==(const Vector<T>& other) const
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
                virtual bool operator !=(const Vector<T>& other) const
                {
                    return !(operator==(other));
                }

            protected:

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
                        T& operator *()                                         const override { return (*Collection)(Index()); }
                        Iterator& operator ++()                                 override { _index++; return *this; }

                    private:
                        uint        _index;
                        Vector<T>*  Collection;
                };
                
        };



    }
}