#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {

        /** PROPERTIES **/
        VirtualProperty& VirtualProperty::Value(const Literal& value)
        {
            _value = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        VirtualProperty::VirtualProperty()
        {

        }

    }
}