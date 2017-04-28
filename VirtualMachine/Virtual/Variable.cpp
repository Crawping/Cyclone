#include "Virtual/Variable.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            /** LITERAL TYPE UTILITIES **/
            constexpr uint VariableTypes::ByteSize()        const
            {
                return
                    (Value == Boolean)  ? 1 :
                    (Value == Double)   ? 8 : 4;
            }
            constexpr bool VariableTypes::IsNumeric()       const
            {
                return 
                    (Value == Boolean)  ||
                    (Value == Double)   ||
                    (Value == Float)    ||
                    (Value == Integer);
            }
            constexpr bool VariableTypes::IsReferential()   const
            {
                return
                    (Value == Array)        ||
                    (Value == Function)     ||
                    (Value == Object)       ||
                    (Value == Reference)    ||
                    (Value == String)       ||
                    (Value == Type);
            }
            string VariableTypes::ToString()                const
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
            constexpr Variable::Variable(VariableTypes type, double value) :
                _type(type),
                _value(value)
            {

            }
            constexpr Variable::Variable(VariableTypes reference, uint type, uint id) : 
                _type(type),
                _value( ((ulong)type << 32) & id )
            {

            }
            constexpr Variable::Variable(bool value) :
                Variable(VariableTypes::Boolean, value)
            {

            }
            constexpr Variable::Variable(double value) :
                Variable(VariableTypes::Double, value)
            {

            }
            constexpr Variable::Variable(float value) :
                Variable(VariableTypes::Float, value)
            {

            }
            constexpr Variable::Variable(int value) :
                Variable(VariableTypes::Integer, value)
            {

            }



            /** UTILITIES **/
            constexpr Variable Variable::Cast(VariableTypes type)                 const
            {
                return 
                    IsOfType(type) ?
                        Variable(_type, _value) :
                    IsNumeric() && type.IsNumeric() ?
                        Variable(type, _value) : Variable();
            }
            constexpr Variable Variable::Compare(const Variable& other)    const
            {
                return _value < other._value ? -1 : _value > other._value ? 1 : 0;
            }
            constexpr bool Variable::IsOfType(VariableTypes type)                        const { return _type == type; }
            constexpr bool Variable::IsOfType(const Variable& other)              const 
            { 
                return IsObject() ?
                    other.IsObject() ? 
                        (FirstHalf() == other.FirstHalf()) : false :
                    (_type == other._type);
            }



            /** STATIC UTILITIES **/
            constexpr Variable Variable::Calculate(Instructions operation, const Variable& x, const Variable& y)
            {
                return Variable
                (
                    VariableTypes::MaxPrecision(x._type, y._type),

                    ( x.IsString() || x.IsNull() || x.IsFunction() )    ? 0.0                                   : 
                    ( y.IsString() || y.IsNull() || y.IsFunction() )    ? 0.0                                   : 
                    ( operation == Instructions::Add )                  ? x._value + y._value                   : 
                    ( operation == Instructions::And )                  ? (ulong)x._value & (ulong)y._value     :
                    ( operation == Instructions::Divide )               ? x._value / y._value                   :
                    ( operation == Instructions::Multiply )             ? x._value * y._value                   :
                    ( operation == Instructions::Or )                   ? (ulong)x._value | (ulong)y._value     :
                    ( operation == Instructions::Subtract )             ? x._value - y._value                   : 0.0
                );
            }



            /** OPERATORS **/
            Variable& Variable::operator =(Variable other)
            {
                _type = other._type;
                _value = other._value;
                return *this;
            }
            Variable& Variable::operator ++()
            {
                if (IsNumeric()) { _value++; }
                return *this;
            }
            Variable& Variable::operator ++(int)
            {
                if (IsNumeric()) { _value++; }
                return *this;
            }
            Variable& Variable::operator --()
            {
                if (IsNumeric()) { _value--; }
                return *this;
            }
            Variable& Variable::operator --(int)
            {
                if (IsNumeric()) { _value--; }
                return *this;
            }

        }
    }
}



