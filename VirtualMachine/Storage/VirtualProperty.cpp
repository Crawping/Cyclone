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



        /** UTILITIES **/
        Literal& VirtualProperty::Access(uint instance)
        {
            return _instances[instance];
        }
        Literal VirtualProperty::Get(uint instance) const
        {
            return _instances.Contains(instance) ? _instances[instance] : Literal();
        }
        void VirtualProperty::Set(uint instance, const Literal& value)
        {
            _instances.Insert(instance, value);
        }
        
    }
}
