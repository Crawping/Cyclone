/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Stack.h"
#include "Execution/Instructions.h"
#include "Storage/StackFrame.h"
#include "Storage/Address.h"
#include "Virtual/Memory.h"


namespace Cyclone
{
    namespace VM
    {
        struct Instruction;

        namespace Virtual
        {
            class Memory;


            class Machine
            {
                public:

                    /** CONSTRUCTOR & DESTRUCTOR **/
                    VMAPI Machine();
                    VMAPI ~Machine();



                    /** UTILITIES **/
                    VMAPI void Abort();
                    VMAPI void Pause();
                    VMAPI void Resume();
                    VMAPI void Execute(const ICollection<Instruction>& instructions);

                protected:

                    RegisterFrame& Registers()  { return Workspace().Registers; }
                    StackFrame& Workspace()     { return _scopes.First(); }

                private:

                    Instructions        _interrupt;
                    Memory              _memory;
                    Stack<StackFrame>   _scopes;



                    /** UTILITIES **/
                    //Variable& Access(double address);
                    //void Call(double address, Variable& lhs, Variable& rhs);
                    //void Delete()

                    template<typename T = Variable> 
                    T& Access(Reference location)   { return _memory.Access<T>(location); }


                    void OperateNumbers(Instructions cmd, Reference xop, Reference yop, Reference zop);


            };


        }
    }
}
