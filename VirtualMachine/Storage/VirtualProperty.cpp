#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualProperty::VirtualProperty(uint id) :
            _id(id)
        {
            _instances.Insert(0, VirtualVariable());
        }



        /** UTILITIES **/
        VirtualVariable& VirtualProperty::Access(uint instance)
        {
            return _instances[ _instances.Contains(instance) ? instance : 0 ];
        }
        const VirtualVariable& VirtualProperty::Access(uint instance)           const
        {
            return _instances[ _instances.Contains(instance) ? instance : 0 ];
        }
        VirtualVariable VirtualProperty::Get(uint instance)                     const
        {
            return _instances.Contains(instance) ? _instances[instance] : VirtualVariable();
        }
        void VirtualProperty::Set(uint instance, const VirtualVariable& value)
        {
            _instances.Insert(instance, value);
        }

    }
}
