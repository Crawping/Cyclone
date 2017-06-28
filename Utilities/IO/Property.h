/* CHANGELOG
 * Written by Josh Grooms on 20170609
 */

#pragma once
#include "IO/Members.h"
#include "IO/Specializations/BaseAttribute.h"
#include "IO/Specializations/BaseProperty.h"



namespace Cyclone
{
    namespace Utilities
    {

        /// <summary> A structure that represents an existing object property. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> A list of input and output argument types found in the property's accessor methods. </typeparam>
        template<typename T, typename ... U> struct Property { };

        /// <summary> A structure that represents an object property with uniform accessor arguments. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> The output and input argument type for the property's get and set accessors, respectively. </typeparam>
        template<typename T, typename U>
        struct Property<T, U>:              public BaseProperty< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, U> > 
        { 
            using BaseProperty::BaseProperty; 
            using BaseProperty::operator =;
        };

        /// <summary> A structure that represents an object property with differing accessor arguments. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> The output argument type for the property's get accessor. </typeparam>
        /// <typeparam name="V"> The input argument type for the property's set accessor. </typeparam>
        template<typename T, typename U, typename V>
        struct Property<T, U, V>:           public BaseProperty< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, V> >
        {
            using BaseProperty::BaseProperty;
            using BaseProperty::operator =;
        };



        /// <summary> A structure that represents a set of class accessor methods. </summary>
        template<typename T, typename ... U> struct Attribute { };

        template<typename T> struct Attribute<T> { };

        /// <summary> A structure that represents a set of class accessor methods. </summary>
        /// <typeparam name="T"> The class to which the accessor methods belong. </typeparam>
        /// <typeparam name="U"> The output and input argument type for the accessor methods. </typeparam>
        template<typename T, typename U>
        struct Attribute<T, U>:             public BaseAttribute< ConstMethodPointer<U, T>, MethodPointer<T&, T, U> > 
        {
            using BaseAttribute::BaseAttribute;
        };

        /// <summary> A structure that represents a set of class accessor methods. </summary>
        /// <typeparam name="T"> The class to which the accessor methods belong. </typeparam>
        /// <typeparam name="U"> The output argument type for the get accessor method. </typeparam>
        /// <typeparam name="V"> The input argument type for the set accessor method. </typeparam>
        template<typename T, typename U, typename V>
        struct Attribute<T, U, V>:          public BaseAttribute< ConstMethodPointer<U, T>, MethodPointer<T&, T, V> >
        {
            using BaseAttribute::BaseAttribute;
        };

    }
}