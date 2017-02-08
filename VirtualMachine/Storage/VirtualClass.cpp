#include "Storage/VirtualClass.h"



namespace Cyclone
{
    namespace VM
    {

        /** UTILITIES **/
        void VirtualClass::Delete(uint instance)
        {
            if (ID() == 0 || !_instances.Contains(instance)) { return; }
            for (auto& kvp : _properties)
                kvp.Value.Delete(instance);
        }
        VirtualVariable& VirtualClass::Get(uint object, uint property)
        {
            return _properties[ _properties.Contains(property) ? property : 0 ].Get(object);
        }
        void VirtualClass::Insert(const VirtualFunction& function)
        {
            if (ID() == 0 || function.ID() == 0) { return; }
            _methods.Insert(function.ID(), function);
        }
        void VirtualClass::Insert(const VirtualProperty& property)
        {
            if (ID() == 0) { return; }
            _properties.Insert(property.ID(), property);
        }
        bool VirtualClass::IsMethod(uint id)                                        const { return _methods.Contains(id); }
        bool VirtualClass::IsOfType(const VirtualVariable& object)                  const
        {
            return object.IsObject() && (object.FirstHalf() == ID());
        }
        void VirtualClass::Set(uint instance, uint property, const VirtualVariable& value)
        {
            if (ID() == 0 || !_properties.Contains(property)) { return; }
            _instances.Insert(instance);
            _properties[property].Set(instance, value);
        }

    }
}
