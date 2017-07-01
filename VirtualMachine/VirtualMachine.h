/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Collections/Stack.h"
#include "Collections/Array.h"
#include "Execution/Instructions.h"
#include "IO/Event.h"
//#include "Storage/VirtualWorkspace.h"
#include "Virtual/Memory.h"



namespace Cyclone
{
    namespace Virtual
    {
        namespace Virtual
        {

            class VirtualMachine
            {
                public:

                    /** PROPERTIES **/
                //    const Memory* _values() const { return _data; }

                //    VMAPI VirtualMachine& _values(Memory* value);



                //    /** CONSTRUCTOR & DESTRUCTOR **/
                //    VMAPI VirtualMachine();
                //    VMAPI ~VirtualMachine();



                //    /** UTILITIES **/
                //    void Input(const Vector<Variable>& values)   { Workspace().Push(values); }
                //    void Clear()                                        { Workspace().Clear(); }

                //    VMAPI void Abort();
                //    //VMAPI void Execute(const Vector<Instruction>& commands);
                //    VMAPI void Pause();
                //    VMAPI void Resume();
                //    //VMAPI void Run(const Vector<Instruction>& instructions);

                //private:

                //    struct StackFrame
                //    {
                //        uint                        Index;
                //        const Vector<Instruction>*  Instructions;
                //        Stack<Variable>             Workspace;
                //    };

                //    Memory*      _data;
                //    Stack<StackFrame>   _frames;

                //    Instructions        Interrupt;



                //    /** PROPERTIES **/
                //    Stack<Variable>& Workspace()                 { return _frames.First().Workspace; }



                //    /** UTILITIES **/
                //    void Push(Variable value)                    { Workspace().Push(value); }
                //    void Push(const Vector<Variable>& values)    { Workspace().Push(values); }
                //    Variable Pop()                               { return Workspace().Pop(); }


            };
        }
    }
}
