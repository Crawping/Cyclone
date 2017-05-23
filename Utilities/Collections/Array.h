/* CHANGELOG
 * Written by Josh Grooms on 20170513
 */

#pragma once
#include "Collections/Vector.h"
#include "Meta/Array.h"
//#include <array>



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, uint N>
        struct NativeArray
        {
            constexpr const static uint Count = N;

            T Value[N];

            constexpr const T& operator ()(uint index)  const { return Value[index]; }
            T& operator ()(uint index)                  { return Value[index]; }

            constexpr NativeArray Flip()                const { return Sort(Meta::Range<uint, N - 1, 0>()); }
            constexpr NativeArray<T, N - 1> Pop()       const { return Sort(Meta::Range<uint, 1, N - 1>()); }

            template<uint ... U>
            constexpr NativeArray<T, sizeof...(U)> Sort(const Meta::Array<T, U...>& indices) const
            {
                return { Value[U]... };
            }
        };



        template<typename T, uint ... U>
        struct Array //: public IArray<T>
        {
            private:

                /** STATIC DATA **/
                constexpr static uint _rank         = sizeof...(U);
                constexpr static uint _count        = Meta::Product(U...);
                constexpr static uint _size[_rank]  = { U... };



                /** DATA **/
                T _values[_count];



                template<uint ... V>
                constexpr Array(const T values[_count], const Meta::Array<uint, V...>& indices):
                    _values{ values[V]... }
                {

                }

                template<uint N>
                constexpr static uint IndexOf(const Array<uint, N>& indices)
                {
                    uint idx = 0;
                    for (uint a = indices.Count() - 1; a > 0; a--)
                        idx += indices(a) * Count(a - 1);
                    return idx + indices(0U);
                }

            public:

                /** PROPERTIES **/
                constexpr uint Count()                          const /*override */{ return _count; }
                constexpr uint Rank()                           const /*override */{ return _rank; }
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
                template<typename V, V ... W>
                constexpr Array(const Meta::Array<V, W...>& values):
                    _values{ W... }
                {

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



                /** UTILITIES **/
                constexpr static uint Count(uint dimension)
                {
                    uint count = Size(0);
                    for (uint a = 1; a <= dimension; a++)
                        count *= Size(a);
                    return count;
                }
                constexpr static uint Size(uint dimension)
                {
                    return (dimension >= _rank) ? 1 : _size[dimension];
                }


                /** OPERATORS **/
                virtual T& operator()(uint index)               { return _values[index]; }
                constexpr const T& operator ()(uint index)      const /*override*/ { return _values[index]; }

                template<typename ... V>
                constexpr const T& operator ()(V ... indices)   const
                {
                    return _values[IndexOf(Array<uint, sizeof...(V)>{ indices... })];
                }

        };
    }
}
