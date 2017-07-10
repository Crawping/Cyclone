/* CHANGELOG
 * Written by Josh Grooms on 20160806
 */

#pragma once
#include "TypeDefinitions.h"
#include "Collections/Array.h"
#include "Graphs/Node.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents a doubly-linked list of generic data. </summary>
        /// <typeparam name="T"> The type name of the data elements held by the list. </typeparam>
        template<typename T>
        class List: public ICollection<T>
        {
            public:
                //template<typename T> struct Node;
                struct Iterator;


                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in the list. </summary>
                virtual uint Count()        const override { return _count; }
                /// <summary> Gets a reference to the first data element in the list. </summary>
                virtual T& First()          { return _first->Value(); }
                /// <summary> Gets a constant reference to the first data element in the list. </summary>
                virtual const T& First()    const { return _first->Value(); }
                /// <summary> Gets a reference to the last data element in the list. </summary>
                virtual T& Last()           { return _last->Value(); }
                /// <summary> Gets a constant reference to the last data element in the list. </summary>
                virtual const T& Last()     const { return _last->Value(); }



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
                    List((const ICollection<T>&)other)
                {

                }
                /// <summary> Constructs a new linked list that is an identical deep copy of another array-like collection of data elements. </summary>
                /// <param name="other"> A pre-existing collection of data elements to be copied. </param>
                List(const ICollection<T>& other):
                    List()
                {
                    Insert(0, other);
                }
                /// <summary> Constructs a new linked list that stores the values found within an initializer list. </summary>
                /// <param name="values"> An initialization list containing the values to be stored within the new list. </param>
                List(const InitialList<T>& values):
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
                void Append(const T& value)                             { Insert(Count(), value); }
                /// <summary> Adds the contents of another collection to the end of the list. </summary>
                /// <param name="values"> An array-like collection containing the data elements to be copied and added to the list. </param>
                /// <remarks> Appending an element to this class of linked list is an O(1) operation. </remarks>
                void Append(const ICollection<T>& values)               { Insert(Count(), values); }
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
                    if (IsEmpty()) { return; }

                    auto* N = _first;
                    while (N = N->Right())
                        delete N->Left();

                    delete _last;
                    _first = _last = nullptr;
                    _count = 0;
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
                template<typename U> void Insert(uint index, U&& value)
                {
                    index = Math::Clamp(index, 0U, Count());
                    auto* N = Index(index);
                    auto* newNode = new BinaryNode<T>(std::forward<U>(value));
                    newNode->Right() = N;

                    if (IsEmpty())
                        _first = _last = newNode;
                    else if (N)
                    {
                        newNode->Left() = N->Left();
                        if (N->Left())  { N->Left() = N->Left()->Right() = newNode; }
                        else            { N->Left() = _first = newNode; }
                    }
                    else
                    {
                        newNode->Left() = _last;
                        _last = _last->Right() = newNode;
                    }

                    _count++;
                }
                /// <summary> Inserts the contents of another collection into the list starting at the specified index. </summary>
                /// <param name="index"> The numeric index at which the first element of the other collection will be placed. </param>
                /// <param name="values"> An array-like collection containing the data elements to be copied and inserted into the list. </param>
                void Insert(uint index, const ICollection<T>& values)
                {
                    for (uint a = values.Count(); a > 0; a--)
                        Insert(index, values(a - 1));
                }
                /// <summary> Adds a new data value to the beginning of the list. </summary>
                /// <param name="value"> The data element that will be copied and added to the list. </param>
                void Prepend(const T& value)                            { Insert(0, value); }
                /// <summary> Adds the contents of another collection to the beginning of the list. </summary>
                /// <param name="values"> An array-like collection containing the data elements to be copied and added to the list. </param>
                void Prepend(const ICollection<T>& values)              { Insert(0, values); }
                /// <summary> Removes the data element found at the specified index from the list. </summary>
                /// <param name="index"> The numeric index of the data element to be removed. </param>
                void Remove(uint index)
                {
                    if (index >= Count()) { return; }

                    auto* N = Index(index);
                    if (N->Left())
                        N->Left()->Right() = N->Right();
                    else
                        _first = N->Right();

                    if (N->Right())
                        N->Right()->Left() = N->Left();
                    else
                        _last = N->Left();

                    delete N;
                    _count--;
                }
                /// <summary> Swaps the values of two separate list elements. </summary>
                /// <param name="idxFirst"> The position of the first list element to be swapped. </param>
                /// <param name="idxSecond"> The position of the second list element to be swapped. </param>
                void Swap(uint idxA, uint idxB)
                {
                    if (idxA >= Count() || idxB >= Count()) { return; }
                    std::swap(Index(idxA)->Value(), Index(idxB)->Value());
                }
                /// <summary> Converts the linked list into an equivalent vector of contiguous data elements. </summary>
                /// <returns> A <see cref="Vector"/> containing copies of all data elements stored in the list. </returns>
                Vector<T> ToVector()                                    const { return Vector<T>(*this, 0, Count()); }



                /** OPERATORS **/
                Iterator begin()                                        const { return Iterator(0, _first); }
                Iterator end()                                          const { return Iterator(Count(), nullptr); }
                /// <summary> Performs linear array-like indexing of the data elements stored within the list. </summary>
                /// <param name="index"> The numeric position of the desired data element within the list. </param>
                /// <returns> A reference to the data element stored at the inputted position. </returns>
                /// <remarks>
                ///     Attempting to index into the list at an invalid position (i.e. beyond the end of the list) is an error and
                ///     will generate a runtime exception.
                /// </remarks>
                T& operator ()(uint index)                              { return Index(index)->Value(); }
                /// <summary> Performs linear array-like indexing of the data elements stored within the list. </summary>
                /// <param name="index"> The numeric position of the desired data element within the list. </param>
                /// <returns> A constant reference to the data element stored at the inputted position. </returns>
                /// <remarks>
                ///     Attempting to index into the list at an invalid position (i.e. beyond the end of the list) is an error and
                ///     will generate a runtime exception.
                /// </remarks>
                const T& operator ()(uint index)                        const override { return Index(index)->Value(); }

                /// <summary> Clears the list of any stored data and transfers the contents of another list into it. </summary>
                /// <returns> A reference to the new list object that contains the uncopied contents of the old one. </returns>
                /// <param name="other"> A pre-existing list whose contents are to be moved. </param>
                List& operator =(List&& other)
                {
                    std::swap(_count, other._count);
                    std::swap(_first, other._first);
                    std::swap(_last, other._last);
                    return *this;
                }
                /// <summary> Clears the list of any stored data and copies the contents of another list into it. </summary>
                /// <returns> A reference to the new list object that contains the copied contents of the other one. </returns>
                /// <param name="values"> Another generic list of data elements. </param>
                List& operator =(const List& values)
                {
                    Clear();
                    for (const T& v : values) { Append(v); }
                    return *this;
                }
                /// <summary> Clears the list of any stored data and copies the contents of another collection into it. </summary>
                /// <returns> A reference to the new list object that contains the copied contents of the other collection. </returns>
                /// <param name="values"> An array-like collection of data elements to be copied. </param>
                List& operator =(const ICollection<T>& values)
                {
                    Clear();
                    Insert(0, values);
                    return *this;
                }
                /// <summary> Clears the list of any stored data and copies the contents of an initialization list into it. </summary>
                /// <returns> A reference to the new list containing the copied contents of the initializer list. </returns>
                /// <param name="values"> An initialization list that contains the values to be copied. </param>
                List& operator =(const InitialList<T>& values)
                {
                    Clear();
                    for (const T& v : values) { Append(v); }
                    return *this;
                }

            private:

                /** PROPERTY DATA **/
                uint            _count;
                BinaryNode<T>*  _first;
                BinaryNode<T>*  _last;



                /** UTILITIES **/
                /// <summary> Performs linear array-like indexing of the data elements stored within the list. </summary>
                /// <param name="index"> The numeric position of the desired data element within the list. </param>
                /// <returns> A pointer to the list node that resides at the inputted position or <c>nullptr</c> if the position is invalid. </returns>
                BinaryNode<T>* Index(uint index) const
                {
                    BinaryNode<T>* N = nullptr;
                    if (index >= Count())
                        return N;
                    else if ((Count() - index) > index)
                    {
                        N = _first;
                        while (index--) { N = N->Right(); }
                    }
                    else
                    {
                        N = _last;
                        for (uint a = Count() - 1; a > index; a--)
                            N = N->Left();
                    }

                    return N;
                }


                struct Iterator
                {
                    public:

                        /** PROPERTIES **/
                        uint Index()                const { return _index; }

                        /** CONSTRUCTOR **/
                        Iterator(uint idx, BinaryNode<T>* element) :
                            _index(idx),
                            Element(element)
                        {

                        }

                        /** OPERATORS **/
                        T& operator *()                         { return Element->Value(); }
                        Iterator& operator++()                  { Element = Element->Right(); _index++; return *this; }
                        Iterator& operator++(int)               { Element = Element->Right(); _index++; return *this; }

                        bool operator ==(const Iterator& other) const 
                        {
                            return (Index() == other.Index()) && (Element == other.Element);
                        }
                        bool operator !=(const Iterator& other) const { return !operator ==(other); }

                    private:
                        uint            _index;
                        BinaryNode<T>*  Element;
                };

        };
    }
}
