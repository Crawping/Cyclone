/* CHANGELOG
 * Written by Josh Grooms on 20170428
 */

#pragma once
#include "Collections/Vector.h"
#include "Virtual/Variable.h"



namespace Cyclone
{
    namespace VM
    {

        struct RegisterFrame
        {
            Vector<Virtual::Variable, 255> Input;
            Vector<Virtual::Variable, 255> Local;
            Vector<Virtual::Variable, 255> Output;
            Vector<Virtual::Variable, 255> Temporary;


            Virtual::Variable& Access(ulong address)
            {
                ubyte stride    = (ubyte)address;
                ubyte count     = (ubyte)(address >> 8);
                ubyte offset    = (ubyte)(address >> 16);
                ubyte base      = (ubyte)(address >> 24);

                switch (base)
                {
                    case 0:     return Input(offset);
                    case 1:     return Local(offset);
                    case 2:     return Output(offset);
                    case 3:     return Temporary(offset);
                    default:    return Virtual::Variable();
                }
            }
        };

        struct StackFrame
        {
            RegisterFrame   Registers;
            uint            ReturnIndex;
        };

    }
}
