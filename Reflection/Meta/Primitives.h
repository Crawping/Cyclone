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
            /// <summary> A compile-time Boolean primitive. </summary>
            template<bool value> using Boolean                  = Primitive<bool, value>;
            /// <summary> A compile-time character primitive. </summary>
            template<char value> using Character                = Primitive<char, value>;
            /// <summary> A compile-time signed 32-bit integer primitive. </summary>
            template<int U> using Integer32                     = Primitive<int, U>;
            /// <summary> A compile-time unsigned 32-bit integer primitive. </summary>
            template<uint U> using Integer32U                   = Primitive<uint, U>;
            
        }
    }
}
