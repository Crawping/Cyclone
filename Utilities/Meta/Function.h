/* CHANGELOG
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "IO/Functions.h"
#include "Meta/List.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {
            template<typename T, typename ... U>
            struct Function : public Class< FunctionPointer<T, U...> >
            {
                using Inputs        = List<U...>;
                using IsPointer     = Boolean<true>;
                using Output        = T;
            };

            template<typename T> struct InputTypes              { };
            template<typename T, typename U, typename ... V>
            struct InputTypes< MethodPointer<T, U, V...> >:     List<V...> { using Value = List<V...>; };

            template<typename T> struct ReturnType              { };
            template<typename T, typename U, typename ...V>
            struct ReturnType< MethodPointer<T, U, V...> >      { using Value = T; };

            template<typename T, typename ... U>
            struct ReturnType< ICallback<T, U...> >             { using Value = T; };
        }
    }
}
