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

                virtual void InsertBlock(uint idx, uint n)
                {
                    if (n == 0) { return; }
                    uint count = _count, offset = 0;



                    if (idx < _count)
                        Move(idx, _count - idx, n);

                    Reallocate(count + n, offset);
                }

                virtual void Redistribute(uint idx, uint offset)
                {

                }


            private:

                uint _count;
                uint _index;

                Vector<T> Data;



                virtual void Move(int idx, int offset)
                {
                    if (offset == 0) { return; }

                    uint idxData = _index + idx;
                    if (n > 0)
                        for (uint a = idxData + count + n - 1; a > idxData; a--)
                            Data(a) = Data(a - n);
                    else
                        for (uint a = idxData; a < count; a++)
                            Data(a + n) = Data(a);

                    _count += n;
                }
                void Reallocate(uint n, uint idx = 0, uint offset = 0)
                {
                    if (n <= Capacity())
                        return Move(idx, offset);

                    //if (n <= Capacity()) { _count = n; _index += offset; return; }
                    uint newCap = nextpow2(n);

                    Vector<T> newData(newCap);
                    uint idx = (newCap / 4) + offset;
                    for (uint a = _index; a < _index + _count; a++)
                        newData(idx++) = Data(a);

                    _count = n;
                    _index = newCap / 4;
                    Data = newData;
                }

        };
    }
}
