/* CHANGELOG
 * Written by Josh Grooms on 20170129
 */

#pragma once
#include "Execution/Instructions.h"



namespace Cyclone
{
    namespace VM
    {
        Vector<Instruction> Enumeration()
        {
            return { };
        }

        Vector<Instruction> Function()
        {
            return { };
        }

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
            };
        }

        Vector<Instruction> String()
        {
            return { };
        }
    }
}
