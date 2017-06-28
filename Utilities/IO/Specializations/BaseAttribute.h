/* CHANGELOG 
 * Written by Josh Grooms on 20170628
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T, typename U, typename V> struct BaseProperty;

        /// <summary> A structure that represents the get and set accessors for a data property of some class. </summary>
        /// <typeparam name="U"> The get accessor function of the property. </typeparam>
        /// <typeparam name="V"> The set accessor function of the property. </typeparam>
        /// <remarks>
        ///     Attributes are defined here as an set of unbound get and set accessor functions that mediate access to a 
        ///     particular data value. These functions are referred to as unbound because, unlike <see cref="BaseProperty"/>
        ///     instances, they are not attached to any particular instance of the class to which they belong. Consequently, 
        ///     invoking attributes directly requires a valid object reference, but attributes can be called on any number of 
        ///     class instances without having to change a stored binding.
        /// </remarks>
        template<typename T, typename U> 
        struct BaseAttribute
        {

            /** ALIASES **/
            /// <summary> The type of the output argument for the get-accessor function. </summary>
            using OutputType = typename Meta::Functor<T>::Output;
            /// <summary> The type of the input argument for the set-accessor function. </summary>
            using InputType = typename Meta::Functor<U>::Inputs::First::Type;

            private:

                Accessor<T> _get;
                Accessor<U> _set;

            public:
                
                /** CONSTRUCTOR **/
                /// <summary> Constructs a new attribute structure using the given accessor functions. </summary>
                /// <param name="get"> The attribute's get-accessor function. </param>
                /// <param name="set"> The attribute's set-accessor function. </param>
                constexpr BaseAttribute(Accessor<T> get, Accessor<U> set): 
                    _get(get), 
                    _set(set) 
                {

                }



                /** UTILITIES **/
                /// <summary> Attaches an object instance to this property. </summary>
                template<typename V>
                BaseProperty<V, T, U> Bind(T* object)           const { return BaseProperty<V, T, U>(object, *this); }



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

                /// <summary> Determines whether two attribute structures are equivalent. </summary>
                /// <returns> A Boolean <c>true</c> if the two attributes are equivalent, or <c>false</c> otherwise. </returns>
                /// <param name="other"> Another attribute structure with identical template parameters. </param>
                bool operator ==(const BaseAttribute& other)    const { return (_get == other._get) && (_set == other._set); }
                /// <summary> Determines whether two attribute structures are not equivalent. </summary>
                /// <returns> A Boolean <c>true</c> if the two attributes are not equivalent, or <c>false</c> otherwise. </returns>
                /// <param name="other"> Another attribute structure with identical template parameters. </param>
                bool operator !=(const BaseAttribute& other)    const { return !operator ==(other); }

        };
    }
}
