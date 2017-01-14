/* CHANGELOG
 * Written by Josh Grooms on 20161221
 */

#pragma once
#include "Enumerator.h"
#include "Collections/ListVector.h"



namespace Cyclone
{
    namespace Utilities
    {

        struct SortOrders : public Enumerator
        {
            enum Orders
            {
                Ascending   = 0,
                Custom      = 1,
                Descending  = 2,
            };

            constexpr SortOrders(enum Orders value = Ascending) : Enumerator((int)value) { }
        };


        template<typename T>
        class Set : public virtual ICollection<T>
        {
            public:
                
                using Iterator = typename ListVector<T>::Iterator;
                


                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in the set. </summary>
                virtual uint Count()                const override { return Data.Count(); }
                /// <summary> Gets a reference to the first data element in the set. </summary>
                virtual T& First()                  { return Data.First(); }
                /// <summary> Gets a constant reference to the first data element in the set. </summary>
                virtual const T& First()            const { return Data.First(); }
                /// <summary> Gets a reference to the last data element in the set. </summary>
                virtual T& Last()                   { return Data.Last(); }
                /// <summary> Gets a constant reference to the last data element in the set. </summary>
                virtual const T& Last()             const { return Data.Last(); }

                virtual SortOrders SortOrder()      const { return _sortOrder; }



                /** CONSTRUCTOR **/
                Set() { }
                Set(const std::initializer_list<T>& values)
                {
                    for (const T& v : values)
                        Insert(v);
                }
                Set(const ICollection<T>& values)
                {
                    for (uint a = 0; a < values.Count(); a++)
                        Insert(values(a));
                }



                /** UTILITIES **/
                int Ceiling(const T& value)         const
                {
                    return -1;
                }
                void Clear()                        { Data.Clear(); }
                bool Contains(const T& value)       const { return IndexOf(value) > -1; }
                int Floor(const T& value)           const
                {
                    return -1;
                }
                int IndexOf(const T& value)         const
                {
                    uint idx = Find(value);
                    return (idx == Count()) ? -1 :
                        (Data(idx) == value) ? idx : -1;
                }
                void Insert(const T& value)         { Data.Insert(Find(value), value); }
                void Remove(const T& value)
                {
                    int idx = Find(value);
                    if (idx < Count() && Data(idx) == value)
                        Data.Remove(idx);
                }



                /** OPERATORS **/
                Iterator begin()                    { return Data.begin(); }
                Iterator end()                      { return Data.end(); }
                T& operator ()(uint index)          { return Data(index); }
                const T& operator ()(uint index)    const override { return Data(index); }

            protected:

                /** UTILITIES **/
                virtual uint Find(const T& value) const
                {
                    if (IsEmpty()) { return 0; }

                    uint idx = 0, idxLower = 0, idxUpper = Count();
                    //Node<T>* data = Data.begin();

                    while (idxLower < idxUpper)
                    {
                        idx = idxLower + ((idxUpper - idxLower) / 2);
                        if (Data(idx) < value)      { idxLower = idx + 1; }
                        else                        { idxUpper = idx; }
                    }

                    return Data(idx) < value ? idx + 1 : idx;
                }
                virtual void Sort(uint idxStart, uint idxEnd)
                {
                    if (idxStart >= idxEnd) { return; }
                    uint idxPivot = idxStart;

                    Data.Swap(idxEnd, idxStart + ((idxEnd - idxStart) / 2));
                    const T& pivot = Data(idxEnd);

                    for (uint a = idxStart; a < idxEnd; a++)
                        if (Data(a) < pivot)
                            Data.Swap(a, idxPivot++);

                    Data.Swap(idxEnd, idxPivot);

                    if (idxPivot > 0)
                        Sort(idxStart, idxPivot - 1);

                    Sort(idxPivot + 1, idxEnd);
                }

            private:

                SortOrders      _sortOrder;
                ListVector<T>   Data;

        };
    }
}
