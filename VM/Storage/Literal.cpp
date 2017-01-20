#include "Storage/Literal.h"



namespace Cyclone
{
    namespace VM
    {

        /** LITERAL TYPE UTILITIES **/
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
        constexpr Literal::Literal(LiteralTypes type = LiteralTypes::Nothing, double value = 0.0) :
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
        constexpr Literal Literal::Calculate(Instructions operation, const Literal& other) const
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



        /** OPERATORS **/
        Literal& Literal::operator =(Literal other)
        {
            Type = other.Type;
            Value = other.Value;
            return *this;
        }

    }
}



