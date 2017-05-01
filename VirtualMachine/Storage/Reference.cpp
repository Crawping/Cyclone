#include "Storage/Reference.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {
            string ReferenceTypes::ToString() const
            {
                return
                    (Value == Array)    ? "Array"       :
                    (Value == Function) ? "Function"    :
                    (Value == Null)     ? "Null"        :
                    (Value == Number)   ? "Number"      :
                    (Value == Object)   ? "Object"      :
                    (Value == String)   ? "String"      : "Reference";
            }



            constexpr Reference::Reference(ubyte storage, ubyte slot, ReferenceTypes type, uint offset):
                _value( ((ulong)storage << 56) | ((ulong)slot << 48) | ((ulong)type << 40) | (ulong)offset )
            {

            }
        }
    }
}