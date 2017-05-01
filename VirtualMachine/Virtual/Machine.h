/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Stack.h"
#include "Execution/Instructions.h"
#include "Storage/Reference.h"
#include "Storage/StackFrame.h"
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

                    /** PROPERTIES **/
                    const Virtual::Memory& Memory() const { return _memory; }



                    /** CONSTRUCTOR & DESTRUCTOR **/
                    VMAPI Machine();
                    VMAPI ~Machine();



                    /** UTILITIES **/
                    VMAPI void Abort();
                    VMAPI void Pause();
                    VMAPI void Resume();
                    VMAPI void Execute(const ICollection<Instruction>& instructions);

                protected:

                    StackFrame& Workspace()     { return _scopes.First(); }

                private:

                    Instructions        _interrupt;
                    Virtual::Memory     _memory;
                    Stack<StackFrame>   _scopes;



                    /** UTILITIES **/
                    //Variable& Access(double address);
                    //void Call(double address, Variable& lhs, Variable& rhs);
                    //void Delete()

                    template<typename T = Variable> 
                    T& Access(Reference location)   
                    { 
                        return location.Storage()               ?  
                            Workspace().Access<T>(location)     : 
                            _memory.Access<T>(location); 
                    }


                    void Load(Reference x, Reference y);
                    void OperateNumbers(Instructions cmd, Reference xop, Reference yop, Reference zop);


            };


        }
    }
}
