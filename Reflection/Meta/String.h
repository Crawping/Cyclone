/* CHANGELOG
 * Written by Josh Grooms on 20170424
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Reflection
    {
        using namespace Utilities;



        template<char ... T>
        struct CharacterList
        {
            using Count = sizeof...(T);
        };



        struct String
        {
            public:
                
                /** PROPERTIES **/
                constexpr uint Count()          const { return _count; }
                constexpr bool IsEmpty()        const { return Count() == 0; }
                constexpr const char* Value()   const { return _value; }



                /** CONSTRUCTOR **/
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
