#include "Storage/VirtualTable.h"
#include <functional>


namespace Cyclone
{
    namespace VM
    {

        /** INTERNAL UTILITIES **/
        static std::hash<string> Hash;



        /** CONSTRUCTOR **/
        VirtualTable::VirtualTable()
        {
            Strings.Insert(0, "");
            Variables.Insert(0, Literal());
        }



        /** UTILITIES **/
        void VirtualTable::Delete(uint id)
        {
            if (id == 0) { return; }
            Variables.Remove(id);
        }
        uint VirtualTable::FindID(const string& name)    const
        {
            if (name.empty()) { return 0; }
            uint id = Hash(name);
            return Strings.Contains(id) ? id : 0;
        }
        string VirtualTable::FindName(uint id)          const
        {
            return Strings.Contains(id) ? Strings[id] : "";
        }
        Literal VirtualTable::Get(uint id) const
        {
            return Variables.Contains(id) ? Variables[id] : Literal();
        }
        Literal VirtualTable::Get(uint type, uint property, uint instance) const
        {
            return Classes.Contains(type) ? Classes[type].Get(instance, property) : Literal();
        }
        void VirtualTable::Insert(const VirtualClass& type)
        {
            Classes.Insert(type.ID(), type);
        }
        void VirtualTable::Insert(const VirtualFunction& function)
        {
            Functions.Insert(function.ID(), function);
        }
        uint VirtualTable::Insert(const string& string)
        {
            if (string.empty()) { return 0; }
            uint id = Hash(string);
            Strings.Insert(id, string);
            return id;
        }
        uint VirtualTable::Insert(const string& name, const Literal& value)
        {
            if (name.empty()) { return 0; }
            uint id = Hash(name);
            Strings.Insert(id, name);
            Variables.Insert(id, value);
            return id;
        }
        void VirtualTable::Set(uint id, const Literal& value)
        {
            if (id == 0) { return; }
            Variables.Insert(id, value);
        }
        void VirtualTable::Set(uint type, uint property, uint instance, const Literal& value)
        {
            if ((type == 0) || !Classes.Contains(type)) { return; }
            Classes[type].Set(instance, property, value);
        }

    }
}