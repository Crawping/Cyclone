#include "Virtual/Memory.h"



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
                Variables.Insert(0, Variable());
            }



            /** UTILITIES **/
            Variable& Memory::Access(Address location)
            {
                return location.Base() ?
                    Classes[location.Base()].Access(location) :
                    Variables[location.Base()];
            }
            const Vector<Instruction>& Memory::Call(Address location) const
            {
                return location.Base() ?
                    Classes[location.Base()].Call(location) :
                    Functions[location.Base()].Logic();
            }
            //const Vector<Instruction>& Memory::Call(const Variable& function) const
            //{
            //    switch (function.Type())
            //    {
            //        case VariableTypes::Function:
            //            return CallFunction(function.FirstHalf());
            //        case VariableTypes::Object:
            //            return CallMethod(function.FirstHalf(), function.SecondHalf());
            //        case VariableTypes::Reference:
            //            return (function.FirstHalf() > VariableTypes::Reference) ? 
            //                Call( Variable(VariableTypes::Object, function.FirstHalf(), function.SecondHalf()) ) : 
            //                Call( Variable(function.FirstHalf(), function.SecondHalf()) );
            //        default:
            //            return Functions[0].Logic();
            //    }
            //}
            //const Vector<Instruction>& Memory::CallFunction(uint id)                 const
            //{
            //    return Functions[ Functions.Contains(id) ? id : 0 ].Logic();
            //}
            //const Vector<Instruction>& Memory::CallMethod(uint type, uint method)    const
            //{
            //    return Classes[ Classes.Contains(type) ? type : 0 ].Call(method);
            //}

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
            //        case VariableTypes::Array:
            //            return DeleteArray(reference.SecondHalf());
            //        case VariableTypes::Object:
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
            //        case VariableTypes::Array:
            //            return property.IsInteger() ? GetArray(reference.SecondHalf(), property.SecondHalf()) : Variables[0];
            //        case VariableTypes::Object:
            //            return GetObject(reference.FirstHalf(), property.SecondHalf(), reference.SecondHalf());
            //        case VariableTypes::Reference:
            //            return (reference.FirstHalf() > VariableTypes::Reference) ? 
            //                Get( Variable(VariableTypes::Object, reference.FirstHalf(), reference.SecondHalf()), property ) : 
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
