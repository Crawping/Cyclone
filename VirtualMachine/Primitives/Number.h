/* CHANGELOG
 * Written by Josh Grooms on 20170429
 */

#pragma once
#include "Primitives/NumericTypes.h"
#include "Storage/Reference.h"



namespace Cyclone
{
    namespace Virtual
    {
        class Number
        {
            public:

                /** PROPERTIES **/
                constexpr NumericTypes Type()       const { return _type; }
                constexpr double Value()            const { return _value; }



                /** CONSTRUCTORS **/
                VMAPI constexpr Number(Reference location);
                VMAPI constexpr Number(NumericTypes type = NumericTypes::Integer32, double value = 0.0);

                template<typename T>
                constexpr Number(T value) :
                    _type(NumericTypes::TypeOf(value)),
                    _value(value)
                {

                }



                /** UTILITIES **/
                VMAPI constexpr operator bool()                     const;
                VMAPI constexpr Number Cast(NumericTypes type)      const;
                VMAPI constexpr Number Compare(Number other)        const;



                /** OPERATORS **/
                VMAPI constexpr bool operator ==(Number other)      const;
                VMAPI constexpr bool operator !=(Number other)      const;

                VMAPI constexpr Number operator +()                 const;
                VMAPI constexpr Number operator -()                 const;
                VMAPI constexpr Number operator !()                 const;
                VMAPI constexpr Number operator ~()                 const;

                VMAPI constexpr Number operator +(Number other)     const;
                VMAPI constexpr Number operator /(Number other)     const;
                VMAPI constexpr Number operator -(Number other)     const;
                VMAPI constexpr Number operator *(Number other)     const;
                VMAPI constexpr Number operator |(Number other)     const;

                VMAPI constexpr Number operator &(Number other)     const;
                VMAPI constexpr Number operator ^(Number other)     const;

                VMAPI Number& operator ++();
                VMAPI Number& operator ++(int);
                VMAPI Number& operator --();
                VMAPI Number& operator --(int);

            private:
                
                NumericTypes    _type;
                double          _value;
        };

    }
}
