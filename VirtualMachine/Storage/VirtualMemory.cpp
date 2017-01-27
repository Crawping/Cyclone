#include "Storage/VirtualMemory.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualMemory::VirtualMemory()
        {
            Variables.Insert(0, Literal());
        }



        /** UTILITIES **/
        Literal& VirtualMemory::Access(uint id)                                   { return Variables[id]; }
        Literal& VirtualMemory::Access(uint type, uint property, uint instance)
        {
            return Classes[type].Access(instance, property);
        }
        void VirtualMemory::Delete(uint id)
        {
            if (id == 0) { return; }
            Variables.Remove(id);
        }
        uint VirtualMemory::Find(const string& name)                        const { return Strings.Find(name); }
        const string& VirtualMemory::Find(uint id)                          const { return Strings.Find(id); }
        Literal VirtualMemory::Get(uint id)                                 const
        {
            return Variables.Contains(id) ? Variables[id] : Literal();
        }
        Literal VirtualMemory::Get(uint type, uint property, uint instance) const
        {
            return Classes.Contains(type) ? Classes[type].Get(instance, property) : Literal();
        }
        void VirtualMemory::Insert(const VirtualClass& type)
        {
            Classes.Insert(type.ID(), type);
        }
        void VirtualMemory::Insert(const VirtualFunction& function)
        {
            Functions.Insert(function.ID(), function);
        }
        uint VirtualMemory::Insert(const string& string)
        {
            return Strings.Insert(string);
        }
        uint VirtualMemory::Insert(const string& name, const Literal& value)
        {
            uint id = Strings.Insert(name);
            Variables.Insert(id, value);
            return id;
        }
        void VirtualMemory::Set(uint id, const Literal& value)
        {
            if (id == 0) { return; }
            Variables.Insert(id, value);
        }
        void VirtualMemory::Set(uint type, uint property, uint instance, const Literal& value)
        {
            if ((type == 0) || !Classes.Contains(type)) { return; }
            Classes[type].Set(instance, property, value);
        }

    }
}