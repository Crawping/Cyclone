#include "Virtual/Memory.h"
#include "Virtual/Array.h"
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
            template<> string& Memory::Access<string>(Reference location)
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
            template<> void Memory::Insert<string>(Reference location, const string& value)
            {
                if (location.Type() == ReferenceTypes::String)
                    Strings.Insert(location.Offset(), value);
            }

            void Memory::Remove(Reference location)
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

            //void Memory::CopyArray(uint source, uint destination)
            //{
            //    if (!destination) { return; }
            //    Arrays.Insert(destination, Arrays[ Arrays.Contains(source) ? source : 0 ]);
            //}
            //void Memory::CopyObject(uint type, uint source, uint destination)
            //{
            //    if (!destination) { return; }

            //}
            //void Memory::Delete(const Variable& reference)
            //{
            //    if (reference.IsNull()) { return; }
            //    switch (reference.Type())
            //    {
            //        case ReferenceTypes::Array:
            //            return DeleteArray(reference.SecondHalf());
            //        case ReferenceTypes::Object:
            //            return DeleteObject(reference.FirstHalf(), reference.SecondHalf());
            //    }
            //}
            //void Memory::DeleteArray(uint id)
            //{
            //    if (!id) { return; }
            //    Arrays.Remove(id);
            //}
            //void Memory::DeleteObject(uint type, uint id)
            //{
            //    Classes[ Classes.Contains(type) ? type : 0 ].Delete(id);
            //}
            //void Memory::DeleteVariable(uint id)
            //{
            //    if (id == 0) { return; }
            //    Variables.Remove(id);
            //}

            //uint Memory::Find(const string& name)                                    const { return Strings.Find(name); }
            //const string& Memory::Find(uint id)                                      const { return Strings.Find(id); }

            //Variable& Memory::Get(const Variable& reference, const Variable& property)
            //{
            //    switch (reference.Type())
            //    {
            //        case ReferenceTypes::Array:
            //            return property.IsInteger() ? GetArray(reference.SecondHalf(), property.SecondHalf()) : Variables[0];
            //        case ReferenceTypes::Object:
            //            return GetObject(reference.FirstHalf(), property.SecondHalf(), reference.SecondHalf());
            //        case ReferenceTypes::Reference:
            //            return (reference.FirstHalf() > ReferenceTypes::Reference) ? 
            //                Get( Variable(ReferenceTypes::Object, reference.FirstHalf(), reference.SecondHalf()), property ) : 
            //                Get( Variable(reference.FirstHalf(), reference.SecondHalf()), property );
            //        default:
            //            return Variables[0];
            //    }
            //}
            //Variable& Memory::GetArray(uint id, uint index)
            //{
            //    return Arrays[ Arrays.Contains(id) ? id : 0 ].Get(index);
            //}
            //Variable& Memory::GetObject(uint type, uint property, uint id)
            //{
            //    return Classes[ Classes.Contains(type) ? type : 0 ].Get(id, property);
            //}
            //Variable& Memory::GetVariable(uint id)
            //{
            //    return Variables[ Variables.Contains(id) ? id : 0 ];
            //}

            //void Memory::Insert(const Class& type)
            //{
            //    if (type.ID() == 0) { return; }
            //    Classes.Insert(type.ID(), type);
            //}
            //void Memory::Insert(const Function& function)
            //{
            //    if (function.ID() == 0) { return; }
            //    Functions.Insert(function.ID(), function);
            //}
            //void Memory::Insert(uint type, const Property& property)
            //{
            //    if (type == 0) { return; }
            //    else if (Classes.Contains(type)) { Classes[type].Insert(property); }
            //    else
            //    {
            //        Class classdef(type);
            //        classdef.Insert(property);
            //        Classes.Insert(type, classdef);
            //    }
            //}
            //uint Memory::Insert(const string& string)
            //{
            //    return Strings.Insert(string);
            //}
            //uint Memory::Insert(const string& name, const Variable& value)
            //{
            //    uint id = Strings.Insert(name);
            //    Variables.Insert(id, value);
            //    return id;
            //}

            //void Memory::Set(const Variable& reference, const Variable& property, const Variable& value)
            //{
            //    Variable& data = Get(reference, property);
            //    if (!data.IsNull()) { data = value; }
            //}
            //void Memory::SetArray(uint id, uint index, const Variable& value)
            //{
            //    Arrays[ Arrays.Contains(id) ? id : 0 ].Set(index, value);
            //}
            //void Memory::SetObject(uint type, uint property, uint id, const Variable& value)
            //{
            //    Classes[ Classes.Contains(type) ? type : 0 ].Set(id, property, value);
            //}
            //void Memory::SetVariable(uint id, const Variable& value)
            //{
            //    if (!id) { return; }
            //    Variables.Insert(id, value);
            //}

        }
    }
}
