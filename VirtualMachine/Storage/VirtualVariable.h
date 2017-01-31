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

        struct VariableTypes : public Enumerator
        {
            enum Types
            {
                Null        = 0,
                Address     = 10,
                Array       = 6,
                Boolean     = 1,
                Double      = 4,
                Float       = 3,
                Function    = 8,
                Integer     = 2,
                Object      = 9,
                String      = 5,
                Type        = 7,
            };



            /** CONSTRUCTORS **/
            constexpr VariableTypes(uint type)           : Enumerator((int)type) { }
            constexpr VariableTypes(enum Types t = Null) : Enumerator((int)t) { }



            /** UTILITIES **/
            VMAPI constexpr uint ByteSize()     const;
            VMAPI constexpr bool IsNumeric()    const;
            VMAPI string ToString()             const;


            constexpr static VariableTypes MaxPrecision(VariableTypes x, VariableTypes y)
            {
                return (x == Null || y == Null) ? Null : 
                    (x >= y) ? x : y;
            }
        };


        struct VirtualVariable
        {

            public:

                /** PROPERTIES **/
                constexpr uint FirstHalf()                          const { return (uint)((ulong)_value >> 32); }
                constexpr bool IsAddress()                          const { return _type == VariableTypes::Address; }
                /// <summary> Gets whether the variable is of Boolean type. </summary>
                constexpr bool IsBoolean()                          const { return _type == VariableTypes::Boolean; }
                /// <summary> Gets whether the variable is of double-precision floating point type. </summary>
                constexpr bool IsDouble()                           const { return _type == VariableTypes::Double; }
                /// <summary> Gets whether the variable is of single-precision floating point type. </summary>
                constexpr bool IsFloat()                            const { return _type == VariableTypes::Float; }
                /// <summary> Gets whether the variable represents a handle to a function. </summary>
                constexpr bool IsFunction()                         const { return _type == VariableTypes::Function; }
                /// <summary> Gets whether the variable is of single-precision signed integer type. </summary>
                constexpr bool IsInteger()                          const { return _type == VariableTypes::Integer; }
                /// <summary> Gets whether the variable is null. </summary>
                constexpr bool IsNull()                             const { return _type == VariableTypes::Null; }
                /// <summary> Gets whether the variable is of one of the numeric types. </summary>
                constexpr bool IsNumeric()                          const { return _type.IsNumeric(); }
                /// <summary> Gets whether the variable represents a handle to an instance of some class. </summary>
                constexpr bool IsObject()                           const { return _type == VariableTypes::Object; }
                /// <summary> Gets whether the variable represents a handle to a string literal. </summary>
                constexpr bool IsString()                           const { return _type == VariableTypes::String; }
                /// <summary> Gets whether the variable represents a handle to a type definition. </summary>
                constexpr bool IsType()                             const { return _type == VariableTypes::Type; }

                constexpr uint SecondHalf()                         const { return (uint)_value; }
                /// <summary> Gets the type of the variable being stored. </summary>
                constexpr VariableTypes Type()                      const { return _type; }
                /// <summary> Gets the value or handle of the variable being stored. </summary>
                constexpr double Value()                            const { return _value; }



                /** CONSTRUCTORS **/
                VMAPI constexpr VirtualVariable(VariableTypes type = VariableTypes::Null, double value = 0.0);
                VMAPI constexpr VirtualVariable(bool value);
                VMAPI constexpr VirtualVariable(double value);
                VMAPI constexpr VirtualVariable(float value);
                VMAPI constexpr VirtualVariable(int value);



                /** UTILITIES **/
                VMAPI constexpr VirtualVariable Cast(VariableTypes type)                const;
                VMAPI constexpr VirtualVariable Compare(const VirtualVariable& other)   const;
                VMAPI constexpr bool IsOfType(VariableTypes type)                       const;
                VMAPI constexpr bool IsOfType(const VirtualVariable& other)             const;
                

                VMAPI constexpr static VirtualVariable Calculate(Instructions operation, const VirtualVariable& x, const VirtualVariable& y);



                /** OPERATORS **/
                constexpr bool operator ==(const VirtualVariable& other)            const { return IsOfType(other) && (_value == other._value); }
                constexpr bool operator !=(const VirtualVariable& other)            const { return !operator ==(other); }
            
                constexpr VirtualVariable operator +(const VirtualVariable& other)  const { return Calculate(Instructions::Add, *this, other); }
                constexpr VirtualVariable operator /(const VirtualVariable& other)  const { return Calculate(Instructions::Divide, *this, other); }
                constexpr VirtualVariable operator -(const VirtualVariable& other)  const { return Calculate(Instructions::Subtract, *this, other); }
                constexpr VirtualVariable operator *(const VirtualVariable& other)  const { return Calculate(Instructions::Multiply, *this, other); }
                constexpr VirtualVariable operator |(const VirtualVariable& other)  const { return Calculate(Instructions::Or, *this, other); }

                VMAPI VirtualVariable& operator =(VirtualVariable other);
                VMAPI VirtualVariable& operator ++();
                VMAPI VirtualVariable& operator ++(int);
                VMAPI VirtualVariable& operator --();
                VMAPI VirtualVariable& operator --(int);

            private:

                /** DATA **/
                VariableTypes    _type;
                double          _value;

        };
    }
}
