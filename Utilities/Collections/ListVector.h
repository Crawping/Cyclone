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
                /// <summary> Gets the total number of slots that are available for storing data elements. </summary>
                virtual uint Capacity()         const { return Data.Count(); }
                /// <summary> Gets the number of slots that are being used to store data elements. </summary>
                virtual uint Count()            const { return _count; }
                /// <summary> Gets a reference to the first data element stored in the vector. </summary>
                virtual T& First()              { return Data(_index); }
                /// <summary> Gets a constant reference to the first data element stored in the vector. </summary>
                virtual const T& First()        const { return Data(_index); }
                /// <summary> Gets a reference to the last data element stored in the vector. </summary>
                virtual T& Last()               { return Data(_index + _count - 1); }
                /// <summary> Gets a constant reference to the last data element stored in the vector. </summary>
                virtual const T& Last()         const { return Data(_index + _count - 1); }



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
                virtual void Clear()
                {
                    _count = 0;
                    _index = Capacity() / 2;
                }
                virtual void Insert(uint idx, const T& value)
                {
                    InsertBlock(idx, 1);
                    Data(_index + idx) = value;
                }
                virtual void Insert(uint idx, const ICollection<T>& values)
                {
                    InsertBlock(idx, values.Count());
                    for (uint a = 0; a < values.Count(); a++)
                        Data(_index + idx++) = values(a);
                }
                virtual void Prepend(const T& value)                            { Insert(0, value); }
                virtual void Prepend(const ICollection<T>& values)              { Insert(0, values); }
                virtual void Remove(uint idx, uint n = 1)
                {
                    RemoveBlock(idx, n);
                }
                virtual void Set(uint idx, const T& value)
                {
                    int idxData = _index + idx;
                    if ( (idxData < 0) || (idxData >= Capacity()) )
                        return Insert(idx, value);
                    Data(idxData) = value;
                }
                virtual void Swap(uint idxFirst, uint idxSecond)
                {
                    Data.Swap(_index + idxFirst, _index + idxSecond);
                }



                /** OPERATORS **/
                virtual Iterator begin()                    { return Iterator(_index, &Data); }
                virtual Iterator end()                      { return Iterator(_index + Count(), &Data); }
                virtual T& operator ()(uint index)          { return Data(_index + index); }
                virtual const T& operator ()(uint index)    const override { return Data(_index + index); }

            protected:

                /** PROPERTIES **/
                uint LeftMargin()       const { return _index; }
                uint RightMargin()      const { return Capacity() - _index - Count(); }



                /** UTILITIES **/
                virtual void InsertBlock(uint idx, uint n)
                {
                    if (n == 0) { return; }

                    idx = clamp(idx, (uint)0, _count);
                    uint newCount = Count() + n;
                    Reallocate(Count() + n);

                    if (idx == 0)
                    {
                        uint nmoved = Math::Min(n, LeftMargin());
                        Move(idx, Count(), n - nmoved);
                        _index -= nmoved;
                        _count += nmoved;
                    }
                    else if (idx <= Count() / 2)
                    {
                        uint nmoved = Math::Min(n, LeftMargin());
                        Move(0, idx, -(int)nmoved);
                        Move(idx, Count() - idx, n - nmoved);
                    }
                    else
                    {
                        uint nmoved = Math::Min(n, RightMargin());
                        Move(idx, Count() - idx, nmoved);
                        Move(0, idx, -(int)(n - nmoved));
                    }
                }
                virtual void RemoveBlock(uint idx, uint n)
                {
                    if (n == 0) { return; }

                    idx = clamp(idx, (uint)0, Count());
                    if (idx == 0)
                    {
                        _index += n;
                        _count -= n;
                    }
                    else if (idx == Count() - n)
                        _count -= n;
                    else if (idx <= Count() / 2)
                    {
                        Move(0, idx, n);
                        _index += n;
                        _count -= 2 * n;
                    }
                    else
                    {
                        Move(idx, Count() - idx, -(int)n);
                        _count -= 2 * n;
                    }
                }

            private:

                uint _count;
                uint _index;

                Vector<T> Data;



                /** UTILITIES **/
                void Move(uint idx, uint count, int offset)
                {
                    if (!(offset && count && Count())) { _count += abs(offset); return; }

                    uint idxStart = _index + idx;
                    uint idxEnd = idxStart + count - 1;

                    if (offset > 0)
                    {
                        for (uint a = idxEnd; a > idxStart; a--)
                            Data(a + offset) = Data(a);
                        Data(idxStart + offset) = Data(idxStart);
                    }
                    else
                    {
                        for (uint a = idxStart; a <= idxEnd; a++)
                            Data(a + offset) = Data(a);
                        _index += offset;
                    }

                    _count += abs(offset);
                }
                void Reallocate(uint n)
                {
                    if (n <= Capacity()) { return; }

                    uint newCap = nextpow2(n);
                    Vector<T> newData(newCap);
                    uint idx = (newCap / 4);

                    for (uint a = _index; a < _index + _count; a++)
                        newData(idx++) = Data(a);

                    _index = newCap / 4;
                    Data = newData;
                }

        };
    }
}
