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
            return (Value != Null) && (Value != Function) && (Value != Object) && (Value != String) && (Value != Type);
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
            _type(type),
            _value(value)
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
                    Literal(_type, _value) :
                IsNumeric() && type.IsNumeric() ?
                    Literal(type, _value) : Literal();
        }
        constexpr Literal Literal::Compare(const Literal& other)    const
        {
            return _value < other._value ? -1 : _value > other._value ? 1 : 0;
        }
        constexpr bool Literal::IsOfType(LiteralTypes type)         const { return _type == type; }
        constexpr bool Literal::IsOfType(const Literal& other)      const 
        { 
            return IsObject() ?
                other.IsObject() ? 
                    (FirstHalf() == other.FirstHalf()) : false :
                (_type == other._type);
        }



        /** STATIC UTILITIES **/
        constexpr Literal Literal::Calculate(Instructions operation, const Literal& x, const Literal& y)
        {
            return Literal
            (
                LiteralTypes::MaxPrecision(x._type, y._type),

                ( x.IsString() || x.IsNull() || x.IsFunction() )    ? 0.0                               : 
                ( y.IsString() || y.IsNull() || y.IsFunction() )    ? 0.0                               : 
                ( operation == Instructions::Add )                  ? x._value + y._value                 : 
                ( operation == Instructions::And )                  ? (ulong)x._value & (ulong)y._value   :
                ( operation == Instructions::Divide )               ? x._value / y._value                 :
                ( operation == Instructions::Multiply )             ? x._value * y._value                 :
                ( operation == Instructions::Or )                   ? (ulong)x._value | (ulong)y._value   :
                ( operation == Instructions::Subtract )             ? x._value - y._value                 : 0.0
            );
        }



        /** OPERATORS **/
        Literal& Literal::operator =(Literal other)
        {
            _type = other._type;
            _value = other._value;
            return *this;
        }
        Literal& Literal::operator ++()
        {
            if (IsNull()) { return *this; }
            _value++;
            return *this;
        }
        Literal& Literal::operator ++(int)
        {
            if (IsNull()) { return *this; }
            _value++;
            return *this;
        }
        Literal& Literal::operator --()
        {
            if (IsNull()) { return *this; }
            _value--;
            return *this;
        }
        Literal& Literal::operator --(int)
        {
            if (IsNull()) { return *this; }
            _value--;
            return *this;
        }

    }
}



