/* CHANGELOG
 * Written by Josh Grooms on 20170423
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Reflection
    {
        using namespace Utilities;

        namespace Meta
        {

            /** FORWARD DECLARATIONS **/
            template<typename T> struct Dereference;
            template<typename T> struct IsConstant;
            template<typename T> struct IsPointer;
            template<typename T> struct IsReference;
            template<typename T, T U> struct Primitive;
            template<bool value> using Boolean                  = Primitive<bool, value>;
            template<char value> using Character                = Primitive<char, value>;


            template<typename T> struct Class
            { 
                using Constructor   = Boolean<false>;
                /// <summary> Gets the core type from which this class is derived. </summary>
                using CoreType      = Dereference<T>;
                using Destructor    = Boolean<false>;
                /// <summary> Gets whether the type is constant qualified. </summary>
                using IsConstant    = IsConstant<T>;
                /// <summary> Gets whether the type is a reference to some core type. </summary>
                using IsReference   = IsReference<T>;
                /// <summary> Gets whether the type is a pointer to some core type. </summary>
                using IsPointer     = IsPointer<T>;
                /// <summary> Gets the number of bytes required to store instances of the type. </summary>
                using Size          = Primitive<uint, sizeof(T)>;
                /// <summary> Gets the type that this class represents. </summary>
                using Type          = T;
            };
            template<> struct Class<void>
            {
                using Constructor   = Boolean<false>;
                using CoreType      = Class<void>;
                using Destructor    = Boolean<false>;
                using IsConstant    = Boolean<false>;
                using IsReference   = Boolean<false>;
                using IsPointer     = Boolean<false>;
                using Size          = Primitive<uint, 0>;
                using Type          = void;
            };

        }
    }
}