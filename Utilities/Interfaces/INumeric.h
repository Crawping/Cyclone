/* CHANGELOG
 * Written by Josh Grooms on 20170711
 */

#pragma once
#include "Meta/Expressions.h"



namespace Cyclone
{
    namespace Utilities
    {
        
        /** INTERFACES **/
        struct IAddable         { };
        struct IDivisible       { };
        struct IEquatable       { };
        struct INumeric         { };
        struct IMultiplicable   { };
        struct ISubtractable    { };



        /** SPECIALIZATIONS **/
        namespace Meta
        {
            template<typename T> struct IsA<T, IAddable>:         IsAddable<T> { };
            template<typename T> struct IsA<T, IDivisible>:       IsDivisible<T> { };
            template<typename T> struct IsA<T, IEquatable>:       IsEquatable<T> { };
            template<typename T> struct IsA<T, IMultiplicable>:   IsMultiplicable<T> { };
            template<typename T> struct IsA<T, ISubtractable>:    IsSubtractable<T> { };

            template<typename T> struct IsA<T, INumeric>:         Conditional
            <
                IsAddable<T>::Value         && 
                IsDivisible<T>::Value       &&
                IsEquatable<T>::Value       &&
                IsMultiplicable<T>::Value   &&
                IsSubtractable<T>::Value,
                Boolean<true>, Boolean<false>
            > { };
        }

    }
}
