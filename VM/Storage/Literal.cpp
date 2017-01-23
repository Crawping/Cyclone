#include "Storage/Literal.h"



namespace Cyclone
{
    namespace VM
    {

        /** LITERAL TYPE UTILITIES **/
        constexpr uint LiteralTypes::ByteSize() const
        {
            return
                (Value == Boolean)  ? 1 :
                (Value == Double)   ? 8 : 4;
        }
        string LiteralTypes::ToString() const
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
        constexpr Literal Literal::Calculate(Instructions operation, const Literal& x, const Literal& y)
        {
            return Literal
            (
                LiteralTypes::MaxPrecision(x.Type, y.Type),

                ( x.IsString() || x.IsNull() )              ? 0.0                               : 
                ( operation == Instructions::Add )          ? x.Value + y.Value                 : 
                ( operation == Instructions::And )          ? (ulong)x.Value & (ulong)y.Value   :
                ( operation == Instructions::Divide )       ? x.Value / y.Value                 :
                ( operation == Instructions::Multiply )     ? x.Value * y.Value                 :
                ( operation == Instructions::Or )           ? (ulong)x.Value | (ulong)y.Value   :
                ( operation == Instructions::Subtract )     ? x.Value - y.Value                 : 0.0
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



