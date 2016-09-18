/* CHANGELOG
 * Written by Josh Grooms on 20160806
 */

#pragma once
#include "TypeDefinitions.h"
#include "Interfaces/IArray.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents a doubly-linked list of generic data. </summary>
        /// <typeparam name="T"> The type name of the data elements held by the list. </typeparam>
        template<typename T>
        class List : public IArray<T>
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in the list. </summary>
                virtual uint Count()        const override { return _count; }
                /// <summary> Gets a reference to the first data element in the list. </summary>
                virtual T& First()                         { return _first->Value; }
                /// <summary> Gets a reference to the last data element in the list. </summary>
                virtual T& Last()                          { return _last->Value; }
                /// <summary> Gets the number of dimensions present in the list. </summary>
                /// <remarks> Lists are always one-dimensional, and thus this property always returns a value of <c>1</c>. </remarks>
                virtual uint Rank()         const override { return 1; }


                /** CONSTRUCTORS & DESTRUCTOR **/
                /// <summary> Constructs a new empty linked list that can be populated with data elements. </summary>
                List() :
                    _count(0),
                    _first(nullptr),
                    _last(nullptr)
                {
                    
                }
                /// <summary> Constructs a new linked list containing the uncopied contents transferred from another list. </summary>
                /// <param name="other"> A pre-existing list whose contents are to be moved over to the new list. </param>
                List(List<T>&& other) :
                    _count(other._count),
                    _first(other._first),
                    _last(other._last)
                {
                    other._count = 0;
                    other._first = nullptr;
                    other._last = nullptr;
                }
                /// <summary> Constructs a new linked list that is an identical deep copy of another list. </summary>
                /// <param name="other"> A pre-existing list of data elements to be copied. </param>
                List(const List<T>& other) :
                    List((const IArray&)other)
                {

                }
                /// <summary> Constructs a new linked list that is an identical deep copy of another array-like collection of data elements. </summary>
                /// <param name="other"> A pre-existing collection of data elements to be copied. </param>
                List(const IArray<T>& other) :
                    List()
                {
                    for (uint a = 0; a < other.Count(); a++)
                        Append(other(a));
                }
                /// <summary> Constructs a new linked list that stores the values found within an initializer list. </summary>
                /// <param name="values"> An initialization list containing the values to be stored within the new list. </param>
                List(std::initializer_list<T> values) :
                    List()
                {
                    for (const T& v : values)
                        Append(v);
                }
                /// <summary> Removes all of the data elements stored within the list. </summary>
                ~List()
                {
                    Clear();
                }



                /** UTILITIES **/
                /// <summary> Adds a new data value to the end of the list. </summary>
                /// <param name="value"> The data element that will copied and added to the list. </param>
                void Append(const T& value)                                         { Insert(Count(), value); }
                /// <summary> Adds the contents of another collection to the end of the list.
                /// <param name="values"> An array-like collection containing the data elements to be copied and added to the list. </param>
                void Append(const IArray<T>& values)                                { Insert(Count(), values); }
                /// <summary> Removes all data elements stored within the list. </summary>
                /// <remarks>
                ///     This method destroys the data nodes that make up the linked list, effectively resetting the collection to an empty state 
                ///     with a zero element count, but takes no responsibility for destroying the data that these nodes contain. For example, if 
                ///     a hypothetical object has been allocated on the heap and a pointer to it is stored within the list, that object is NOT 
                ///     destroyed by this operation (or by the destructor for this class, for that matter). Such heap-allocated objects will 
                ///     remain valid for use and must be reclaimed elsewhere.
                /// </remarks>
                void Clear()
                {
                    if (!IsEmpty())
                    {
                        Node<T>* ctNode = _first;
                        while (ctNode->Next)
                        {
                            ctNode = ctNode->Next;
                            delete ctNode->Previous;
                        }
                        delete _last;
                        _count = 0;
                    }
                }
                /// <summary> Inserts a new data value into the list at the specified index. </summary>
                /// <param name="index"> The numeric index at which the new data element will be placed. </param>
                /// <param name="value"> The data element that will be copied and inserted into the list. </param>
                /// <remarks>
                ///     Inserting a new data element into the linked list is an O(n) operation. Attempting to insert a new element at 
                ///     an index greater than or equal to the list <see cref="Count"/> will result in a simple <see cref="Append"/> 
                ///     operation. For indices greater than the list size at the time of insertion, this means that the new data element 
                ///     CANNOT be accessed in the future using that same numeric index (although indices equal to the list size are fine 
                ///     for future use). After insertion, any element that previously occupied the index of the new data element will 
                ///     have been displaced one position to the right.
                /// </remarks>
                void Insert(uint index, const T& value)
                {
                    index = (index > Count()) ? Count() : index;

                    Node<T>* toShift = Index(index);
                    Node<T>* newNode = new Node<T>(value);

                    if (toShift)
                    {
                        if (toShift->Previous)
                        {
                            toShift->Previous->Next = newNode;
                            newNode->Previous = toShift->Previous;
                        }
                        else
                            _first = newNode;
                        
                        newNode->Next = toShift;
                        toShift->Previous = newNode;
                    }
                    else if (IsEmpty())
                    {
                        _first = newNode;
                        _last = newNode;
                    }
                    else
                    {
                        _last->Next = newNode;
                        newNode->Previous = _last;
                        _last = newNode;
                    }

                    _count++;
                }
                /// <summary> Inserts the contents of another collection into the list starting at the specified index. </summary>
                /// <param name="index"> The numeric index at which the first element of the other collection will be placed. </param>
                /// <param name="values"> An array-like collection containing the data elements to be copied and inserted into the list. </param>
                void Insert(uint index, const IArray<T>& values)
                {
                    for (uint a = values.Count(); a > 0; a--)
                        Insert(index, values(a - 1));
                }
                /// <summary> Adds a new data value to the beginning of the list. </summary>
                /// <param name="value"> The data element that will be copied and added to the list. </param>
                void Prepend(const T& value)                                        { Insert(0, value); }
                /// <summary> Adds the contents of another collection to the beginning of the list. </summary>
                /// <param name="values"> An array-like collection containing the data elements to be copied and added to the list. </param>
                void Prepend(const IArray<T>& values)                               { Insert(0, values); }
                /// <summary> Removes the data element found at the specified index from the list. </summary>
                /// <param name="index"> The numeric index of the data element to be removed. </param>
                void Remove(uint index)
                {
                    if (index >= Count()) { return; }

                    Node<T>* toRemove = Index(index);
                    if (toRemove->Previous)
                        toRemove->Previous->Next = toRemove->Next;
                    else
                        _first = toRemove->Next;

                    if (toRemove->Next)
                        toRemove->Next->Previous = toRemove->Previous;
                    else
                        _last = toRemove->Previous;

                    delete toRemove;
                    _count--;
                }
                


                /** OPERATORS **/
                /// <summary> Performs linear array-like indexing of the data elements stored within the list. </summary>
                /// <param name="index"> The numeric position of the desired data element within the list. </param>
                /// <returns> A reference to the data element stored at the inputted position. </returns>
                /// <remarks>
                ///     Attempting to index into the list at an invalid position (i.e. beyond the end of the list) is an error and 
                ///     will generate a runtime exception.
                /// </remarks>
                T& operator ()(uint index)                                          { return Index(index)->Value; }
                /// <summary> Performs linear array-like indexing of the data elements stored within the list. </summary>
                /// <param name="index"> The numeric position of the desired data element within the list. </param>
                /// <returns> A constant reference to the data element stored at the inputted position. </returns>
                /// <remarks>
                ///     Attempting to index into the list at an invalid position (i.e. beyond the end of the list) is an error and 
                ///     will generate a runtime exception.
                /// </remarks>
                const T& operator ()(uint index)                     const override { return Index(index)->Value; }
                
                /// <summary> Clears the list of any stored data and transfers the contents of another list into it. </summary>
                /// <param name="other"> A pre-existing list whose contents are to be moved. </param>
                /// <returns> A reference to the new list object that contains the uncopied contents of the old one. </returns>
                List& operator =(List<T>&& other)
                {
                    Clear();
                    _count = other._count;
                    _first = other._first;
                    _last = other._last;

                    other._count = 0;
                    other._first = nullptr;
                    other._last = nullptr;
                }
                /// <summary> Clears the list of any stored data and copies the contents of another list into it. </summary>
                /// <param name="values"> An array-like collection of data elements to be copied. </param>
                /// <returns> A reference to the new list object that contains the copied contents of the other one. </returns>
                List& operator =(const IArray<T>& values)
                {
                    Clear();
                    for (uint a = 0; a < values.Count(); a++)
                        Append(values(a));
                    return *this;
                }
                /// <summary> Clears the list of any stored data and copies the contents of an initialization list into it. </summary>
                /// <param name="values"> An initialization list that contains the values to be copied. </param>
                /// <returns></returns>
                List& operator =(std::initializer_list<T> values)
                {
                    Clear();
                    for (const T& v : values)
                        Append(v);
                    return *this;
                }



            private:

                template<typename T> struct Node
                {
                    Node<T>*    Next;
                    Node<T>*    Previous;
                    T           Value;

                    Node(const T& value) :
                        Next(nullptr),
                        Previous(nullptr),
                        Value(value)
                    {

                    }
                    Node(const T& value, Node<T>* previous, Node<T>* next) :
                        Next(next),
                        Previous(previous),
                        Value(value)
                    {

                    }
                };

                /// <summary> Performs linear array-like indexing of the data elements stored within the list. </summary>
                /// <param name="index"> The numeric position of the desired data element within the list. </param>
                /// <returns> A pointer to the list node that resides at the inputted position or <c>nullptr</c> if the position is invalid. </returns>
                Node<T>* Index(uint index) const
                {                    
                    if (index >= Count())
                        return nullptr;

                    Node<T>* node = _first;
                    for (uint a = 0; a < index; a++)
                        node = node->Next;

                    return node;
                }



                /** PROPERTY DATA **/
                uint        _count;
                Node<T>*    _first;
                Node<T>*    _last;

        };
    }
}

