#include "Primitives/Number.h"



namespace Cyclone
{
    namespace Virtual
    {

        /** CONSTRUCTORS **/
        constexpr Number::Number(Reference location) :
            _type(NumericTypes::Reference),
            _value(location.Value())
        {

        }
        constexpr Number::Number(NumericTypes type, double value) :
            _type(type),
            _value(value)
        {

        }



        /** UTILITIES **/
        constexpr Number Number::Cast(NumericTypes type)        const
        {
            return Number( Type() == NumericTypes::Null ? NumericTypes::Null : type, Value() );
        }
        constexpr Number Number::Compare(Number other)          const
        {
            return (Value() < other.Value())    ? -1 :
                (Value() > other.Value())       ?  1 : 0;
        }



        /** OPERATORS **/
        constexpr Number::operator bool()                       const
        {
            return (Type() != NumericTypes::Null) && (_value != 0.0);
        }
        constexpr bool Number::operator ==(Number other)        const
        {
            return
                (Type() == NumericTypes::Null)              ?
                    (other.Type() == NumericTypes::Null)    ? true : false :
                    (other.Type() == NumericTypes::Null)    ? false : (Value() == other.Value());
        }
        constexpr bool Number::operator !=(Number other)        const { return !(operator ==(other)); }

        constexpr Number Number::operator +()                   const { return *this; }
        constexpr Number Number::operator -()                   const { return Number(Type(), -Value()); }
        constexpr Number Number::operator !()                   const { return Number(Type(), !Value()); }
        constexpr Number Number::operator ~()                   const { return Number(Type(), ~(ulong)Value()); }

        constexpr Number Number::operator +(Number other)       const
        {
            return Number
            (
                NumericTypes::Max(Type(), other.Type()),
                Value() + other.Value()
            );
        }
        constexpr Number Number::operator /(Number other)       const
        {
            return Number
            (
                NumericTypes::Max(Type(), other.Type()),
                Value() / other.Value()
            );
        }
        constexpr Number Number::operator -(Number other)       const
        {
            return Number
            (
                NumericTypes::Max(Type(), other.Type()),
                Value() - other.Value()
            );
        }
        constexpr Number Number::operator *(Number other)       const
        {
            return Number
            (
                NumericTypes::Max(Type(), other.Type()),
                Value() * other.Value()
            );
        }
        constexpr Number Number::operator |(Number other)       const
        {
            return Number
            (
                NumericTypes::Max(Type(), other.Type()),
                (ulong)Value() | (ulong)other.Value()
            );
        }
        constexpr Number Number::operator &(Number other)       const
        {
            return Number
            (
                NumericTypes::Max(Type(), other.Type()),
                (ulong)Value() & (ulong)other.Value()
            );
        }
        constexpr Number Number::operator ^(Number other)       const
        {
            return Number
            (
                NumericTypes::Max(Type(), other.Type()),
                (ulong)Value() ^ (ulong)other.Value()
            );
        }

        Number& Number::operator ++()
        {
            _value += 1;
            return *this;
        }
        Number& Number::operator ++(int)
        {
            _value += 1;
            return *this;
        }
        Number& Number::operator --()
        {
            _value -= 1;
            return *this;
        }
        Number& Number::operator --(int)
        {
            _value -= 1;
            return *this;
        }

    }
}
