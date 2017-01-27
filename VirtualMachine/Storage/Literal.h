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
                Null        = 0,
                Address     = 9,
                Boolean     = 1,
                Double      = 4,
                Float       = 3,
                Function    = 7,
                Integer     = 2,
                Object      = 8,
                String      = 5,
                Type        = 6,
            };



            /** CONSTRUCTORS **/
            constexpr LiteralTypes(uint type)           : Enumerator((int)type) { }
            constexpr LiteralTypes(enum Types t = Null) : Enumerator((int)t) { }



            /** UTILITIES **/
            VMAPI constexpr uint ByteSize()     const;
            VMAPI constexpr bool IsNumeric()    const;
            VMAPI string ToString()             const;


            constexpr static LiteralTypes MaxPrecision(LiteralTypes x, LiteralTypes y)
            {
                return (x == Null || y == Null) ? Null : 
                    (x >= y) ? x : y;
            }
        };


        struct Literal
        {

            /** DATA **/
            LiteralTypes    Type;
            double          Value;



            /** PROPERTIES **/
            constexpr uint FirstHalf()                          const { return (uint)((ulong)Value >> 32); }
            constexpr bool IsAddress()                          const { return Type == LiteralTypes::Address; }
            constexpr bool IsBoolean()                          const { return Type == LiteralTypes::Boolean; }
            constexpr bool IsDouble()                           const { return Type == LiteralTypes::Double; }
            constexpr bool IsFloat()                            const { return Type == LiteralTypes::Float; }
            constexpr bool IsFunction()                         const { return Type == LiteralTypes::Function; }
            constexpr bool IsInteger()                          const { return Type == LiteralTypes::Integer; }
            constexpr bool IsNull()                             const { return Type == LiteralTypes::Null; }
            constexpr bool IsNumeric()                          const { return Type.IsNumeric(); }
            constexpr bool IsObject()                           const { return Type == LiteralTypes::Object; }
            constexpr bool IsString()                           const { return Type == LiteralTypes::String; }
            constexpr bool IsType()                             const { return Type == LiteralTypes::Type; }
            constexpr uint SecondHalf()                         const { return (uint)Value; }



            /** CONSTRUCTORS **/
            VMAPI constexpr Literal(LiteralTypes type = LiteralTypes::Null, double value = 0.0);
            VMAPI constexpr Literal(bool value);
            VMAPI constexpr Literal(double value);
            VMAPI constexpr Literal(float value);
            VMAPI constexpr Literal(int value);
            VMAPI constexpr Literal(const string& value);



            /** UTILITIES **/
            VMAPI constexpr Literal Cast(LiteralTypes type)         const;
            VMAPI constexpr Literal Compare(const Literal& other)   const;
            VMAPI constexpr bool IsOfType(LiteralTypes type)        const;
            VMAPI constexpr bool IsOfType(const Literal& other)     const;
                

            VMAPI constexpr static Literal Calculate(Instructions operation, const Literal& x, const Literal& y);



            /** OPERATORS **/
            constexpr bool operator ==(const Literal& other)    const { return IsOfType(other) && (Value == other.Value); }
            constexpr bool operator !=(const Literal& other)    const { return !operator ==(other); }
            
            constexpr Literal operator +(const Literal& other)  const { return Calculate(Instructions::Add, *this, other); }
            constexpr Literal operator /(const Literal& other)  const { return Calculate(Instructions::Divide, *this, other); }
            constexpr Literal operator -(const Literal& other)  const { return Calculate(Instructions::Subtract, *this, other); }
            constexpr Literal operator *(const Literal& other)  const { return Calculate(Instructions::Multiply, *this, other); }
            constexpr Literal operator |(const Literal& other)  const { return Calculate(Instructions::Or, *this, other); }

            VMAPI Literal& operator =(Literal other);

        };
    }
}
