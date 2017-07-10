/* CHANGELOG
 * Written by Josh Grooms on 20170709
 */

#pragma once
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            template<typename ... T>
            constexpr void Expand(T&&...)           { }


            template<typename T, typename U, typename ... V>
            struct IsRelated:                      Conditional< IsRelative<T, U>::Value, Boolean<true>, IsRelated<T, V...> > { };
            template<typename T, typename U>
            struct IsRelated<T, U>:                IsRelative<T, U> { };



            template<bool S, typename T = void>
            struct EnableIf                         { };

            template<typename T>
            struct EnableIf<true, T>                { using Type = T; };



            template<typename T, typename ... U>
            using EnableRelatives                   = typename EnableIf< IsRelated<T, U...>::Value >::Type*;

            template<typename T, typename ... U>
            using EnableTypes                       = typename EnableIf< IsMember<T, U...>::Value >::Type*;

            template<typename T, typename ... U>
            using DisableRelatives                  = typename EnableIf< !IsRelated<T, U...>::Value >::Type*;
            
            template<typename T, typename ... U>
            using DisableTypes                      = typename EnableIf< !IsMember<T, U...>::Value >::Type*;

        }
    }
}
