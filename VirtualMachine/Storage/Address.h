/* CHANGELOG
 * Written by Josh Grooms on 20170428
 */

#pragma once
#include "Enumerator.h"
#include "TypeDefinitions.h"
#include "VMAPI.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {
            using namespace Utilities;

            struct ReferenceTypes : public Enumerator
            {
                enum Types
                {
                    /// <summary> A blank default variable type that is invalid in nearly all operations. </summary>
                    Null = 0,
                    Array,
                    Function,
                    Number,
                    Object,
                    Reference,
                    /// <summary> An array of characters. </summary>
                    String,
                };



                /** CONSTRUCTORS **/
                constexpr ReferenceTypes(uint type)           : Enumerator((int)type) { }
                constexpr ReferenceTypes(enum Types t = Null) : Enumerator((int)t) { }



                /** UTILITIES **/
                VMAPI string ToString() const;

            };


            struct Reference
            {
                public:

                    constexpr uint Offset()           const { return (uint)_value; }
                    constexpr ubyte Slot()            const { return (ubyte)(_value >> 48); }
                    constexpr ubyte Storage()         const { return (ubyte)(_value >> 56); }
                    constexpr ReferenceTypes Type()   const { return (ubyte)(_value >> 40); }
                    constexpr ulong Value()           const { return _value; }

                    constexpr Reference(ulong value = 0):   _value(value) { }

                    constexpr operator bool()                   const
                    {
                        return (Type() != ReferenceTypes::Null) && (Offset() != 0);
                    }
                    constexpr bool operator ==(Reference other) const
                    {
                        return Type() == other.Type() && Offset() == other.Offset();
                    }
                    constexpr bool operator !=(Reference other) const { return !(operator ==(other)); }

                private:
                    ulong _value;
            };

        }
    }
}
