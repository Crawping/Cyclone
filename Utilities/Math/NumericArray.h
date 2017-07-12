/* CHANGELOG
 * Written by Josh Grooms on 20170712
 */

#pragma once
#include "Collections/Array.h"
#include "Meta/Expressions.h"
#include "Meta/Queries.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, typename U, uint ... V, Meta::EnableIf<Meta::IsAddable<T, U>> = 0>
        constexpr auto operator +(const Array<T, V...>& x, const Array<U, V...>& y)
        {
            using Type = decltype(Meta::Declare<T>() + Meta::Declare<U>());
            Array<Type, V...> z;

            for (uint a = 0; a < x.Count(); a++)
                z(a) = x(a) + y(a);

            return z;
        }

    }
}
