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
            struct IsRelated:                       Conditional< IsRelative<T, U>::Value, Boolean<true>, IsRelated<T, V...> > { };
            template<typename T, typename U>
            struct IsRelated<T, U>:                 IsRelative<T, U> { };

            template<typename T, typename U, typename ... V>
            struct IsSubtype:                       Conditional< IsA<T, U>::Value, Boolean<true>, IsSubtype<T, V...> > { };
            template<typename T, typename U>
            struct IsSubtype<T, U>:                 IsA<T, U> { };



            template<bool S, typename T = void>
            struct Disable                          { using Type = T; };

            template<typename T> 
            struct Disable<false, T>                { };

            template<bool S, typename T = void>
            struct Enable                           { };

            template<typename T>
            struct Enable<true, T>                  { using Type = T; };



            template<typename T, typename U = void>
            using DisableIf                         = typename Disable<T::Value, U>::Type*;
        
            template<typename T, typename U = void>
            using EnableIf                          = typename Enable<T::Value, U>::Type*;



            template<typename T, typename ... U>
            using DisableRelatives                  = typename DisableIf< IsRelated<T, U...> >;
            
            template<typename T, typename ... U>
            using DisableTypes                      = typename DisableIf< IsMember<T, U...> >;

            template<typename T, typename ... U>
            using EnableRelatives                   = typename EnableIf< IsRelated<T, U...> >;

            template<typename T, typename ... U>
            using EnableTypes                       = typename EnableIf< IsMember<T, U...> >;

        }
    }
}
