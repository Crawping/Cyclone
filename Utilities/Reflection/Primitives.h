/* CHANGELOG
 * Written by Josh Grooms on 20170421
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            template<typename T, T U> struct Primitive;
            template<bool value> using Boolean = Primitive<bool, value>;
            template<char value> using Character = Primitive<char, value>;

            template<typename T, typename U> struct IsEqual;
            template<typename T> struct SizeOf;
            template<> struct SizeOf<void>;

            
            template<typename T> struct Class
            { 
                using IsConstant    = Boolean<false>;
                using IsReference   = Boolean<false>;
                using IsPointer     = Boolean<false>;
                using Type          = T;


                template<typename U>
                constexpr bool operator ==(const Class<U>& other) const
                {
                    return 
                        IsConstant() == Class<U>::IsConstant()      &&
                        IsReference() == Class<U>::IsReference()    &&
                        IsPointer() == Class<U>::Ispointer()        &&
                        IsEqual<T, U>();
                }
            };



            template<typename T> struct Class<T*>               : public Class<T>
            {
                using IsPointer     = Boolean<true>;
            };
            template<typename T> struct Class<const T*>         : public Class<T*>
            {
                using IsConstant    = Boolean<true>;
            };

            template<typename T> struct Class<T&>               : public Class<T>
            {
                using IsReference   = Boolean<true>;
            };
            template<typename T> struct Class<const T&>         : public Class<T&>
            {
                using IsConstant    = Boolean<true>;
            };



            template<typename T, T U> struct Primitive          : public Class<T> { constexpr operator T() const { return U; } };


            template<uint N, typename T, typename ... U>
            struct Node                                         : public Node<N - 1, U...> { };

            template<typename T, typename ... U>
            struct Node<0, T, U...>                             : public Class<T> { };


            template<typename ... T>
            struct List
            {
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


            //struct Primitive<FunctionPointer, value>            : Class<FunctionPointer>
            //{
            //    using Invoke = 
            //};
            //template<bool value> struct Boolean                 : Primitive<bool, value> { };
            //template<char value> struct Character               : Primitive<char, value> { };


            //template<bool value> using Boolean = typename Primitive<bool, value>;

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
