/* CHANGELOG
 * Written by Josh Grooms on 20170428
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {
            using namespace Utilities;

            struct Address
            {
                public:

                    uint Base()     const { return (uint)(_value >> 32); }
                    uint Offset()   const { return (uint)_value; }
                    ulong Value()   const { return _value; }

                    Address(ulong value) : _value(value) { }

                private:
                    ulong _value;
            };

            struct Register: public Address { };

        }
    }
}
