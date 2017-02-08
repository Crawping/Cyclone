#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualProperty::VirtualProperty() :
            _id(0)
        {

        }
        VirtualProperty::VirtualProperty(uint id, const VirtualVariable& type) :
            _id(id),
            _type(type)
        {
            _instances.Insert(0, VirtualVariable());
        }



        /** UTILITIES **/
        void VirtualProperty::Delete(uint instance)
        {
            _instances.Remove(instance);
        }
        VirtualVariable& VirtualProperty::Get(uint instance)
        {
            return _instances[ _instances.Contains(instance) ? instance : 0 ];
        }
        void VirtualProperty::Set(uint instance, const VirtualVariable& value)
        {
            _instances.Insert(instance, value);
        }

    }
}
