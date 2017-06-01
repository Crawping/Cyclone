/* CHANGELOG
 * Written by Josh Grooms on 20170424
 */

#pragma once
#include "TypeDefinitions.h"
#include "Meta/Primitives.h"
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Reflection
    {
        using namespace Utilities;
        struct String;


        namespace Meta
        {

            template<char ... T> struct String;

            template<uint N, char T, char ... U> struct Characters          : public Characters<N - 1, U...> { };
            template<char T, char ... U> struct Characters<0, T, U...>      : public Character<T> { };
            template<char T, char ... U> struct Substring                   : public String<U...> { };


            template<char ... T>
            struct String
            {
                
                /** STATIC PROPERTIES **/
                using Count                                 = Integer32U<sizeof...(T)>;
                using First                                 = Characters<0, T...>;
                using IsEmpty                               = Boolean<false>;
                using Last                                  = Characters<sizeof...(T) - 1, T...>;



                /** STATIC UTILITIES **/
                template<char ... U> using Concatenate      = String<T..., U...>;
                using Discard                               = Substring<T...>;
                template<uint N> using Get                  = Characters<N, T...>;



                /** RUNTIME OPERATORS **/

                operator std::string()                                      const { return std::string({ T... }); }

                bool operator ==(const string& other)                       const { return (operator std::string() == other); }
                bool operator !=(const string& other)                       const { return !(operator ==(other)); }

                template<char ... U>
                constexpr bool operator ==(const String<U...>& other)       const { return IsEqual<First, String<U...>::First>(); }

                template<char ... U>
                constexpr bool operator !=(const String<U...>& other)       const { return !(operator ==(other)); }

                constexpr char operator ()(uint index)                      const { return Reflection::String({ T..., '\0' })(index); }

                template<char U>
                constexpr static String<T..., U> Cat(Character<U> value)    { return Concatenate<U>(); }

            };

            template<> struct String<>
            {
                using Count                                 = Integer32U<0>;
                using First                                 = Character<'\0'>;
                using IsEmpty                               = Boolean<true>;
                using Last                                  = Character<'\0'>;

                template<char ... U> using Concatenate      = String<U...>;
                using Discard                               = Substring<'\0'>;
                template<uint N> using Get                  = First;

                operator std::string()                                      const { return std::string(); }
                
                template<char ... U>
                constexpr bool operator ==(const String<U...>& other)       const { return IsEqual<First, String<U...>>::First(); }

                template <char ... U>
                constexpr bool operator !=(const String<U...>& other)       const { return !(operator ==(other)); }

                constexpr char operator ()(uint index)                      const { return First(); }

            };

        }
    }
}
