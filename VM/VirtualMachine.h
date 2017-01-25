/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Event.h"
#include "Collections/Stack.h"
#include "Collections/Vector.h"
#include "Execution/Instructions.h"
#include "Storage/Literal.h"
#include "Storage/VirtualMemory.h"



namespace Cyclone
{
    namespace VM
    {
        struct StackFrame
        {
            uint            ReturnAddress;
            Stack<Literal>  Workspace;
        };


        class VirtualMachine
        {
            public:

                /** PROPERTIES **/
                const VirtualMemory* Data() const { return _data; }

                VMAPI VirtualMachine& Data(VirtualMemory* value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                VMAPI VirtualMachine();
                VMAPI ~VirtualMachine();



                /** UTILITIES **/
                void Insert(const Vector<Literal>& values)  { Workspace.Push(values); }
                void Clear()                                { Workspace.Clear(); }

                VMAPI void Execute(const Vector<Instruction>& commands);
                VMAPI void Pause();
                VMAPI void Resume();

            private:

                VirtualMemory*       _data;

                Stack<uint>         CallStack;
                Instructions        Interrupt;
                Stack<Literal>      Workspace;



                /** UTILITIES **/
                void Push(Literal value)                    { Workspace.Push(value); }
                void Push(const Vector<Literal>& values)    { Workspace.Push(values); }
                Literal Pop()                               { return Workspace.Pop(); }

        };
    }
}
