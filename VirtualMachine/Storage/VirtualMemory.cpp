#include "Storage/VirtualMemory.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualMemory::VirtualMemory()
        {
            Arrays.Insert(0, { });
            Classes.Insert(0, { });
            Functions.Insert(0, { });
            Variables.Insert(0, VirtualVariable());
        }



        /** UTILITIES **/
        const Vector<Instruction>& VirtualMemory::Call(const VirtualVariable& function) const
        {
            switch (function.Type())
            {
                case VariableTypes::Function:
                    return CallFunction(function.FirstHalf());
                case VariableTypes::Object:
                    return CallMethod(function.FirstHalf(), function.SecondHalf());
                case VariableTypes::Reference:
                    return (function.FirstHalf() > VariableTypes::Reference) ? 
                        Call( VirtualVariable(VariableTypes::Object, function.FirstHalf(), function.SecondHalf()) ) : 
                        Call( VirtualVariable(function.FirstHalf(), function.SecondHalf()) );
                default:
                    return Functions[0].Logic();
            }
        }
        const Vector<Instruction>& VirtualMemory::CallFunction(uint id)                 const
        {
            return Functions[ Functions.Contains(id) ? id : 0 ].Logic();
        }
        const Vector<Instruction>& VirtualMemory::CallMethod(uint type, uint method)    const
        {
            return Classes[ Classes.Contains(type) ? type : 0 ].Call(method);
        }

        void VirtualMemory::CopyArray(uint source, uint destination)
        {
            if (!destination) { return; }
            Arrays.Insert(destination, Arrays[ Arrays.Contains(source) ? source : 0 ]);
        }
        void VirtualMemory::CopyObject(uint type, uint source, uint destination)
        {
            if (!destination) { return; }

        }

        //uint VirtualMemory::Define(VariableTypes type, const string& name)
        //{
        //    uint id = Strings.Insert(name);
        //    switch (type)
        //    {
        //        case VariableTypes::Function:

        //            break;
        //        case VariableTypes::Type:
        //            Classes.Insert(id, VirtualClass(id));
        //            break;
        //        default:
        //            Variables.Insert(id, VirtualVariable(type));
        //            break;
        //    }

        //    return id;
        //}

        void VirtualMemory::Delete(const VirtualVariable& reference)
        {
            if (reference.IsNull()) { return; }
            switch (reference.Type())
            {
                case VariableTypes::Array:
                    return DeleteArray(reference.SecondHalf());
                case VariableTypes::Object:
                    return DeleteObject(reference.FirstHalf(), reference.SecondHalf());
            }
        }
        void VirtualMemory::DeleteArray(uint id)
        {
            if (!id) { return; }
            Arrays.Remove(id);
        }
        void VirtualMemory::DeleteObject(uint type, uint id)
        {
            Classes[ Classes.Contains(type) ? type : 0 ].Delete(id);
        }
        void VirtualMemory::DeleteVariable(uint id)
        {
            if (id == 0) { return; }
            Variables.Remove(id);
        }

        uint VirtualMemory::Find(const string& name)                                    const { return Strings.Find(name); }
        const string& VirtualMemory::Find(uint id)                                      const { return Strings.Find(id); }

        VirtualVariable& VirtualMemory::Get(const VirtualVariable& reference, const VirtualVariable& property)
        {
            switch (reference.Type())
            {
                case VariableTypes::Array:
                    return property.IsInteger() ? GetArray(reference.SecondHalf(), property.SecondHalf()) : Variables[0];
                case VariableTypes::Object:
                    return GetObject(reference.FirstHalf(), property.SecondHalf(), reference.SecondHalf());
                case VariableTypes::Reference:
                    return (reference.FirstHalf() > VariableTypes::Reference) ? 
                        Get( VirtualVariable(VariableTypes::Object, reference.FirstHalf(), reference.SecondHalf()), property ) : 
                        Get( VirtualVariable(reference.FirstHalf(), reference.SecondHalf()), property );
                default:
                    return Variables[0];
            }
        }
        VirtualVariable& VirtualMemory::GetArray(uint id, uint index)
        {
            return Arrays[ Arrays.Contains(id) ? id : 0 ].Get(index);
        }
        VirtualVariable& VirtualMemory::GetObject(uint type, uint property, uint id)
        {
            return Classes[ Classes.Contains(type) ? type : 0 ].Get(id, property);
        }
        VirtualVariable& VirtualMemory::GetVariable(uint id)
        {
            return Variables[ Variables.Contains(id) ? id : 0 ];
        }

        void VirtualMemory::Insert(const VirtualClass& type)
        {
            if (type.ID() == 0) { return; }
            Classes.Insert(type.ID(), type);
        }
        void VirtualMemory::Insert(const VirtualFunction& function)
        {
            if (function.ID() == 0) { return; }
            Functions.Insert(function.ID(), function);
        }
        void VirtualMemory::Insert(uint type, const VirtualProperty& property)
        {
            if (type == 0) { return; }
            else if (Classes.Contains(type)) { Classes[type].Insert(property); }
            else
            {
                VirtualClass classdef(type);
                classdef.Insert(property);
                Classes.Insert(type, classdef);
            }
        }
        uint VirtualMemory::Insert(const string& string)
        {
            return Strings.Insert(string);
        }
        uint VirtualMemory::Insert(const string& name, const VirtualVariable& value)
        {
            uint id = Strings.Insert(name);
            Variables.Insert(id, value);
            return id;
        }

        void VirtualMemory::Set(const VirtualVariable& reference, const VirtualVariable& property, const VirtualVariable& value)
        {
            VirtualVariable& data = Get(reference, property);
            if (!data.IsNull()) { data = value; }
        }
        void VirtualMemory::SetArray(uint id, uint index, const VirtualVariable& value)
        {
            Arrays[ Arrays.Contains(id) ? id : 0 ].Set(index, value);
        }
        void VirtualMemory::SetObject(uint type, uint property, uint id, const VirtualVariable& value)
        {
            Classes[ Classes.Contains(type) ? type : 0 ].Set(id, property, value);
        }
        void VirtualMemory::SetVariable(uint id, const VirtualVariable& value)
        {
            if (!id) { return; }
            Variables.Insert(id, value);
        }
    }
}
