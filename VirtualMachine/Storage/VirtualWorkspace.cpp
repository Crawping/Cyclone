#include "Storage/VirtualWorkspace.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            /** CONSTRUCTOR **/
            VirtualWorkspace::VirtualWorkspace()
            {
                _locals.Insert(0, Variable());
            }



            /** UTILITIES **/
            void VirtualWorkspace::Set(uint id, const Variable& value)
            {
                if (id) { _locals.Insert(id, value); }
            }

        }
    }
}
