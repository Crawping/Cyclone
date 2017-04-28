#include "Collections/Vector.h"
#include "Virtual/Machine.h"
#include "Virtual/Memory.h"
#include "Virtual/Instruction.h"
#include "Virtual/Variable.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            /** CONSTRUCTOR & DESTRUCTOR **/
            Machine::Machine() :
                _memory(new Memory())
            {

            }
            Machine::~Machine()
            {
                if (_memory) { delete _memory; }
            }



            /** PUBLIC UTILITIES **/
            void Machine::Abort()   { _interrupt = Instructions::Abort; }
            void Machine::Pause()   { _interrupt = Instructions::Pause; }
            void Machine::Resume()  { _interrupt = Instructions::None; }

            void Machine::Execute(const ICollection<Instruction>& instructions)
            {
                for (uint a = 0; a < instructions.Count(); a++)
                {
                    const auto& cmd = instructions(a).Command;
                    const auto& ops = instructions(a).Operands;
                    Variable& xop(Access(ops(0)));
                    Variable& yop(Access(ops(1)));
                    Variable& zop(Access(ops(2)));

                    switch (cmd)
                    {
                        case Instructions::Abort:               return;
                        case Instructions::Add:                 xop = yop + zop;                                break;
                        case Instructions::Allocate:                                                            break;
                        case Instructions::And:                 xop = yop & zop;                                break;

                        case Instructions::Call:                Call(ops(0), yop, zop);                         break;
                        case Instructions::CallRelative:                                                        break;

                        case Instructions::Cast:                                                                break;
                        case Instructions::Compare:             xop = yop.Compare(zop);                         break;
                        case Instructions::Copy:                xop = yop;                                      break;
                        case Instructions::Decrement:           xop--;                                          break;
                        case Instructions::Delete:              xop = Variable();                               break;
                        case Instructions::Divide:              xop = yop / zop;                                break;
                        case Instructions::Get:                 xop = yop;                                      break;
                        case Instructions::Increment:           xop++;                                          break;
                        case Instructions::Index:                                                               break;

                        case Instructions::Jump:                a = (uint)ops(0);                               break;
                        case Instructions::JumpIf:              a = (uint)(xop ? ops(1) : ops(2));              break;
                        case Instructions::JumpRelative:        a += (int)ops(0);                               break;
                        case Instructions::JumpRelativeIf:      a += (int)(xop ? ops(1) : ops(2));              break;

                        case Instructions::Load:                xop = yop;                                      break;
                        case Instructions::Multiply:            xop = yop * zop;                                break;
                        case Instructions::Negate:              xop = ~yop;                                     break;
                        case Instructions::Not:                 xop = !yop;                                     break;
                        case Instructions::Or:                  xop = yop | zop;                                break;
                        case Instructions::Print:                                                               break;
                        case Instructions::Set:                                                                 break;
                        case Instructions::Subtract:            xop = yop - zop;                                break;
                        case Instructions::Swap:                                                                break;
                        case Instructions::Xor:                 xop = yop ^ zop;                                break;

                        default:                                break;
                    }
                }
            }



            /** PRIVATE UTILITIES **/
            Variable& Machine::Access(double address)
            {
                return (address < 0) ? Registers().Access((ulong)address) : _memory->Access((ulong)address);
            }
            void Machine::Call(double address, Variable& lhs, Variable& rhs)
            {
                StackFrame newFrame;
                newFrame.Registers.Access(0) = rhs;

                _scopes.Push(newFrame);
                Execute(_memory->Call(address));
                newFrame = _scopes.Pop();

                Registers().Output = newFrame.Registers.Output;
            }
        }
    }
}