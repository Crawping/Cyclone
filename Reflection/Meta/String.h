/* CHANGELOG
 * Written by Josh Grooms on 20170424
 */

#pragma once
#include "TypeDefinitions.h"
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

            template<uint N, char T, char ... U> struct Characters      : public Characters<N - 1, U...> { };
            template<char T, char ... U> struct Characters<0, T, U...>  : public Character<T> { };
            template<char T, char ... U> struct Substring               : public String<U...> { };


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

                //constexpr static char LetterOf(char value)
                //{
                //    return
                //        value == 'A' ? 'A' :
                //        value == 'B' ? 'B' :
                //        value == 'C' ? 'C' :
                //        'Z';
                //}
                //constexpr static auto Cat(char value) -> decltype( Concatenate<Reflection::String(value)(0)>() )
                //{
                //    return
                //        value == 'A' ? Concatenate<'A'>() :
                //        value == 'B' ? Concatenate<'B'>() :
                //        value == 'C' ? Concatenate<'C'>() :
                //        String<T..., 'Z'>();

                //}
                //constexpr static String<T..., char> Cat(char value)               { return Concatenate<'A'>(); }
                /*template<char U>
                constexpr static String<T..., U> Cat(char U)                { return Concatenate<U>(); }*/

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


                //
                //static auto Create(const Reflection::String& value) -> decltype(Create(value))
                //{

                //}
            };

        }


        struct String
        {
            public:
                
                /** PROPERTIES **/
                constexpr uint Count()          const { return _count; }
                constexpr bool IsEmpty()        const { return Count() == 0; }
                constexpr const char* Value()   const { return _value; }



                /** CONSTRUCTOR **/
                constexpr String() :
                    _count(0),
                    _value(0)
                {

                }
                template<uint N>
                constexpr String(const char (&value)[N]) : 
                    _count(N - 1),
                    _value(value)
                {

                }


                



                /** OPERATORS **/
                operator std::string()                      const { return Value(); }
                constexpr char operator ()(uint index)      const { return (index < Count()) ? Value()[index] : '\0'; }

                bool operator ==(const std::string& other)  const { return string(*this) == other; }
                bool operator !=(const std::string& other)  const { return !(operator ==(other)); }

            private:

                uint        _count;
                const char* _value;

        };
    }
}
