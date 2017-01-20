#include "Storage/VirtualTable.h"
#include <functional>


namespace Cyclone
{
    namespace VM
    {

        static std::hash<string> Hash;



        /** UTILITIES **/

        int VirtualTable::FindID(const string& name)    const
        {
            uint id = Hash(name);
            return Strings.Contains(id) ? id : -1;
        }
        string VirtualTable::FindName(uint id)          const
        {
            return Strings.Contains(id) ? Strings[id] : "";
        }
        Literal VirtualTable::Get(const Literal& object)
        {
            switch (object.Type)
            {
                case LiteralTypes::Function:
                case LiteralTypes::String:
                case LiteralTypes::Type:
                    return object;
            }
        }
        Literal VirtualTable::Insert(const VirtualClass& type)
        {
            Classes.Insert(type.ID(), type);
            return Literal(LiteralTypes::Type, type.ID());
        }
        Literal VirtualTable::Insert(const VirtualFunction& function)
        {
            Functions.Insert(function.ID(), function);
            return Literal(LiteralTypes::Function, function.ID());
        }
        Literal VirtualTable::Insert(const string& string)
        {
            uint id = Hash(string);
            Strings.Insert(id, string);
            return Literal(LiteralTypes::String, id);
        }



    }
}