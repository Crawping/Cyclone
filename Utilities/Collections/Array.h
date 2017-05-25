/* CHANGELOG
 * Written by Josh Grooms on 20170513
 */

#pragma once
#include "Collections/Vector.h"
#include "Meta/Array.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, uint ... U>
        struct Array
        {
            private:

                /** STATIC DATA **/
                constexpr static uint _rank         = sizeof...(U);
                constexpr static uint _count        = Meta::Product(U...);
                constexpr static uint _size[_rank]  = { U... };



                /** DATA **/
                T _values[_count];





            public:

                /** PROPERTIES **/
                constexpr static uint Count()                   { return _count; }
                constexpr static uint Rank()                    { return _rank; }
                constexpr static Array<uint, _rank> Size()      { return Array<uint, _rank>(_size); }



                /** CONSTRUCTORS **/
                constexpr Array():
                    _values{ 0 }
                {

                }
                constexpr Array(const T& value):
                    _values{ }
                {
                    for (uint a = 0; a < _count; a++)
                        _values[a] = value;
                }
                constexpr Array(const T values[_count]):
                    _values{ }
                {
                    for (uint a = 0; a < _count; a++)
                        _values[a] = values[a];
                }
                constexpr Array(const std::initializer_list<T>& values):
                    _values{ }
                {
                    for (uint a = 0; a < values.size(); a++)
                        _values[a] = *(values.begin() + a);
                }

                template<uint N, uint ... V>
                constexpr Array(const Array<T, V...>& values, const Array<T, N>& indices):
                    _values{ }
                {
                    for (uint a = 0; a < indices.Count(); a++)
                        _values[a] = values(indices(a));
                }



                /** UTILITIES **/
                constexpr static uint Count(uint dimension)
                {
                    uint count = Size(0);
                    for (uint a = 1; a <= dimension; a++)
                        count *= Size(a);
                    return count;
                }
                constexpr Array<T, _count> Flatten()                            const { return { _values }; }
                constexpr static Array<uint, _rank> SubscriptsOf(uint index)
                {

                }
                constexpr static uint Size(uint dimension)
                {
                    return (dimension >= _rank) ? 1 : _size[dimension];
                }

                template<typename ... V>
                constexpr static uint IndexOf(V ... indices)
                { 
                    return IndexOf( Array<uint, sizeof...(V)>{ uint(indices)... } );
                }
                template<uint N>
                constexpr static uint IndexOf(const Array<uint, N>& indices)
                {
                    uint idx = indices(0U);
                    for (uint a = 1; a < indices.Count(); a++)
                        idx += indices(a) * Count(a - 1);
                    return idx;
                }



                /** OPERATORS **/
                virtual T& operator ()(uint index)                              { return _values[index]; }
                constexpr const T& operator ()(uint index)                      const { return _values[index]; }

                template<typename ... V>
                constexpr const T& operator ()(V ... indices)                   const { return _values[IndexOf(indices...)]; }
                template<uint N>
                constexpr Array<T, N> operator ()(const Array<T, N>& indices)   const
                {
                    return Array<T, N>(*this, indices);
                }

        };

    }
}
