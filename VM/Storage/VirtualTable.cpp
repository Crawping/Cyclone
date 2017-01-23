#include "Storage/VirtualTable.h"
#include <functional>


namespace Cyclone
{
    namespace VM
    {

        static std::hash<string> Hash;



        /** UTILITIES **/
        void VirtualTable::Delete(uint id)
        {
            Variables.Remove(id);
        }
        int VirtualTable::FindID(const string& name)    const
        {
            uint id = Hash(name);
            return Strings.Contains(id) ? id : -1;
        }
        string VirtualTable::FindName(uint id)          const
        {
            return Strings.Contains(id) ? Strings[id] : "";
        }
        Literal VirtualTable::Get(uint id) const
        {
            return Variables.Contains(id) ? Variables[id] : Literal();
        }
        Literal VirtualTable::Get(uint type, uint instance, uint property) const
        {
            return Classes.Contains(type) ? Classes[type].Get(instance, property) : Literal();
        }
        void VirtualTable::Insert(const VirtualClass& type)
        {
            Classes.Insert(type.ID(), type);
            //return Literal(LiteralTypes::Type, (ulong)(type.ID()) << 32);
        }
        void VirtualTable::Insert(const VirtualFunction& function)
        {
            Functions.Insert(function.ID(), function);
            //return Literal(LiteralTypes::Function, function.ID());
        }
        uint VirtualTable::Insert(const string& string)
        {
            uint id = Hash(string);
            Strings.Insert(id, string);
            return id;
        }
        uint VirtualTable::Insert(const string& name, const Literal& value)
        {
            uint id = Hash(name);
            Strings.Insert(id, name);
            Variables.Insert(id, value);
            return id;
        }
        void VirtualTable::Set(uint id, const Literal& value)
        {
            Variables.Insert(id, value); 
        }
        void VirtualTable::Set(uint type, uint instance, uint property, const Literal& value)
        {
            if (!Classes.Contains(type)) { return; }
            Classes[type].Set(instance, property, value);
        }

    }
}