#include "Storage/StackFrame.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            Reference& RegisterFrame::Access(Reference location)
            {
                static Reference null;
                uint offset(location.Offset());
                switch (location.Slot())
                {
                    case 0:     return Input(offset);
                    case 1:     return Local(offset);
                    case 2:     return Output(offset);
                    case 3:     return Temporary(offset);
                    default:    return null;
                }
            }

        }
    }
}