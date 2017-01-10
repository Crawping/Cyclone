/* CHANGELOG
 * Written by Josh Grooms on 20170110
 */

#pragma once
#include "Utilities.h"
#include "Collections/Vector.h"



namespace Cyclone
{
    namespace Utilities
    {
        
        template<typename T>
        class ListVector : public ICollection<T>
        {

            public:

                /** PROPERTIES **/
                virtual uint Capacity() const { return Data.Count(); }
                virtual uint Count()    const { return _count; }



                /** CONSTRUCTOR **/
                ListVector(uint n = 128) : 
                    _count(0),
                    _index(n / 4),
                    Data(n)
                {

                }



                /** UTILITIES **/
                virtual void Append(const T& value)                     { Insert(Count(), value); }
                virtual void Append(const ICollection<T>& values)       { Insert(Count(), values); }
                virtual void Insert(int idx, const T& value)
                {
                    int idxVal = _index + idx;
                    if (idx < 0)
                    {
                        if (idxVal < 0)
                        {
                            uint offset = _index - idx;
                            uint newCount = offset + _count;
                            idxVal = newCount / 4;
                            Reallocate(2 * newCount, offset);
                        }

                        Data(idxVal) = value;
                        //_count = 

                    }

                    if (idx >= _count)
                    {
                        if (idxVal >= Capacity())
                        {
                            uint newCap = 2 * Capacity();
                            while (idxVal >= newCap) { newCap *= 2; }
                            Reallocate(newCap, _index);
                        }

                        Data(idxVal) = value;
                        _count = idx + 1;
                    }
                    else
                    {
                        if (_index + _count + 1 >= Capacity())
                            Reallocate(2 * Capacity(), _index);;

                        uint nToMove = _count - idx;
                        Move(_index + idx, nToMove, 1);
                        Data(idxVal) = value;
                        _count++;
                    }
                }
                virtual void Insert(uint idx, const ICollection<T>& values)
                {

                }
                virtual void Prepend(const T& value)
                {

                }
                virtual void Prepend(const ICollection<T>& values)
                {

                }
                

                virtual const T& operator ()(uint index) const override
                {
                    return Data(_index + index);
                }



            protected:

                virtual void Move(uint idx, uint count, int n)
                {
                    //  [ 0, 0, 0, 0, a, b, c, d, 0, 0, 0, 0 ]

                    if (n == 0) { return; }

                    if (n > 0)
                        for (uint a = idx + count + n - 1; a > idx; a--)
                            Data(a) = Data(a - n);
                    else
                        for (uint a = idx; a < count; a++)
                            Data(a + n) = Data(a);
                }

                virtual void Reallocate(uint n, int offset)
                {
                    Vector<T> newData(n);
                    uint idx = (n / 4) + offset;
                    for (uint a = _index; a < _index + _count; a++)
                        newData(idx++) = Data(a);

                    _index = idx;
                    Data = newData;
                }


            private:

                uint _count;
                uint _index;

                Vector<T> Data;



        };
    }
}
