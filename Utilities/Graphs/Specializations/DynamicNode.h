/* CHANGELOG
 * Written by Josh Grooms on 20170702
 */

#pragma once
#include "Collections/Array.h"
#include "Collections/List.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T> struct Node<T>
        {
            private:

                List<Node>  _adjacencies;
                T           _value;

            public:

                /** PROPERTIES **/
                bool IsEmpty()  const { return _adjacencies.IsEmpty(); }



                /** CONSTRUCTORS **/
                Node() { }
                template<typename U> Node(U&& value):
                    _value(std::forward<U>(value))
                {

                }



                /** OPERATORS **/
                T* operator ->()                        { return std::addressof(_value); }
                const T* operator ->()                 const { return std::addressof(_value); }

                Node& operator ()(uint index)           { return _adjacencies(index); }
                const Node& operator ()(uint index)     const { return _adjacencies(index); }
                
        };


    }
}
