/* CHANGELOG
 * Written by Josh Grooms on 20170121
 */

#pragma once
#include "Collections/ArrayList.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T>
        class Stack : public ICollection<T>
        {
            public:

                /** PROPERTIES **/
                uint Count()        const { return Data.Count(); }
                T& First()                { return Data.First(); }
                const T& First()    const { return Data.First(); }
                T& Last()                 { return Data.Last(); }
                const T& Last()     const { return Data.Last(); }



                /** CONSTRUCTOR **/
                Stack() { }
                Stack(const ICollection<T>& values) :
                    Data(values)
                {

                }
                Stack(std::initializer_list<T> values) :
                    Data(values)
                {

                }



                /** UTILITIES **/
                void Clear()                                { Data.Clear(); }
                void Insert(uint index, const T& value)     { Data.Insert(idx, value); }
                T Pop()                             
                { 
                    T value = Data.First();
                    Data.Remove(0);
                    return value;
                }
                void Push(const T& value)                   { Data.Prepend(value); }
                void Push(const ICollection<T>& values)     { Data.Prepend(values); }
                void Remove(uint index)                     { Data.Remove(index); }



                /** OPERATORS **/
                const T& operator ()(uint index)        const { return Data(index); }
                T& operator ()(uint index)              { return Data(index); }
                

            private:

                ArrayList<T> Data;

        };

    }
}
