#include "Storage/VirtualClass.h"



namespace Cyclone
{
    namespace VM
    {

        /** UTILITIES **/
        Literal& VirtualClass::Access(uint instance, uint property)
        {
            return _properties[property].Access(instance);
        }
        Literal VirtualClass::Get(uint object, uint property) const
        {
            return _properties.Contains(property) ? _properties[property].Get(object) : Literal();
        }
        void VirtualClass::Insert(const VirtualFunction& function)
        {
            _methods.Insert(function.ID(), function);
        }
        void VirtualClass::Insert(const VirtualProperty& property)
        {
            _properties.Insert(property.ID(), property);
        }
        bool VirtualClass::IsOfType(const Literal& object) const
        {
            return object.IsObject() && (object.FirstHalf() == ID());
        }
        void VirtualClass::Set(uint object, uint property, const Literal& value)
        {
            if (!_properties.Contains(property)) { return; }
            _properties[property].Set(object, value);
        }

    }
}