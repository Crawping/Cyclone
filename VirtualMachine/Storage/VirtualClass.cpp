#include "Storage/VirtualClass.h"



namespace Cyclone
{
    namespace VM
    {

        /** UTILITIES **/
        Literal& VirtualClass::Access(uint instance, uint property)
        {
            return _properties[ _properties.Contains(property) ? property : 0 ].Access(instance);
        }
        const Literal& VirtualClass::Access(uint instance, uint property) const
        {
            return _properties[_properties.Contains(property) ? property : 0].Access(instance);
        }
        Literal VirtualClass::Get(uint object, uint property)       const
        {
            return _properties[ _properties.Contains(property) ? property : 0 ].Get(object);
        }
        void VirtualClass::Insert(const VirtualFunction& function)
        {
            if (function.ID() == 0) { return; }
            _methods.Insert(function.ID(), function);
        }
        void VirtualClass::Insert(const VirtualProperty& property)
        {
            _properties.Insert(property.ID(), property);
        }
        bool VirtualClass::IsMethod(uint id)                        const { return _methods.Contains(id); }
        bool VirtualClass::IsOfType(const Literal& object)          const
        {
            return object.IsObject() && (object.FirstHalf() == ID());
        }
        void VirtualClass::Set(uint instance, uint property, const Literal& value)
        {
            if (!_properties.Contains(property)) { return; }
            _properties[property].Set(instance, value);
        }

    }
}