#include "Storage/VirtualWorkspace.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualWorkspace::VirtualWorkspace()
        {
            _locals.Insert(0, VirtualVariable());
        }



        /** UTILITIES **/
        void VirtualWorkspace::Set(uint id, const VirtualVariable& value)
        {
            if (id) { _locals.Insert(id, value); }
        }
    }
}
