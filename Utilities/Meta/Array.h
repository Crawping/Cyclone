/* CHANGELOG
 * Written by Josh Grooms on 20170513
 */

#pragma once
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            template<typename T, T ... U>
            struct Array
            {
                template<uint N, T V, T ... W> struct Element;

                private:

                    template<uint N, T V, T W, T ... X> 
                    struct MultiplyElements:                                    public MultiplyElements<N - 1, V * W, X...> { };
                    template<T V, T W, T ... X>
                    struct MultiplyElements<1, V, W, X...>:                     public Primitive<T, V> { };

                    template<uint N, T V, T ... W> struct RemoveElements:       public RemoveElements<N - 1, W...> { };
                    template<T V, T ... W> struct RemoveElements<0, V, W...>:   public Array<T, V, W...> { };

                    template<uint I, uint N, T V, T ... W> 
                    struct TakeElements:                                        public TakeElements<I - 1, N, W..., V> { };
                    template<uint N, T V, T ... W> 
                    struct TakeElements<0, N, V, W...>:                         public RemoveElements<N, V, W...> { };

                    template<uint I, uint N, T V, T ... W> 
                    struct SliceElements:                                       public SliceElements<I - 1, N, W...> { };
                    template<uint N, T V, T ... W> 
                    struct SliceElements<0, N, V, W...>:                        public TakeElements<N, sizeof...(W) + 1 - N, V, W...> { };

                public:

                    /** STATIC DATA **/
                    constexpr const static uint Numel       = sizeof...(U);
                    constexpr const static T Value[Numel]   = { U... };



                    /** SUBTYPES **/
                    template<uint N, T V, T ... W> struct Element:              public Element<N - 1, W...> { };
                    template<T V, T ... W> struct Element<0, V, W...>:          public Primitive<T, V> { };



                    /** META PROPERTIES **/
                    using Count     = Integer32U<sizeof...(U)>;
                    using First     = Element<0, U...>;
                    using IsEmpty   = Boolean<false>;
                    using Last      = Element<sizeof...(U) - 1, U...>;



                    /** META UTILITIES **/
                    template<T ... V> using Append          = Array<T, U..., V...>;
                    template<uint N> using Get              = Element<N, U...>;
                    template<T ... V> using Prepend         = Array<T, V..., U...>;
                    template<uint N> using Product          = MultiplyElements<N, U..., 1>;
                    template<uint N> using Remove           = RemoveElements<N, U...>;
                    template<uint I, uint N> using Slice    = SliceElements<I, N, U...>;
                    template<uint N> using Take             = TakeElements<N, Numel - N, U...>;

                    constexpr const T& operator ()(uint index)                  const { return Value[index]; }

                    template<uint N = Numel, T ... V> struct Flip:              public Flip<N - 1, V..., Get<N - 1>::Value> { };
                    template<T ... V> struct Flip<0, V...>:                     public Array<T, V...> { };

            };

            template<typename T, uint N, T U, T ... V> struct Fill:             public Fill<T, N - 1, U, U, V...> { };
            template<typename T, T U, T ... V> struct Fill<T, 0, U, V...>:      public Array<T, V...> { };

            template<typename T, uint N, T ... U> struct Zeros:                 public Zeros<T, N - 1, 0> { };
            template<typename T, T ... U> struct Zeros<T, 0, U...>:             public Array<T, U...> { };



            template<typename T, uint N, int S, T U, T ... V>
            struct Sequence:                    public Sequence<T, N - 1, S, U, U + N * S, V...> { };
            template<typename T, int S, T U, T ... V>
            struct Sequence<T, 0, S, U, V...>:  public Array<T, U, V...> { };


            template<typename T, T X, T Y> struct Range:
                public Conditional<(X < Y), Sequence<T, Y - X, 1, X>, Sequence<T, X - Y, -1, X>> { };

            template<typename T, typename ... U> 
            constexpr T Product(T first, U ... values)
            {
                return first * Product(values...);
            }
            template<typename T>
            constexpr T Product(T first) { return first; }

            template<typename T, T ... U>
            constexpr T Product(const Array<T, U...>& values) { return Product(U...); }

        }
    }
}
