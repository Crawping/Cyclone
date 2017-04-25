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
            template<bool value> using Boolean                  = Primitive<bool, value>;
            template<char value> using Character                = Primitive<char, value>;
            template<int U> using Integer32                     = Primitive<int, U>;
            template<uint U> using Integer32U                   = Primitive<uint, U>;
            
        }
    }
}
