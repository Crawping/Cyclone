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
        }
    }
}
