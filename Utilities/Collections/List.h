/* CHANGELOG
 * Written by Josh Grooms on 20160806
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {
        template<typename T>
        class List
        {
            public:

                /** PROPERTIES **/
                uint Count()                const { return _count; }
                bool IsEmpty()              const { return Count() == 0; }
                T& First()                        { return _first->Value; }
                T& Last()                         { return _last->Value; }



                /** CONSTRUCTORS & DESTRUCTOR **/
                List() :
                    _count(0),
                    _first(nullptr),
                    _last(nullptr)
                {
                    
                }

                List(List<T>&& other) :
                    _count(other._count),
                    _first(other._first),
                    _last(other._last)
                {
                    other._count = 0;
                    other._first = nullptr;
                    other._last = nullptr;
                }

                List(const List<T>& other) : 
                    List()
                {
                    for (uint a = 0; a < other.Count(); a++)
                        Append(other(a));
                }

                List(std::initializer_list<T> values) :
                    List()
                {
                    for (const T& v : values)
                        Append(v);
                }

                ~List()
                {
                    Clear();
                }



                /** UTILITIES **/
                void Append(const T& value)
                {
                    Insert(Count(), value);
                }

                void Append(const List<T>& values)
                {
                    for (uint a = 0; a < values.Count(); a++)
                        Append(values(a));
                }

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

                void Insert(uint index, const List<T>& values)
                {
                    for (uint a = values.Count() - 1; a >= 0; a--)
                        Insert(index, values(a));
                }

                void Prepend(const T& value)
                {
                    Insert(0, value);
                }

                void Prepend(const List<T>& values)
                {
                    for (uint a = values.Count() - 1; a >= 0; a--)
                        Prepend(values(a));
                }

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
                T& operator ()(uint index)                                { return Index(index)->Value; }
                const T& operator ()(uint index)                    const { return Index(index)->Value; }
                
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
                List& operator =(const List<T> values)
                {
                    Clear();
                    for (uint a = 0; a < values.Count(); a++)
                        Append(values(a));
                    return *this;
                }
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


                Node<T>* Index(uint index) const
                {                    
                    if (index >= Count())
                        return nullptr;

                    Node<T>* node = _first;
                    for (uint a = 0; a < index; a++)
                        node = node->Next;

                    return node;
                }


                uint        _count;
                Node<T>*    _first;
                Node<T>*    _last;

        };
    }
}

