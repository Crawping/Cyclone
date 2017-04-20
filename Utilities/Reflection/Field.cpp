#include "Utilities.h"
#include "Reflection/Field.h"



namespace Cyclone
{
    namespace Utilities
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