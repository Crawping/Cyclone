#include "Storage/Literal.h"



namespace Cyclone
{
    namespace VM
    {

        /** LITERAL TYPE UTILITIES **/
        constexpr uint LiteralTypes::ByteSize()     const
        {
            return
                (Value == Boolean)  ? 1 :
                (Value == Double)   ? 8 : 4;
        }
        constexpr bool LiteralTypes::IsNumeric()    const
        {
            return (Value != Null) && (Value != Function) && (Value != String) && (Value != Type);
        }
        string LiteralTypes::ToString()             const
        {
            return
                (Value == Boolean)  ? "Boolean" :
                (Value == Double)   ? "Double"  :
                (Value == Float)    ? "Float"   :
                (Value == Integer)  ? "Integer" :
                (Value == String)   ? "String"  : "Void";
        }



        /** CONSTRUCTORS **/
        constexpr Literal::Literal(LiteralTypes type, double value) :
            Type(type),
            Value(value)
        {

        }
        constexpr Literal::Literal(bool value) :
            Literal(LiteralTypes::Boolean, value)
        {

        }
        constexpr Literal::Literal(double value) :
            Literal(LiteralTypes::Double, value)
        {

        }
        constexpr Literal::Literal(float value) :
            Literal(LiteralTypes::Float, value)
        {

        }
        constexpr Literal::Literal(int value) :
            Literal(LiteralTypes::Integer, value)
        {

        }
        constexpr Literal::Literal(const string& value) :
            Literal(LiteralTypes::String)
        {

        }



        /** UTILITIES **/
        constexpr Literal Literal::Cast(LiteralTypes type)          const
        {
            return 
                IsOfType(type) ?
                    Literal(Type, Value) :
                IsNumeric() && type.IsNumeric() ?
                    Literal(type, Value) : Literal();
        }
        constexpr Literal Literal::Compare(const Literal& other)    const
        {
            return Value < other.Value ? -1 : Value > other.Value ? 1 : 0;
        }
        constexpr bool Literal::IsOfType(LiteralTypes type)         const { return Type == type; }
        constexpr bool Literal::IsOfType(const Literal& other)      const 
        { 
            return IsObject() ?
                other.IsObject() ? 
                    (FirstHalf() == other.FirstHalf()) : false :
                (Type == other.Type);
        }



        /** STATIC UTILITIES **/
        constexpr Literal Literal::Calculate(Instructions operation, const Literal& x, const Literal& y)
        {
            return Literal
            (
                LiteralTypes::MaxPrecision(x.Type, y.Type),

                ( x.IsString() || x.IsNull() || x.IsFunction() )    ? 0.0                               : 
                ( y.IsString() || y.IsNull() || y.IsFunction() )    ? 0.0                               : 
                ( operation == Instructions::Add )                  ? x.Value + y.Value                 : 
                ( operation == Instructions::And )                  ? (ulong)x.Value & (ulong)y.Value   :
                ( operation == Instructions::Divide )               ? x.Value / y.Value                 :
                ( operation == Instructions::Multiply )             ? x.Value * y.Value                 :
                ( operation == Instructions::Or )                   ? (ulong)x.Value | (ulong)y.Value   :
                ( operation == Instructions::Subtract )             ? x.Value - y.Value                 : 0.0
            );
        }



        /** OPERATORS **/
        Literal& Literal::operator =(Literal other)
        {
            Type = other.Type;
            Value = other.Value;
            return *this;
        }

    }
}



