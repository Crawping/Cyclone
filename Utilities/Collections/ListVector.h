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
                ListVector(const ICollection<T>& values) :
                    _count(0),
                    _index(n / 4),
                    Data(nextpow2(values.Count()))
                {

                }
                ListVector(std::initializer_list<T> values) :
                    _count(0),
                    _index(n / 4),
                    Data(nextpow2(values.size()))
                {
                    uint idx = 0;
                    for (const T& v : values)
                        Set(idx++, v);
                }




                /** UTILITIES **/
                virtual void Append(const T& value)                             { Insert(Count(), value); }
                virtual void Append(const ICollection<T>& values)               { Insert(Count(), values); }
                virtual void Insert(int idx, const T& value)
                {
                    InsertBlock(idx, 1);
                    if (idx < 0)
                        Data(_index) = value;
                    else
                        Data(_index + idx) = value;
                    

                    //if (idx < 0)
                    //{
                    //    if (idxData < 0)
                    //    {
                    //        uint newCap = 2 * Capacity();
                    //        while ((_count - idx) >= newCap) { newCap *= 2; }
                    //        Reallocate(newCap, -idx);
                    //        idxData = _index;
                    //    }

                    //    _count = _count - idx;
                    //    _index = idxData;
                    //    Data(idxData) = value;
                    //}
                    //else if (idx >= _count)
                    //{
                    //    if (idxData >= Capacity())
                    //    {
                    //        uint newCap = 2 * Capacity();
                    //        while (idxData >= newCap) { newCap *= 2; }
                    //        Reallocate(newCap);
                    //        idxData = _index + idx;
                    //    }

                    //    Data(idxData) = value;
                    //    _count = idx + 1;
                    //}
                    //else
                    //{
                    //    if (_index + _count + 1 >= Capacity())
                    //        Reallocate(2 * Capacity());

                    //    uint nToMove = _count - idx;
                    //    Move(_index + idx, nToMove, 1);
                    //    Data(idxData) = value;
                    //    _count++;
                    //}
                }
                virtual void Insert(int idx, const ICollection<T>& values)
                {

                }
                virtual void Prepend(const T& value)                            { Insert(0, value); }
                virtual void Prepend(const ICollection<T>& values)              { Insert(0, values); }
                virtual void Set(int idx, const T& value)
                {
                    int idxData = _index + idx;
                    if ( (idxData < 0) || (idxData >= Capacity()) )
                        return Insert(idx, value);
                    Data(idxData) = value;
                }



                /** OPERATORS **/
                virtual T& operator ()(uint index)          { return Data(_index + index); }
                virtual const T& operator ()(uint index)    const override { return Data(_index + index); }



            protected:

                virtual void InsertBlock(int idx, uint n)
                {
                    int idxData = _index + idx;
                    uint count = 0, offset = 0;

                    if (idx < 0)
                    {
                        count = _index - idx + n + _count;
                        offset = _index - idx + n;
                    }
                    else if (idx > _count)
                    {
                        count = _count + idx + n;
                    }
                    else
                    {
                        count = _count + n;
                        Move(idxData, _count - idxData, n);
                    }

                    /*needsReallocation = (count >= Capacity());*/
                    Reallocate(count, offset);


                    /*if (idx < 0)
                        if (idxData < 0)
                        {
                            count = _index - idx + n + _count;
                            offset = -idx;
                        }
                        else if (idxData)
                        {

                        }
                        else
                        {
                            _index += idx;
                            _count -= idx;
                            return;
                        }
                    else if (idx >= _count)
                        if (idxData >= Capacity())
                            count = idx + n;
                         else
                        {
                            _count = idx + n;
                            return;
                        }
                    else
                    {
                        _count += n;
                        Move(idx, _count - idx, n);
                        return;
                    }*/

                    //if (idxData < 0)
                    //{
                    //    newCount = _index - idx + _count;
                    //    offset = -idx;
                    //}
                    //else if (idxData >= Capacity())
                    //    newCount = idx - _index + n;
                    //else
                    //    return Move(idx, _count - idx, n);

                    //if (newCount >= Capacity())
                    //    Reallocate(nextpow2(newCount), offset);
                    //else
                    //    Move(_index, )

                    //Reallocate(count, offset);
                }

                virtual void Move(int idx, uint count, int n)
                {
                    //  [ 0, 0, 0, 0, a, b, c, d, 0, 0, 0, 0 ]

                    if (n == 0) { return; }
                    uint idxData = _index + idx;
                    if (n > 0)
                        for (uint a = idxData + count + n - 1; a > idxData; a--)
                            Data(a) = Data(a - n);
                    else
                        for (uint a = idxData; a < count; a++)
                            Data(a + n) = Data(a);

                    _count += n;
                }

                virtual void Reallocate(uint n, int offset = 0)
                {
                    if (n <= Capacity()) { return; }
                    uint newCap = nextpow2(n);

                    Vector<T> newData(newCap);
                    uint idx = (newCap / 4) + offset;
                    for (uint a = _index; a < _index + _count; a++)
                        newData(idx++) = Data(a);

                    _count = n;
                    _index = newCap / 4;
                    Data = newData;
                }


            private:

                uint _count;
                uint _index;

                Vector<T> Data;
        };
    }
}
