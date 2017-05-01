#include "Storage/Address.h"



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
        }
    }
}