/* CHANGELOG
 * Written by Josh Grooms on 20170119
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {

        /// <summary> An interface that represents a parameterized callback procedure. </summary>
        /// <typeparam name="T"> A list of types that match the prcedure's input argument signature. </typeparam>
        template<typename T, typename ... U>
        struct ICallback
        {
            /** DESTRUCTOR **/
            /// <summary> Destroys any specially allocated resources held by the callback object. </summary>
            virtual ~ICallback() { }



            /** UTILITIES **/
            /// <summary> Generates a deep copy of the callback structure on the heap. </summary>
            virtual ICallback<T, U...>* Copy()                          const = 0;
            /// <summary> Executes the callback procedure using the specified input arguments. </summary>
            /// <param name="...arguments"> An argument list that matches the signature of the callback procedure. </param>
            virtual T Invoke(U ... arguments)                           const = 0;



            /** OPERATORS **/
            /// <summary> Executes the callback procedure using the specified input arguments. </summary>
            /// <param name="...arguments"> An argument list that matches the signature of the callback procedure. </param>
            virtual T operator ()(U ... arguments)                      const { return Invoke(arguments...); }
            /// <summary> Determines whether this callback procedure is equivalent to another. </summary>
            /// <returns> A Boolean <c>true</c> if the two procedures are the same, or <c>false</c> otherwise. </returns>
            /// <param name="other"> A reference to another callback procedure. </param>
            virtual bool operator ==(const ICallback<T, U...>& other)   const = 0;
            /// <summary> Determines whether this callback procedure is not equivalent to another. </summary>
            /// <returns> A Boolean <c>true</c> if the two procedures are not the same, or <c>false</c> otherwise. </returns>
            /// <param name="other"> A reference to another callback procedure. </param>
            virtual bool operator !=(const ICallback<T, U...>& other)   const { return !(operator ==(other)); }
        };

    }
}
