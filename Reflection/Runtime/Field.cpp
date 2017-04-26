#include "../Utilities/Utilities.h"
#include "Runtime/Field.h"



namespace Cyclone
{
    namespace Reflection
    {

        /** PROPERTIES **/
        Field& Field::Value(const Variable& value)
        {
            _value = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        Field::Field(const string& name) : 
            _id(hash(name)),
            _name(name)
        {

        }

    }
}