/* CHANGELOG
 * Written by Josh Grooms on 20170628 
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, typename U> struct BaseAttribute;

        /// <summary> A structure that represents an object data member accessible via get and set functions. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> A list of class method pointers representing the accessor functions of the property. </typeparam>
        //template<typename T, typename ... U> struct BaseProperty { };

        /// <summary> A structure that represents an object data member accessible via get and set functions. </summary>
        /// <typeparam name="T"> The class to which the property belongs. </typeparam>
        /// <typeparam name="U"> The get accessor function of the property. </typeparam>
        /// <typeparam name="V"> The set accessor function of the property. </typeparam>
        template<typename T, typename U, typename V> 
        struct BaseProperty
        {
            using OutputType = typename Meta::Functor<U>::Output;
            using InputType = typename Meta::Functor<V>::Inputs::First::Type;

            private:

                BaseAttribute<U, V>         _accessors;
                T*                          _object;

            public:
                
                BaseProperty(T* object, U get, V set):
                    _accessors(get, set),
                    _object(object)
                {

                }
                BaseProperty(T* object, BaseAttribute<U, V> accessors):
                    _accessors(accessors),
                    _object(object)
                {

                }



                /** UTILITIES **/
                BaseAttribute<U, V> Unbind()                    const { return _accessors; }


                template<typename ... W>
                auto operator ()(W ... arguments)               const { return _accessors(_object, arguments...); }


                /// <summary> Implicitly converts the property to its underlying type by calling the get accessor. </summary>
                /// <returns> The result of calling the get accessor function. </returns>
                operator OutputType()                           const { return _accessors(_object); }
                /// <summary> Calls the property's set accessor function with the inputted value. </summary>
                /// <param name="value"> The value to be forwarded to the property's set accessor. </param>
                BaseProperty& operator =(InputType value)       { _accessors(_object, value); return *this; }
                /// <summary> Calls the property's set accessor with the output of another property's get accessor. </summary>
                /// <typeparam name="W"> The class to which the other property belongs. </typeparam>
                /// <typeparam name="X"> A list of accessor methods associated with the other property. </typeparam>
                /// <param name="value"> Another object property with a compatible output type. </param>
                /// <remarks>
                ///     The inputted property in this method must contain a get accessor whose output type can be used in a call 
                ///     to this property's set accessor. Compilation errors will result when incompatible types are detected.
                /// </remarks>
                template<typename W, typename ... X>
                BaseProperty& operator =(BaseProperty<W, X...> value)
                {
                    using Other = BaseProperty<W, X...>;
                    static_assert(Meta::IsA< Other::OutputType, InputType >(),
                        "Types must agree.");

                    _accessors(_object, value());
                    return *this;
                }


                bool operator ==(const BaseProperty& other)     const 
                {
                    return (_object == other._object) && (_accessors == other._accessors);
                }
                bool operator !=(const BaseProperty& other)     const { return !operator ==(other); }
                bool operator ==(OutputType value)              const { return (_accessors(_object) == value); }
                bool operator !=(OutputType value)              const { return !operator ==(value); }

        };
    }
}
