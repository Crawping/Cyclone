/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "VMAPI.h"
#include "Execution/Instructions.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {

        struct LiteralTypes : public Enumerator
        {
            enum Types
            {
                Nothing     = 0,
                Boolean     = 1,
                Double      = 4,
                Float       = 3,
                Function    = 7,
                Integer     = 2,
                String      = 5,
                Type        = 6,
            };

            constexpr LiteralTypes(enum Types t = Nothing) : Enumerator((int)t) { }



            /** UTILITIES **/
            constexpr static LiteralTypes MaxPrecision(LiteralTypes x, LiteralTypes y)
            {
                return x >= y ? x : y;
            }

            VMAPI string ToString() const;
        };


        struct Literal
        {

            public:
                /** DATA **/
                LiteralTypes    Type;
                double          Value;



                /** PROPERTIES **/
                constexpr uint FirstHalf()                          const { return (uint)((ulong)Value >> 32); }
                constexpr bool IsNull()                             const { return Type == LiteralTypes::Nothing; }
                constexpr bool IsBoolean()                          const { return Type == LiteralTypes::Boolean; }
                constexpr bool IsDouble()                           const { return Type == LiteralTypes::Double; }
                constexpr bool IsFloat()                            const { return Type == LiteralTypes::Float; }
                constexpr bool IsFunction()                         const { return Type == LiteralTypes::Function; }
                constexpr bool IsInteger()                          const { return Type == LiteralTypes::Integer; }
                constexpr bool IsObject()                           const { return Type == LiteralTypes::Type; }
                constexpr bool IsString()                           const { return Type == LiteralTypes::String; }
                constexpr uint SecondHalf()                         const { return (uint)Value; }



                /** CONSTRUCTORS **/
                VMAPI constexpr Literal(LiteralTypes type = LiteralTypes::Nothing, double value = 0.0);
                VMAPI constexpr Literal(bool value);
                VMAPI constexpr Literal(double value);
                VMAPI constexpr Literal(float value);
                VMAPI constexpr Literal(int value);
                VMAPI constexpr Literal(const string& value);



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

                VMAPI Literal& operator =(Literal other);

            private:

                constexpr Literal Calculate(Instructions operation, const Literal& other) const;

        };
    }
}
