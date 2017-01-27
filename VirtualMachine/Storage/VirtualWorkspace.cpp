#include "Storage/VirtualWorkspace.h"



namespace Cyclone
{
    namespace VM
    {

        /** CONSTRUCTOR **/
        VirtualWorkspace::VirtualWorkspace(const VirtualMemory& memory) :
            _memory(&memory)
        {
            _locals.Insert(0, Literal());
        }



        /** OPERATORS **/
        Literal VirtualWorkspace::operator ()(uint index) const
        {
            return (index < Count()) ? _workspace(index) : Literal();
        }

    }
}
