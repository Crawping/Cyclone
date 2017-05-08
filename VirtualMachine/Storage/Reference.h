/* CHANGELOG
 * Written by Josh Grooms on 20170428
 */

#pragma once
#include "Enumerator.h"
#include "TypeDefinitions.h"
#include "VMAPI.h"



namespace Cyclone
{
    namespace Virtual
    {
        using namespace Utilities;

        struct ReferenceTypes : public Enumerator
        {
            enum Types
            {
                /// <summary> A reference to nothing. </summary>
                Null = 0,
                /// <summary> A reference to an array. </summary>
                Array,
                /// <summary> A reference to a function. </summary>
                Function,
                /// <summary> A reference to a number. </summary>
                Number,
                /// <summary> A reference to a class. </summary>
                Object,
                /// <summary> A reference to another reference. </summary>
                Reference,
                /// <summary> A reference to a string of characters. </summary>
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

                constexpr ubyte Base()              const { return (ubyte)(_value >> 56); }
                constexpr ubyte Index()             const { return (ubyte)(_value >> 48); }
                constexpr uint Offset()             const { return (uint)_value; }
                constexpr ReferenceTypes Type()     const { return (ubyte)(_value >> 40); }
                constexpr ulong Value()             const { return _value; }

                VMAPI constexpr Reference(ulong value = 0);
                VMAPI constexpr Reference(ubyte storage, ubyte slot, ReferenceTypes type, uint offset);

                VMAPI constexpr operator bool()                   const;
                VMAPI constexpr bool operator ==(Reference other) const;
                VMAPI constexpr bool operator !=(Reference other) const;

            private:
                ulong _value;
        };

    }
}
