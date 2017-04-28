/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "Enumerator.h"



namespace Cyclone
{
    namespace VM
    {
        using namespace Utilities;

        namespace Virtual
        {

            struct PrimitiveTypes : public Enumerator
            {
                enum Types : ubyte
                {
                    Null        = 0,
                    Array       = 1,
                    Boolean     = 2,
                    Double      = 3,
                    Float       = 4,
                    Function    = 5,
                    Integer     = 6,
                    Object      = 7,
                    Reference   = 8,
                    String      = 9,
                };
            };


            struct VariableType
            {
                PrimitiveTypes  Primary;
                PrimitiveTypes  Secondary;
                
            };


            class Variable
            {
                public:

                    Variable operator +(const Variable& other)  const; // { return Calculate(Instructions::Add, *this, other); }
                    Variable operator /(const Variable& other)  const; // { return Calculate(Instructions::Divide, *this, other); }
                    Variable operator -(const Variable& other)  const; // { return Calculate(Instructions::Subtract, *this, other); }
                    Variable operator *(const Variable& other)  const; // { return Calculate(Instructions::Multiply, *this, other); }
                    
                    Variable operator |(const Variable& other)  const; // { return Calculate(Instructions::Or, *this, other); }
                    Variable operator &(const Variable& other)  const;
                    Variable operator ~()                       const;


                    VMAPI Variable& operator =(const Variable& other);
                    VMAPI Variable& operator ++();
                    VMAPI Variable& operator ++(int);
                    VMAPI Variable& operator --();
                    VMAPI Variable& operator --(int);

                private:



            };



        }
    }
}
