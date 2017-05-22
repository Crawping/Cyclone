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

                template<typename ... V>
                constexpr static uint IndexOf(V ... indices)
                {
                    return IndexOf(NativeArray<uint, sizeof...(V)>{ indices... }.Flip());
                }

                template<uint N>
                constexpr static uint IndexOf(const NativeArray<uint, N>& indices)
                {
                    using A = Meta::Array<uint, U...>;
                    return indices(0) * A::Product<N - 1>() + IndexOf(indices.Pop());
                }
                template<> constexpr static uint IndexOf<1>(const NativeArray<uint, 1>& indices)
                {
                    return indices(0);
                }

            public:

                /** PROPERTIES **/
                constexpr uint Count()                          const /*override */{ return _count; }
                constexpr uint Rank()                           const /*override */{ return _rank; }
                constexpr static Array<uint, _rank> Size()      { return Array<uint, _rank>(_size); }



                /** CONSTRUCTORS **/
                constexpr Array():
                    _values { 0 }
                {

                }
                template<typename V, V ... W>
                constexpr Array(const Meta::Array<V, W...>& values):
                    _values { W... }
                {

                }
                constexpr Array(const T values[_count]):
                    Array(values, Meta::Range<uint, 0, _count - 1>())
                {

                }
                constexpr Array(const std::initializer_list<T>& values):
                    _values{ }
                {
                    for (uint a = 0; a < values.size(); a++)
                        _values[a] = *(values.begin() + a);
                }



                /** UTILITIES **/
                constexpr uint Size(uint dimension) const
                {
                    return (dimension >= _rank) ? 1 : _size[dimension];
                }


                /** OPERATORS **/
                virtual T& operator()(uint index)               { return _values[index]; }
                constexpr const T& operator ()(uint index)      const /*override*/ { return _values[index]; }

                template<typename ... V>
                constexpr const T& operator ()(V ... indices)   const
                {
                    return _values[ IndexOf(indices...) ];
                }

        };
    }
}
