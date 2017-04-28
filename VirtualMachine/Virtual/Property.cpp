#include "Virtual/Property.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            /** CONSTRUCTOR **/
            Property::Property(uint id) :
                _id(id)
            {
                _instances.Insert(0, Variable());
            }



            /** UTILITIES **/
            void Property::Delete(uint instance)
            {
                _instances.Remove(instance);
            }
            Variable& Property::Get(uint instance)
            {
                return _instances[ _instances.Contains(instance) ? instance : 0 ];
            }
            void Property::Set(uint instance, const Variable& value)
            {
                _instances.Insert(instance, value);
            }

        }
    }
}
