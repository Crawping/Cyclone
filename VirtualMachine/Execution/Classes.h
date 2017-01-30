/* CHANGELOG
 * Written by Josh Grooms on 20170129
 */

#pragma once
#include "Execution/Instructions.h"



namespace Cyclone
{
    namespace VM
    {
        Vector<Instruction> Integer()
        {
            return
            {
                { Instructions::DefineClass,    1 },
                { Instructions::DefineProperty, 1 },
                { Instructions::DefineProperty, 2 },
            };
        }

        Vector<Instruction> Object()
        {
            return
            {
                { Instructions::DefineClass,    1 },
                { Instructions::DefineProperty, 1 },
            }
        }
    }
}
