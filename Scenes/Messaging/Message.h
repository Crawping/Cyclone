/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Enumerator.h"
#include "SceneAPI.h"
#include "Interfaces/ISceneMessage.h"



namespace Cyclone
{
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
                Integer     = 2,
                String      = 5,
            };

            constexpr LiteralTypes(enum Types t = Nothing) : Enumerator((int)t) { }

            constexpr static LiteralTypes MaxPrecision(LiteralTypes x, LiteralTypes y)
            {
                return x >= y ? x : y;
            }
        };



        struct Literal
        {

            public:
                /** DATA **/
                LiteralTypes    Type;
                double          Value;



                /** PROPERTIES **/
                constexpr bool IsNull()                     const { return Type == LiteralTypes::Nothing; }
                constexpr bool IsBoolean()                  const { return Type == LiteralTypes::Boolean; }
                constexpr bool IsDouble()                   const { return Type == LiteralTypes::Double; }
                constexpr bool IsFloat()                    const { return Type == LiteralTypes::Float; }
                constexpr bool IsInteger()                  const { return Type == LiteralTypes::Integer; }
                constexpr bool IsString()                   const { return Type == LiteralTypes::String; }



                /** CONSTRUCTORS **/
                constexpr Literal(LiteralTypes type = LiteralTypes::Nothing, double value = 0.0) :
                    Type(type),
                    Value(value)
                {

                }
                constexpr Literal(bool value) :
                    Literal(LiteralTypes::Boolean, value)
                {

                }
                constexpr Literal(double value) :
                    Literal(LiteralTypes::Double, value)
                {

                }
                constexpr Literal(float value) :
                    Literal(LiteralTypes::Float, value)
                {

                }
                constexpr Literal(int value) :
                    Literal(LiteralTypes::Integer, value)
                {

                }
                constexpr Literal(const string& value) :
                    Literal(LiteralTypes::String)
                {

                }



                /** UTILITIES **/
                constexpr bool IsOfType(LiteralTypes type)  const { return Type == type; }
                constexpr bool IsOfType(Literal other)      const { return Type == other.Type; }



                /** OPERATORS **/
                constexpr bool operator ==(Literal other)   const
                {
                    return IsOfType(other) && (Value == other.Value);
                }
                constexpr bool operator !=(Literal other)   const { return !operator ==(other); }
            
                constexpr Literal operator +(Literal other) const { return Calculate(Instructions::Add, other); }
                constexpr Literal operator /(Literal other) const { return Calculate(Instructions::Divide, other); }
                constexpr Literal operator -(Literal other) const { return Calculate(Instructions::Subtract, other); }
                constexpr Literal operator *(Literal other) const { return Calculate(Instructions::Multiply, other); }

            private:

                constexpr Literal Calculate(Instructions operation, Literal other) const
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
