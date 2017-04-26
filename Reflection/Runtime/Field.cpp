#include "../Utilities/Utilities.h"
#include "Runtime/Field.h"



namespace Cyclone
{
    namespace Reflection
    {

        /** CONSTRUCTOR **/
        Field::Field(const Metaclass& type, const string& name) : 
            _id(hash(name)),
            _name(name),
            _offset(0),
            _type(type)
        {

        }

    }
}