#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualProperty::VirtualProperty(uint id) :
            _id(id)
        {

        }

        Literal VirtualProperty::Get(uint instance) const
        {
            return _instances.Contains(instance) ? _instances[instance] : Literal();
        }
        void VirtualProperty::Set(uint instance, const Literal& value)
        {
            _instances.Insert(instance, value);
        }



        /** UTILITIES **/
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
