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

            public:

                /** PROPERTIES **/
                constexpr uint FirstHalf()                          const { return (uint)((ulong)_value >> 32); }
                constexpr bool IsAddress()                          const { return _type == LiteralTypes::Address; }
                constexpr bool IsBoolean()                          const { return _type == LiteralTypes::Boolean; }
                constexpr bool IsDouble()                           const { return _type == LiteralTypes::Double; }
                constexpr bool IsFloat()                            const { return _type == LiteralTypes::Float; }
                constexpr bool IsFunction()                         const { return _type == LiteralTypes::Function; }
                constexpr bool IsInteger()                          const { return _type == LiteralTypes::Integer; }
                constexpr bool IsNull()                             const { return _type == LiteralTypes::Null; }
                constexpr bool IsNumeric()                          const { return _type.IsNumeric(); }
                constexpr bool IsObject()                           const { return _type == LiteralTypes::Object; }
                constexpr bool IsString()                           const { return _type == LiteralTypes::String; }
                constexpr bool IsType()                             const { return _type == LiteralTypes::Type; }
                constexpr uint SecondHalf()                         const { return (uint)_value; }
                constexpr LiteralTypes Type()                       const { return _type; }
                constexpr double Value()                            const { return _value; }



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
                constexpr bool operator ==(const Literal& other)    const { return IsOfType(other) && (_value == other._value); }
                constexpr bool operator !=(const Literal& other)    const { return !operator ==(other); }
            
                constexpr Literal operator +(const Literal& other)  const { return Calculate(Instructions::Add, *this, other); }
                constexpr Literal operator /(const Literal& other)  const { return Calculate(Instructions::Divide, *this, other); }
                constexpr Literal operator -(const Literal& other)  const { return Calculate(Instructions::Subtract, *this, other); }
                constexpr Literal operator *(const Literal& other)  const { return Calculate(Instructions::Multiply, *this, other); }
                constexpr Literal operator |(const Literal& other)  const { return Calculate(Instructions::Or, *this, other); }

                VMAPI Literal& operator =(Literal other);
                VMAPI Literal& operator ++();
                VMAPI Literal& operator ++(int);
                VMAPI Literal& operator --();
                VMAPI Literal& operator --(int);

            private:

                /** DATA **/
                LiteralTypes    _type;
                double          _value;

        };
    }
}
