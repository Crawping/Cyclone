#include "Storage/VirtualVariable.h"



namespace Cyclone
{
    namespace VM
    {

        /** LITERAL TYPE UTILITIES **/
        constexpr uint VariableTypes::ByteSize()     const
        {
            return
                (Value == Boolean)  ? 1 :
                (Value == Double)   ? 8 : 4;
        }
        constexpr bool VariableTypes::IsNumeric()    const
        {
            return 
                (Value == Boolean)  ||
                (Value == Double)   ||
                (Value == Float)    ||
                (Value == Integer);
        }
        string VariableTypes::ToString()             const
        {
            return
                (Value == Array)    ? "Array"       :
                (Value == Boolean)  ? "Boolean"     :
                (Value == Double)   ? "Double"      :
                (Value == Float)    ? "Float"       :
                (Value == Function) ? "Function"    :
                (Value == Integer)  ? "Integer"     :
                (Value == Null)     ? "Null"        :
                (Value == Object)   ? "Object"      :
                (Value == String)   ? "String"      : "Reference";
        }



        /** CONSTRUCTORS **/
        constexpr VirtualVariable::VirtualVariable(VariableTypes type, double value) :
            _type(type),
            _value(value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(VariableTypes reference, uint type, uint id) : 
            _type(type),
            _value( ((ulong)type << 32) & id )
        {

        }
        constexpr VirtualVariable::VirtualVariable(bool value) :
            VirtualVariable(VariableTypes::Boolean, value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(double value) :
            VirtualVariable(VariableTypes::Double, value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(float value) :
            VirtualVariable(VariableTypes::Float, value)
        {

        }
        constexpr VirtualVariable::VirtualVariable(int value) :
            VirtualVariable(VariableTypes::Integer, value)
        {

        }



        /** UTILITIES **/
        constexpr VirtualVariable VirtualVariable::Cast(VariableTypes type)                 const
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
        constexpr bool VirtualVariable::IsOfType(VariableTypes type)                        const { return _type == type; }
        constexpr bool VirtualVariable::IsOfType(const VirtualVariable& other)              const 
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
                VariableTypes::MaxPrecision(x._type, y._type),

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
            if (IsNumeric()) { _value++; }
            return *this;
        }
        VirtualVariable& VirtualVariable::operator ++(int)
        {
            if (IsNumeric()) { _value++; }
            return *this;
        }
        VirtualVariable& VirtualVariable::operator --()
        {
            if (IsNumeric()) { _value--; }
            return *this;
        }
        VirtualVariable& VirtualVariable::operator --(int)
        {
            if (IsNumeric()) { _value--; }
            return *this;
        }

    }
}



