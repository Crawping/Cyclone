#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {

        /** PROPERTIES **/



        /** CONSTRUCTOR **/
        VirtualProperty::VirtualProperty()
        {

        }

        Literal VirtualProperty::Get(uint instance) const
        {
            return _instances.Contains(instance) ? _instances[instance] : Literal();
        }




        Literal VirtualClass::Get(uint object, uint property) const
        {
            return _properties.Contains(property) ? _properties[property].Get(object) : Literal();
        }
        bool VirtualClass::IsOfType(const Literal& object) const
        {
            return object.IsObject() && (object.FirstComponent() == ID());
        }

    }
}