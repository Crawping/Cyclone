/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "SceneAPI.h"
#include "Messaging/Instructions.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Scenes
    {

        struct LiteralTypes : public Enumerator
        {
            enum Types
            {
                Nothing     = 0,
                Boolean     = 1,
                Double      = 4,
                Float       = 3,
                Function    ,
                Integer     = 2,
                Object      ,
                String      = 5,
            };

            constexpr LiteralTypes(enum Types t = Nothing) : Enumerator((int)t) { }



            /** UTILITIES **/
            constexpr static LiteralTypes MaxPrecision(LiteralTypes x, LiteralTypes y)
            {
                return x >= y ? x : y;
            }

            SceneAPI constexpr string ToString() const;
        };


        struct Literal
        {

            public:
                /** DATA **/
                LiteralTypes    Type;
                double          Value;



                /** PROPERTIES **/
                constexpr bool IsNull()                             const { return Type == LiteralTypes::Nothing; }
                constexpr bool IsBoolean()                          const { return Type == LiteralTypes::Boolean; }
                constexpr bool IsDouble()                           const { return Type == LiteralTypes::Double; }
                constexpr bool IsFloat()                            const { return Type == LiteralTypes::Float; }
                constexpr bool IsInteger()                          const { return Type == LiteralTypes::Integer; }
                constexpr bool IsString()                           const { return Type == LiteralTypes::String; }



                /** CONSTRUCTORS **/
                SceneAPI constexpr Literal(LiteralTypes type = LiteralTypes::Nothing, double value = 0.0);
                SceneAPI constexpr Literal(bool value);
                SceneAPI constexpr Literal(double value);
                SceneAPI constexpr Literal(float value);
                SceneAPI constexpr Literal(int value);
                SceneAPI constexpr Literal(const string& value);



                /** UTILITIES **/
                constexpr bool IsOfType(LiteralTypes type)          const { return Type == type; }
                constexpr bool IsOfType(const Literal& other)       const { return Type == other.Type; }



                /** OPERATORS **/
                constexpr bool operator ==(const Literal& other)    const { return IsOfType(other) && (Value == other.Value); }
                constexpr bool operator !=(const Literal& other)    const { return !operator ==(other); }
            
                constexpr Literal operator +(const Literal& other)  const { return Calculate(Instructions::Add, other); }
                constexpr Literal operator /(const Literal& other)  const { return Calculate(Instructions::Divide, other); }
                constexpr Literal operator -(const Literal& other)  const { return Calculate(Instructions::Subtract, other); }
                constexpr Literal operator *(const Literal& other)  const { return Calculate(Instructions::Multiply, other); }

                SceneAPI Literal& operator =(Literal other);


            private:

                constexpr Literal Calculate(Instructions operation, const Literal& other) const
                {
                    return 
                        ( IsString() || IsNull() ) ? 
                            Literal() : 
                        ( operation == Instructions::Add ) ? 
                            Literal(LiteralTypes::MaxPrecision(Type, other.Type), Value + other.Value) : 
                        ( operation == Instructions::Divide ) ?
                            Literal(LiteralTypes::MaxPrecision(Type, other.Type), Value / other.Value) :
                        ( operation == Instructions::Multiply ) ?
                            Literal(LiteralTypes::MaxPrecision(Type, other.Type), Value * other.Value) :
                        ( operation == Instructions::Subtract ) ?
                            Literal(LiteralTypes::MaxPrecision(Type, other.Type), Value - other.Value) : 
                            Literal();
                }

        };
    }
}
