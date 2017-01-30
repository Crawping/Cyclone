#include "Storage/VirtualMemory.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualMemory::VirtualMemory()
        {
            Classes.Insert(0, { });
            Variables.Insert(0, VirtualVariable());
        }



        /** UTILITIES **/
        VirtualVariable& VirtualMemory::Access(uint id)                                   { return Variables[id]; }
        VirtualVariable& VirtualMemory::Access(uint type, uint property, uint instance)
        {
            return Classes[type].Access(instance, property);
        }
        void VirtualMemory::Delete(uint id)
        {
            if (id == 0) { return; }
            Variables.Remove(id);
        }
        uint VirtualMemory::Find(const string& name)                                    const { return Strings.Find(name); }
        const string& VirtualMemory::Find(uint id)                                      const { return Strings.Find(id); }
        VirtualVariable VirtualMemory::Get(uint id)                                     const
        {
            return Variables.Contains(id) ? Variables[id] : VirtualVariable();
        }
        VirtualVariable VirtualMemory::Get(uint type, uint property, uint instance)     const
        {
            return Classes.Contains(type) ? Classes[type].Get(instance, property) : VirtualVariable();
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
        void VirtualMemory::Set(uint id, const VirtualVariable& value)
        {
            if (id == 0) { return; }
            Variables.Insert(id, value);
        }
        void VirtualMemory::Set(uint type, uint property, uint instance, const VirtualVariable& value)
        {
            if ((type == 0) || !Classes.Contains(type)) { return; }
            Classes[type].Set(instance, property, value);
        }

    }
}
