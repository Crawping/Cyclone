/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Stack.h"
#include "Virtual/Memory.h"
#include "Execution/Instructions.h"


namespace Cyclone
{
    namespace VM
    {
        struct Instruction;

        namespace Virtual
        {
            using namespace Utilities;

            class Machine
            {
                public:

                    VMAPI void Abort();
                    VMAPI void Execute(const ICollection<Instruction>& instructions);

                private:

                    struct StackFrame;

                    Instructions        _interrupt;
                    Memory*             _memory;
                    Stack<StackFrame>   _scopes;


                    Variable& Access(double address);
                    void Call(Variable& lhs, Variable& fcn, Variable& rhs);
            };


        }
    }
}
