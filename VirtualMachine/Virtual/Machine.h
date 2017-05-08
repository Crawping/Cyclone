/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Stack.h"
#include "Execution/Instructions.h"
#include "Storage/StackFrame.h"
#include "Virtual/Memory.h"



namespace Cyclone
{
    namespace Virtual
    {
        struct Instruction;
        class Memory;


        class Machine
        {
            public:

                /** PROPERTIES **/
                Virtual::Memory& Memory() { return _memory; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                VMAPI Machine();
                VMAPI ~Machine();



                /** UTILITIES **/
                VMAPI void Abort();
                VMAPI void Pause();
                VMAPI void Resume();
                VMAPI void Execute(const ICollection<Instruction>& instructions);

                template<typename T> void Insert(Reference location, T& value)
                {
                    location.Base() ? 
                        Workspace().Insert<T>(location, value) :
                        _memory.Insert<T>(location, value);
                }

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
                    return location.Base()                  ?  
                        Workspace().Access<T>(location)     : 
                        _memory.Access<T>(location); 
                }

                void Allocate(Reference x, Reference y);
                void Call(Reference x, Reference y, Reference z);
                void Compute(Instructions cmd, Reference xop, Reference yop, Reference zop);
                void Copy(Reference x, Reference y);
                void Delete(Reference x);
                void Load(Reference x, Reference y);

        };

    }
}
