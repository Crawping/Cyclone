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
                uint Count()    const { return _count; }
                bool IsEmpty()  const { return Count() == 0; }
                T& First()            { return _first.Value; }
                T& Last()             { return _last.Value; }


                /** CONSTRUCTORS & DESTRUCTOR **/
                List() :
                    _count(0),
                    _first(nullptr),
                    _last(nullptr)
                {
                    
                }

                ~List()
                {
                    Clear();
                }


                void Append(const T& value)
                {
                    Node<T>* newNode = new Node<T>(value, _last, nullptr);

                    if (IsEmpty())
                        _first = newNode;
                    else
                    {
                        _last->Next = newNode;
                        _last = newNode;
                    }

                    _count++;
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
                    index = index > Count() ? Count() : index;

                    Node<T>* toShift = _first;
                    for (uint a = 0; a < index; a++)
                        toShift = toShift->Next;

                    Node<T>* newNode = new Node<T>(value, toShift->Previous, toShift);
                    if (toShift->Previous)
                        toShift->Previous->Next = newNode;
                    else
                        _first = newNode;

                    toShift->Previous = newNode;
                }

                void Prepend(const T& value)
                {
                    Node<T>* newNode = new Node<T>(value, nullptr, _first);

                    if (IsEmpty())
                        _first = newNode;
                    else
                    {
                        _first->Previous = newNode;
                        _first = newNode;
                    }

                    _count++;
                }

                void Remove(uint index)
                {
                    if (index >= Count()) { return; }

                    Node<T>* toRemove = _first;
                    for (uint a = 0; a < index; a++)
                        toRemove = toRemove->Next;

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
                




            private:

                template<typename T>
                struct Node
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


                uint        _count;
                Node<T>*    _first;
                Node<T>*    _last;

        };
    }
}

