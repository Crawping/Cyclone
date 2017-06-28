/* CHANGELOG
 * Written by Josh Grooms on 20170628
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {
            
            template<> struct List<>
            {
                /** PROPERTIES **/
                /// <summary> Gets the number of types present in the list. </summary>
                constexpr const static uint Count               = 0U;
                /// <summary> Gets the first type present in the list. </summary>
                using First                                     = Class<void>;
                /// <summary> Gets whether the list has any stored types. </summary>
                using IsEmpty                                   = Boolean<true>;
                /// <summary> Gets the last type present in the list. </summary>
                using Last                                      = Class<void>;
                /// <summary> Gets the total number of bytes required to store an instance of every type in the list. </summary>
                constexpr const static uint Size                = 0;
                /// <summary> A vector containing the byte sizes of each type stored in the list. </summary>
                constexpr const static uint Sizes[]             = { 0 };




                /** UTILITIES **/
                /// <summary> Appends additional types to the list. </summary>
                /// <typeparam name="U"> Any number of additional types to be added to the end of the list. </typeparam>
                template<typename ... U> using Concatenate      = List<U...>;
                /// <summary> Returns another empty list. </summary>
                using Discard                                   = List<>;
                /// <summary> Returns a void type. </summary>
                template<uint N> using Get                      = void;

                /// <summary> Determines whether a given type is equivalent to a specific type stored in the list. s</summary>
                /// <returns> A Boolean <c>true</c> if the inputted type is void, or <c>false</c> otherwise. </returns>
                /// <typeparam name="U"> A type to be tested against the one stored at the inputted index. </typeparam>
                /// <param name="index"> An unused array index. </param>
                template<typename U> constexpr static bool IsEqual(uint index) { return Meta::IsVoid<U>(); }

            };



            template<uint N, typename T> struct Sublist<N, T>:                          public List<> { };

        }
    }
}