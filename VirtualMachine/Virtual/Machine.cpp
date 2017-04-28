#include "Virtual/Machine.h"
#include "Virtual/Instruction.h"
#include "Virtual/Variable.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            struct RegisterFrame
            {
                Vector<Variable, 255> Input;
                Vector<Variable, 255> Local;
                Vector<Variable, 255> Output;
                Vector<Variable, 255> Temporary;


                Variable& Get(ulong address)
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
                        default:    return Variable();
                    }
                }
            };

            struct Machine::StackFrame
            {
                RegisterFrame   Registers;
                uint            ReturnIndex;
            };



            void Machine::Execute(const ICollection<Instruction>& instructions)
            {
                for (uint a = 0; a < instructions.Count(); a++)
                {
                    const auto& cmd = instructions(a).Command;
                    const auto& ops = instructions(a).Operands;
                    Variable& xop = Access(ops(0)), yop = Access(ops(1)), zop = Access(ops(2));

                    switch (cmd)
                    {
                        case Instructions::Add:         xop = yop + zop; break;
                        case Instructions::And:         xop = yop & zop; break;
                        case Instructions::Divide:      xop = yop / zop; break;
                        case Instructions::Multiply:    xop = yop * zop; break;
                        case Instructions::Negate:      xop = ~yop; break;
                        case Instructions::Not:         xop = !yop; break;
                        case Instructions::Or:          xop = yop | zop; break;
                        case Instructions::Subtract:    xop = yop - zop; break;
                        case Instructions::Xor:         xop = yop ^ zop; break;
                        default:                        break;
                    }
                }
            }




            Variable& Machine::Access(double address)
            {
                return (address < 0) ?
                    _scopes.First().Registers.Get((ulong)address) :
                    Variable();
            }
            void Machine::Call(Variable& lhs, Variable& fcn, Variable& rhs)
            {
                StackFrame newFrame;

            }
        }
    }
}