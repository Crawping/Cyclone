/* CHANGELOG
 * Written by Josh Grooms on 20170211
 */

#pragma once
#include "Enumerator.h"
#include "Collections/ArrayList.h"
#include "IO/Functions.h"



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

        /// <summary> A class that represents an ordered collection of data elements. </summary>
        template<typename T>
        class Multiset : public virtual ICollection<T>
        {
            public:

                using Iterator = typename ArrayList<T>::Iterator;



                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in the set. </summary>
                virtual uint Count()                const override { return Data.Count(); }
                /// <summary> Gets a reference to the first data element of the set. </summary>
                virtual T& First()                  { return Data.First(); }
                /// <summary> Gets a constant reference to the first data element of the set. </summary>
                virtual const T& First()            const { return Data.First(); }
                /// <summary> Gets a reference to the last data element of the set. </summary>
                virtual T& Last()                   { return Data.Last(); }
                /// <summary> Gets a constant reference to the last data element of the set. </summary>
                virtual const T& Last()             const { return Data.Last(); }
                /// <summary> Gets the ordering scheme used to sort elements of the set. </summary>
                virtual SortOrders SortOrder()      const { return _sortOrder; }

                /// <summary> Sets the function used to compare and sort elements of the set. </summary>
                virtual Multiset& Comparator(Function<bool, const T&, const T&> value)
                {
                    _comparator = value;
                    Sort(0, Count());
                    return *this;
                }
                /// <summary> Sets the sorting order used to arrange elements of the set. </summary>
                virtual Multiset& SortOrder(SortOrders value)
                {
                    if (_sortOrder == value) { return *this; }

                    switch (value)
                    {
                        case SortOrders::Ascending:         _comparator = Multiset::LessThan; break;
                        case SortOrders::Descending:        _comparator = Multiset::GreaterThan; break;
                        default:                            break;
                    }

                    _sortOrder = value;
                    Sort(0, Count());
                    return *this;
                }



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new empty set that can be populated with data elements. </summary>
                Multiset() : 
                    _comparator(Multiset::LessThan)
                {

                }
                /// <summary> Constructs a new set containing the values found within an initalizer list. </summary>
                /// <param name="values"> An initialization list containing values to be to be inserted into the new set. </param>
                Multiset(const std::initializer_list<T>& values) : 
                    _comparator(Multiset::LessThan)
                {
                    for (const T& v : values)
                        Insert(v);
                }

                /// <summary> Constructs a new set by inserting data from another generic collection. </summary>
                /// <param name="values"> An existing generic collection whose contents are to be copied into the new set. </param>
                explicit Multiset(const ICollection<T>& values) : 
                    _comparator(Multiset::LessThan)
                {
                    for (uint a = 0; a < values.Count(); a++)
                        Insert(values(a));
                }


                /** UTILITIES **/
                virtual int Ceiling(const T& value)             const
                {
                    return -1;
                }
                /// <summary> Removes all data elements stored within the set. </summary>
                virtual void Clear() { Data.Clear(); }
                /// <summary> Determines whether the set contains a specific data element. </summary>
                /// <param name="value"> The data element to be tested for membership in the set. </param>
                /// <returns> A Boolean <c>true</c> if the element is stored in the set, or <c>false</c> otherwise. </returns>
                virtual bool Contains(const T& value)           const { return Find(value) > -1; }
                virtual int Floor(const T& value)               const
                {
                    return -1;
                }
                /// <summary> Gets the numeric index of a specific data element, if it exists in the set. </summary>
                /// <param name="value"> The data element whose index is to be found. </param>
                /// <returns> The integer array index at which the data element is stored, or <c>-1</c> if the element isn't found. </returns>
                virtual int Find(const T& value)                const
                {
                    uint idx = IndexOf(value);
                    return (idx == Count()) ? -1 :
                        (Data(idx) == value) ? idx : -1;
                }
                /// <summary> Inserts a new data element into the set, if it isn't already stored. </summary>
                /// <param name="value"> A unique data element to be inserted into the set. </param>
                /// <remarks> This operation silently fails when attempting to insert multiple copies of elements. </remarks>
                virtual void Insert(const T& value)             { Data.Insert(IndexOf(value), value); }
                /// <summary> Removes a data element from the set, if it exists. </summary>
                /// <param name="value"> The unique data element to be removed from the set. </param>
                /// <remarks> This operation silently fails when attempting to remove elements that aren't in the set. </remarks>
                virtual void Remove(const T& value)
                {
                    uint idx = IndexOf(value);
                    if (idx < Count() && Data(idx) == value)
                        Data.Remove(idx);
                }



                /** OPERATORS **/
                virtual Iterator begin()                        { return Data.begin(); }
                virtual Iterator end()                          { return Data.end(); }
                /// <summary> Performs linear array-like indexing of the data elements stored within the set. </summary>
                /// <returns> A reference to the data element stored at the inputted index. </returns>
                /// <param name="index"> The numeric position of the desired data element within the set. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
                virtual T& operator ()(uint index)              { return Data(index); }
                /// <summary> Performs linear array-like indexing of the data elements stored within the set. </summary>
                /// <returns> An immutable reference to the data element stored at the inputted index. </returns>
                /// <param name="index"> The numeric position of the desired data element within the set. </param>
                /// <remarks> Array indexing is not checked and could result in exceptions if out-of-bounds indices are provided. </remarks>
                virtual const T& operator ()(uint index)        const override { return Data(index); }

            protected:

                /** UTILITIES **/
                /// <summary> Gets the numeric index of a specific data element, if it exists in the set. </summary>
                /// <param name="value"> The data element whose index is to be found. </param>
                /// <returns></returns>
                virtual uint IndexOf(const T& value)            const
                {
                    if (IsEmpty()) { return 0; }

                    uint idx = 0, idxLower = 0, idxUpper = Count();
                    while (idxLower < idxUpper)
                    {
                        idx = idxLower + ((idxUpper - idxLower) / 2);
                        if (_comparator(Data(idx), value))      { idxLower = idx + 1; }
                        else                                    { idxUpper = idx; }
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
                        if (_comparator(Data(a), pivot))
                            Data.Swap(a, idxPivot++);

                    Data.Swap(idxEnd, idxPivot);

                    if (idxPivot > 0)
                        Sort(idxStart, idxPivot - 1);

                    Sort(idxPivot + 1, idxEnd);
                }

            private:

                Function<bool, const T&, const T&>      _comparator;
                SortOrders                              _sortOrder;
                ArrayList<T>                           Data;


                static bool GreaterThan(const T& x, const T& y)     { return x > y; }
                static bool LessThan(const T& x, const T& y)        { return x < y; }

        };
    }
}
