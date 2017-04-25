/* CHANGELOG
 * Written by Josh Grooms on 20170421
 */

#pragma once
#include "TypeDefinitions.h"
#include "Meta/Class.h"



namespace Cyclone
{
    namespace Reflection
    {

        using namespace Utilities;

        namespace Meta
        {

            /// <summary> A compile-time typed variable. </summary>
            template<typename T, T U> struct Primitive          : public Class<T> { constexpr operator T() const { return U; } };
            template<int U> using Integer32                     = Primitive<int, U>;
            template<uint U> using Integer32U                   = Primitive<uint, U>;


            template<uint N, typename T, typename ... U>
            struct Node                                         : public Node<N - 1, U...> { };

            template<typename T, typename ... U>
            struct Node<0, T, U...>                             : public Class<T> { };


            template<typename ... T>
            struct List
            {
                template<typename ... U>
                using Concatenate = List<T..., U...>;

                using Count = Primitive<uint, sizeof...(T)>;

                template<uint N> using Get = Node<N, T...>;

                template<uint N, typename S>
                constexpr static auto Cast(S x) -> decltype((Get<N>::Type)x)
                {
                    return (Get<N>::Type)x;
                }
            };

            template<typename ... T>
            struct Structure : List<T...>
            {

            };



            template<typename T, typename ... U>
            struct Function : public Class< FunctionPointer<T, U...> >
            {
                using Inputs        = List<U...>;
                using IsPointer     = Boolean<true>;
                using Output        = T;
            };


            

            //template<typename T, T U> struct Number             : Primitive<T, U>
            //{ 
            //    using IsIntegral    = Boolean<true>;
            //    using IsSigned      = Boolean<true>;
            //    using Precision     = Number<uint, 32>;
            //};

            ////template<byte value> struct Number<byte, value>     : Number<
            ////{
            ////    using Precision     = Number<uint, 8>;
            ////};
            //template<byte value> struct Integer8                : Number<byte, value>
            //{
            //    using Precision     = Number<uint, 8>;
            //};
            //template<uint value> struct Integer32U              : Number<uint, value>
            //{
            //    using IsSigned      = Boolean<false>;
            //};



            /*template<double value> struct Float64               : Number<double, value>
            {
                using Precision = Number<uint, 64>;
            };
            */

            //template<float value> using Float32 = Number<float, value>;

            
        }
    }
}
