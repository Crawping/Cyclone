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

            template<typename T, T U> struct Primitive;
            template<bool value> using Boolean                  = Primitive<bool, value>;
            template<char value> using Character                = Primitive<char, value>;

            template<typename T> struct Dereference;
            template<typename T, typename U> struct IsEqual;


            template<typename T> struct Class
            { 
                using CoreType      = Dereference<T>;
                using IsConstant    = Boolean<false>;
                using IsReference   = Boolean<false>;
                using IsPointer     = Boolean<false>;
                using Size          = Primitive<uint, sizeof(T)>;
                using Type          = T;

                ~Class() { }
            };
            template<> struct Class<void>
            {
                using CoreType      = Class<void>;
                using IsConstant    = Boolean<false>;
                using IsReference   = Boolean<false>;
                using IsPointer     = Boolean<false>;
                using Size          = Primitive<uint, 0>;
                using Type          = void;

                ~Class() { }
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

        }
    }
}