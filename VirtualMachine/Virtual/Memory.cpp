#include "Primitives/Array.h"
#include "Virtual/Memory.h"
#include "Virtual/Class.h"
#include "Virtual/Function.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            /** CONSTRUCTOR **/
            Memory::Memory()
            {
                Arrays.Insert(0, { });
                Classes.Insert(0, { });
                Functions.Insert(0, { });
                Numbers.Insert(0, { });
                References.Insert(0, { });
                Strings.Insert(0, "");
            }



            /** UTILITIES **/
            template<> Array& Memory::Access<Array>(Reference location)
            {
                bool isValid = (location.Type() == ReferenceTypes::Array) &&
                    Arrays.Contains(location.Offset());
                return Arrays[ isValid ? location.Offset() : 0 ];
            }
            template<> Function& Memory::Access<Function>(Reference location)
            {
                bool isValid = (location.Type() == ReferenceTypes::Function) &&
                    Functions.Contains(location.Offset());
                return Functions[ isValid ? location.Offset() : 0 ];
            }
            template<> Number& Memory::Access<Number>(Reference location)
            {
                bool isValid = (location.Type() == ReferenceTypes::Number) &&
                    Numbers.Contains(location.Offset());
                return Numbers[isValid ? location.Offset() : 0];
            }
            template<> Class& Memory::Access<Class>(Reference location)
            {
                bool isValid = (location.Type() == ReferenceTypes::Object) &&
                    Classes.Contains(location.Offset());
                return Classes[ isValid ? location.Offset() : 0 ];
            }
            template<> Reference& Memory::Access<Reference>(Reference location)
            {
                bool isValid = (location.Type() == ReferenceTypes::Reference) &&
                    References.Contains(location.Offset());
                return References[ isValid ? location.Offset() : 0 ];
            }
            template<> String& Memory::Access<String>(Reference location)
            {
                bool isValid = (location.Type() == ReferenceTypes::String) &&
                    Strings.Contains(location.Offset());
                return Strings[ isValid ? location.Offset() : 0 ];
            }

            template<> void Memory::Insert<Array>(Reference location, const Array& value)
            {
                if (location.Type() == ReferenceTypes::Array)
                    Arrays.Insert(location.Offset(), value);
            }
            template<> void Memory::Insert<Class>(Reference location, const Class& value)
            {
                if (location.Type() == ReferenceTypes::Object)
                    Classes.Insert(location.Offset(), value);
            }
            template<> void Memory::Insert<Function>(Reference location, const Function& value)
            {
                if (location.Type() == ReferenceTypes::Function)
                    Functions.Insert(location.Offset(), value);
            }
            template<> void Memory::Insert<Number>(Reference location, const Number& value)
            {
                if (location.Type() == ReferenceTypes::Number)
                    Numbers.Insert(location.Offset(), value);
            }
            template<> void Memory::Insert<Reference>(Reference location, const Reference& value)
            {
                if (location.Type() == ReferenceTypes::Reference)
                    References.Insert(location.Offset(), value);
            }
            template<> void Memory::Insert<String>(Reference location, const String& value)
            {
                if (location.Type() == ReferenceTypes::String)
                    Strings.Insert(location.Offset(), value);
            }

            void Memory::Delete(Reference location)
            {
                uint offset = location.Offset();
                switch (location.Type())
                {
                    case ReferenceTypes::Array:         Arrays.Remove(offset);      break;
                    case ReferenceTypes::Object:        Classes.Remove(offset);     break;
                    case ReferenceTypes::Function:      Functions.Remove(offset);   break;
                    case ReferenceTypes::Number:        Numbers.Remove(offset);     break;
                    case ReferenceTypes::Reference:     References.Remove(offset);  break;
                    case ReferenceTypes::String:        Strings.Remove(offset);     break;
                    default:                            break;
                }
            }

        }
    }
}
