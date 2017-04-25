/* CHANGELOG
 * Written by Josh Grooms on 20170424
 */

#pragma once
#include "TypeDefinitions.h"
#include "Meta/Primitives.h"



namespace Cyclone
{
    namespace Reflection
    {
        using namespace Utilities;

        namespace Meta
        {

            template<uint N, char T, char ... U>
            struct CharacterList                : public CharacterList<N - 1, U...> { };

            template<char T, char ... U>
            struct CharacterList<0, T, U...>    : public Character<T> { };

            template<char ... T>
            struct String
            {
                template<typename ... U>
                using Concatenate   = String<T..., U...>;
                using Count         = Integer32U<sizeof...(T)>;

                template<uint N> using Get = CharacterList<N, T...>;
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
                operator std::string()                  const { return Value(); }
                constexpr char operator ()(uint index)  const { return (index < Count()) ? Value()[index] : '\0'; }

            private:
                uint        _count;
                const char* _value;

        };
    }
}
