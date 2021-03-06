#include "Storage/StackFrame.h"
#include "Primitives/Array.h"


namespace Cyclone
{
    namespace Virtual
    {

        /** PROPERTIES **/
        StackFrame& StackFrame::Inputs(const Vector<Reference, 128>& value)
        {
            Input = Vector<Reference, 128>(value, 64, 64);
            return *this;
        }
        StackFrame& StackFrame::Outputs(const Vector<Reference, 128>& value)
        {

            return *this;
        }



        /** UTILITIES **/
        template<> Array& StackFrame::Access<Array>(Reference location)
        {
            bool isValid = (location.Type() == ReferenceTypes::Array) && (location.Offset() < 256);
            return *Arrays( isValid ? location.Offset() : 0 );
        }
        template<> Class& StackFrame::Access<Class>(Reference location)
        {
            bool isValid = (location.Type() == ReferenceTypes::Object) && (location.Offset() < 256);
            return *Classes(isValid ? location.Offset() : 0);
        }
        template<> Function& StackFrame::Access<Function>(Reference location)
        {
            bool isValid = (location.Type() == ReferenceTypes::Function) && (location.Offset() < 256);
            return *Functions(isValid ? location.Offset() : 0);
        }
        template<> Number& StackFrame::Access<Number>(Reference location)
        {
            bool isValid = (location.Type() == ReferenceTypes::Number) && (location.Offset() < 256);
            return Numbers(isValid ? location.Offset() : 0);
        }
        template<> Reference& StackFrame::Access<Reference>(Reference location)
        {
            bool isValid = (location.Type() == ReferenceTypes::Reference) && (location.Offset() < 256);
            uint offset = isValid ? location.Offset() : 0;
            switch (location.Index())
            {
                case 0:     return Input(offset);
                case 1:     return Local(offset);
                default:    return Output(offset);
            }
        }
        template<> String& StackFrame::Access<String>(Reference location)
        {
            bool isValid = (location.Type() == ReferenceTypes::String) && (location.Offset() < 256);
            return *Strings(isValid ? location.Offset() : 0);
        }

        template<> void StackFrame::Insert<Array>(Reference location, Array& value)
        {
            if ( (location.Type() == ReferenceTypes::Array) && (location.Offset() < 256) )
                Arrays(location.Offset()) = &value;
        }
        template<> void StackFrame::Insert<Class>(Reference location, Class& value)
        {
            if ((location.Type() == ReferenceTypes::Object) && (location.Offset() < 256))
                Classes(location.Offset()) = &value;
        }
        template<> void StackFrame::Insert<Function>(Reference location, Function& value)
        {
            if ((location.Type() == ReferenceTypes::Function) && (location.Offset() < 256))
                Functions(location.Offset()) = &value;
        }
        template<> void StackFrame::Insert<Number>(Reference location, Number& value)
        {
            if ((location.Type() == ReferenceTypes::Number) && (location.Offset() < 256))
                Numbers(location.Offset()) = value;
        }
        template<> void StackFrame::Insert<Reference>(Reference location, Reference& value)
        {
            if ((location.Type() != ReferenceTypes::Reference) || (location.Offset() >= 256))
                return;

            uint offset = location.Offset();
            switch (location.Index())
            {
                case 0:     Input(offset) = value;      break;
                case 1:     Local(offset) = value;      break;
                case 2:     Output(offset) = value;     break;
                default:    break;
            }
        }
        template<> void StackFrame::Insert<String>(Reference location, String& value)
        {
            if ((location.Type() == ReferenceTypes::String) && (location.Offset() < 256))
                Strings(location.Offset()) = &value;
        }

        void StackFrame::Delete(Reference location)
        {
            uint offset = location.Offset();
            if (offset > 255) { return; }
            switch (location.Type())
            {
                case ReferenceTypes::Array:         Arrays(offset) = nullptr;           break;
                case ReferenceTypes::Object:        Classes(offset) = nullptr;          break;
                case ReferenceTypes::Function:      Functions(offset) = nullptr;        break;
                case ReferenceTypes::Number:        Numbers(offset) = 0;                break;
                case ReferenceTypes::Reference:     Access<Reference>(location) = 0;    break;
                case ReferenceTypes::String:        Strings(offset) = nullptr;          break;
                default:                            break;
            }
        }
        void StackFrame::Reset()
        {
            Reference r;
            Input.Fill(r);
            Local.Fill(r);
            Output.Fill(r);
        }

    }
}