/* CHANGELOG
 * Written by Josh Grooms on 20170609
 */

#pragma once
#include "IO/Members.h"



namespace Cyclone
{
    namespace Utilities
    {

        /// <summary> A structure that represents an object data member accessible via get and set functions. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> A list of class method pointers representing the accessor functions of the property. </typeparam>
        template<typename T, typename ... U> struct PropertyBase { };

        /// <summary> A structure that represents an object data member accessible via get and set functions. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> The get accessor function of the property. </typeparam>
        /// <typeparam name="V"> The set accessor function of the property. </typeparam>
        template<typename T, typename U, typename V> 
        struct PropertyBase<T, U, V>
        {
            using OutputType = typename Meta::Functor<U>::Output;
            using InputType = typename Meta::Functor<V>::Inputs::First::Type;

            private:

                PropertyBase<void, U, V>    _accessors;
                T*                          _object;

            public:
                
                PropertyBase(T* object, U get, V set):
                    _accessors(get, set),
                    _object(object)
                {

                }
                PropertyBase(T* object, PropertyBase<void, U, V> accessors):
                    _accessors(accessors),
                    _object(object)
                {

                }



                /** UTILITIES **/
                PropertyBase<void, U, V> Unbind()               const { return _accessors; }


                template<typename ... W>
                auto operator ()(W ... arguments)               const { return _accessors(_object, arguments...); }


                /// <summary> Implicitly converts the property to its underlying type by calling the get accessor. </summary>
                /// <returns> The result of calling the get accessor function. </returns>
                operator OutputType()                           const { return _accessors(_object); }
                /// <summary> Calls the property's set accessor function with the inputted value. </summary>
                /// <param name="value"> The value to be forwarded to the property's set accessor. </param>
                PropertyBase& operator =(InputType value)       { _accessors(_object, value); return *this; }
                /// <summary> Calls the property's set accessor with the output of another property's get accessor. </summary>
                /// <typeparam name="W"> The class to which the other property belongs. </typeparam>
                /// <typeparam name="X"> A list of accessor methods associated with the other property. </typeparam>
                /// <param name="value"> Another object property with a compatible output type. </param>
                /// <remarks>
                ///     The inputted property in this method must contain a get accessor whose output type can be used in a call 
                ///     to this property's set accessor. Compilation errors will result when incompatible types are detected.
                /// </remarks>
                template<typename W, typename ... X>
                PropertyBase& operator =(PropertyBase<W, X...> value)
                {
                    using Other = PropertyBase<W, X...>;
                    static_assert(Meta::IsA< Other::OutputType, InputType >(),
                        "Types must agree.");

                    _accessors(_object, value());
                    return *this;
                }


                bool operator ==(OutputType value)              const { return (_accessors(_object) == value); }
                bool operator !=(OutputType value)              const { return !operator ==(value); }

        };

        /// <summary> A structure that represents only the get and set functions for a value. </summary>
        /// <typeparam name="U"> The get accessor function of the property. </typeparam>
        /// <typeparam name="V"> The set accessor function of the property. </typeparam>
        /// <remarks>
        ///     Unlike the less specialized versions, this type of base property represents only the get and set 
        ///     functions of a property, and therefore can be attached to any compatible class instance.
        /// </remarks>
        template<typename T, typename U> 
        struct PropertyBase<void, T, U>
        {
            using OutputType = typename Meta::Functor<T>::Output;
            using InputType = typename Meta::Functor<U>::Inputs::First::Type;

            private:

                Accessor<T> _get;
                Accessor<U> _set;

            public:
                
                constexpr PropertyBase(Accessor<T> get, Accessor<U> set): 
                    _get(get), 
                    _set(set) 
                {

                }



                /** UTILITIES **/
                /// <summary> Attaches an object instance to this property. </summary>
                template<typename V>
                PropertyBase<V, T, U> Bind(T* object)           const { return PropertyBase<V, T, U>(object, *this); }



                /** OPERATORS **/
                /// <summary> Calls the get accessor on a specific object. </summary>
                /// <returns> The output of the stored get accessor method. </returns>
                /// <param name="object"> A reference to the class instance on which to call the stored get method. </param>
                template<typename W>
                auto operator ()(W& object)                     const { return _get(object); }
                /// <summary> Calls the get accessor on a specific object. </summary>
                /// <returns> The output of the stored get accessor method. </returns>
                /// <param name="object"> A pointer to the class instance on which to call the stored get method. </param>
                template<typename W>
                auto operator ()(W* object)                     const { return _get(object); }

                /// <summary> Calls the set accessor on a specific object. </summary>
                /// <param name="object"> A reference to the class instance on which to call the stored get method. </param>
                /// <param name="values"> A list of input arguments to forward into the set method. </param>
                template<typename W, typename ... X>
                void operator ()(W& object, X ... values)       const { _set(object, values...); }
                /// <summary> Calls the set accessor on a specific object. </summary>
                /// <param name="object"> A pointer to the class instance on which to call the stored get method. </param>
                /// <param name="values"> A list of input arguments to forward into the set method. </param>
                template<typename W, typename ... X>
                void operator ()(W* object, X ... values)       const { _set(object, values...); }


                bool operator ==(const PropertyBase& other)     const { return (_get == other._get) && (_set == other._set); }
                bool operator !=(const PropertyBase& other)     const { return !operator ==(other); }
        };

        /// <summary> A structure that represents an existing object property. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> A list of input and output argument types found in the property's accessor methods. </typeparam>
        template<typename T, typename ... U>
        struct Property { };

        /// <summary> A structure that represents an object property with uniform accessor arguments. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> The output and input argument type for the property's get and set accessors, respectively. </typeparam>
        template<typename T, typename U>
        struct Property<T, U>:              public PropertyBase< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, U> > 
        { 
            using PropertyBase::PropertyBase; 
            using PropertyBase::operator =;
        };

        /// <summary> A structure that represents an object property with differing accessor arguments. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> The output argument type for the property's get accessor. </typeparam>
        /// <typeparam name="V"> The input argument type for the property's set accessor. </typeparam>
        template<typename T, typename U, typename V>
        struct Property<T, U, V>:           public PropertyBase< T, ConstMethodPointer<U, T>, MethodPointer<T&, T, V> >
        {
            using PropertyBase::PropertyBase;
            using PropertyBase::operator =;
        };



        /// <summary> A structure that represents a set of class accessor methods. </summary>
        template<typename T, typename ... U> struct Attribute { };

        /// <summary> A structure that represents a set of class accessor methods. </summary>
        /// <typeparam name="T"> The class to which the accessor methods belong. </typeparam>
        /// <typeparam name="U"> The output and input argument type for the accessor methods. </typeparam>
        template<typename T, typename U>
        struct Attribute<T, U>:             public PropertyBase< void, ConstMethodPointer<U, T>, MethodPointer<T&, T, U> > 
        {
            using PropertyBase::PropertyBase;
        };

        /// <summary> A structure that represents a set of class accessor methods. </summary>
        /// <typeparam name="T"> The class to which the accessor methods belong. </typeparam>
        /// <typeparam name="U"> The output argument type for the get accessor method. </typeparam>
        /// <typeparam name="V"> The input argument type for the set accessor method. </typeparam>
        template<typename T, typename U, typename V>
        struct Attribute<T, U, V>:          public PropertyBase< void, ConstMethodPointer<U, T>, MethodPointer<T&, T, V> >
        {
            using PropertyBase::PropertyBase;
        };

    }
}