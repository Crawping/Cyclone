/* CHANGELOG
 * Written by Josh Grooms on 20170711
 */

#pragma once
#include "Meta/Expressions.h"


namespace Cyclone
{
    namespace Utilities
    {


        

        //template<typename T, Meta::EnableIf< M>
        //class IAdd

        struct IAddable { };





        namespace Meta
        {

            struct Nothing { };
            //template<typename T, typename U> Nothing operator +(const T&, const U&);
            //template<typename T, typename U> Nothing operator ==(const T&, const U&);

            //struct NaN { };


            template<typename T, typename U> struct IsAddable:      IsEqual<decltype(Declare<T>() + Declare<U>()), Nothing> { };
            template<typename T, typename U> struct IsEquatable:    IsEqual<decltype(Declare<T>() == Declare<U>()), Nothing> { };
            


            //template<typename T> struct IsA<T, IAddable>:   
        }

        //class IAddable
        //{
        //    public:

        //        
        //        //virtual Meta::Disable<IAddable> operator +(const IAddable& other)          const = 0;

        //};

    }
}
