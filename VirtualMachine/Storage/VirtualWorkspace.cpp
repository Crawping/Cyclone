#include "Storage/VirtualWorkspace.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualWorkspace::VirtualWorkspace()
        {
            _locals.Insert(0, Literal());
        }



        /** UTILITIES **/
        void VirtualWorkspace::Set(uint id, const Literal& value)
        {
            if (id) { _locals.Insert(id, value); }
        }
    }
}
