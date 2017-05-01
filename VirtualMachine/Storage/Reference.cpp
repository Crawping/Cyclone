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



            /** CONSTRUCTOR **/
            constexpr Reference::Reference(ubyte storage, ubyte slot, ReferenceTypes type, uint offset):
                _value( ((ulong)storage << 56) | ((ulong)slot << 48) | ((ulong)type << 40) | (ulong)offset )
            {

            }



            /** OPERATORS **/
            constexpr Reference::operator bool()                    const
            {
                return (Type() != ReferenceTypes::Null) && (Offset() != 0);
            }
            constexpr bool Reference::operator ==(Reference other)  const
            {
                return Type() == other.Type() && Offset() == other.Offset();
            }
            constexpr bool Reference::operator !=(Reference other)  const { return !(operator ==(other)); }

        }
    }
}