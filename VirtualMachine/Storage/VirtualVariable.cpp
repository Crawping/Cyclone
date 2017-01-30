#include "Storage/VirtualVariable.h"



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
        constexpr VirtualVariable::VirtualVariable(LiteralTypes type, double value) :
            _type(type),
            _value(value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(bool value) :
            VirtualVariable(LiteralTypes::Boolean, value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(double value) :
            VirtualVariable(LiteralTypes::Double, value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(float value) :
            VirtualVariable(LiteralTypes::Float, value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(int value) :
            VirtualVariable(LiteralTypes::Integer, value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(const string& value) :
            VirtualVariable(LiteralTypes::String)
        {

        }



        /** UTILITIES **/
        constexpr VirtualVariable VirtualVariable::Cast(LiteralTypes type)          const
        {
            return 
                IsOfType(type) ?
                    VirtualVariable(_type, _value) :
                IsNumeric() && type.IsNumeric() ?
                    VirtualVariable(type, _value) : VirtualVariable();
        }
        constexpr VirtualVariable VirtualVariable::Compare(const VirtualVariable& other)    const
        {
            return _value < other._value ? -1 : _value > other._value ? 1 : 0;
        }
        constexpr bool VirtualVariable::IsOfType(LiteralTypes type)         const { return _type == type; }
        constexpr bool VirtualVariable::IsOfType(const VirtualVariable& other)      const 
        { 
            return IsObject() ?
                other.IsObject() ? 
                    (FirstHalf() == other.FirstHalf()) : false :
                (_type == other._type);
        }



        /** STATIC UTILITIES **/
        constexpr VirtualVariable VirtualVariable::Calculate(Instructions operation, const VirtualVariable& x, const VirtualVariable& y)
        {
            return VirtualVariable
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
        VirtualVariable& VirtualVariable::operator =(VirtualVariable other)
        {
            _type = other._type;
            _value = other._value;
            return *this;
        }
        VirtualVariable& VirtualVariable::operator ++()
        {
            if (IsNull()) { return *this; }
            _value++;
            return *this;
        }
        VirtualVariable& VirtualVariable::operator ++(int)
        {
            if (IsNull()) { return *this; }
            _value++;
            return *this;
        }
        VirtualVariable& VirtualVariable::operator --()
        {
            if (IsNull()) { return *this; }
            _value--;
            return *this;
        }
        VirtualVariable& VirtualVariable::operator --(int)
        {
            if (IsNull()) { return *this; }
            _value--;
            return *this;
        }

    }
}



