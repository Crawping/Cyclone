#include "IO/Console.h"
#include "Collections/Vector.h"
#include "Virtual/Machine.h"
#include "Virtual/Memory.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            /** CONSTRUCTOR & DESTRUCTOR **/
            Machine::Machine()
            {

            }
            Machine::~Machine()
            {
                //if (_memory) { delete _memory; }
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



                    if (cmd >= Instructions::Add && cmd <= Instructions::Xor)
                    {
                        OperateNumbers(cmd, ops(0), ops(1), ops(2));
                        continue;
                    }
                    switch (cmd)
                    {
                        case Instructions::Abort:               return;
                    //    case Instructions::Call:
                    //        break;

                    //    //case Instructions::Copy:                xop = yop;                                      break;
                    //    //case Instructions::Delete:              xop = Variable();                               break;
                    //    //case Instructions::Get:                 xop = yop;                                      break;
                    //    //case Instructions::Index:                                                               break;

                        case Instructions::Jump:                a = ops(0).Offset();                          break;
                        case Instructions::JumpIf:

                            if (ops(0).Type() == ReferenceTypes::Reference)
                                a = Access<Reference>(ops(0)) ? ops(1).Offset() : ops(2).Offset();
                            else
                                a = Access<Number>(ops(0)) ? ops(1).Offset() : ops(2).Offset();
                            break;

                    //    //case Instructions::Load:                xop = yop;                                      break;
                        case Instructions::Print:
                            Console::WriteLine(Access<string>(ops(0)));
                            break;
                    //    //case Instructions::Set:                                                                 break;
                    //    //case Instructions::Swap:                                                                break;

                    //    default:                                break;
                    }
                }
            }



            /** PRIVATE UTILITIES **/
            template<> Reference& Machine::Access<Reference>(Reference location)
            {
                return location.Storage() ? 
                    Registers().Access(location) : 
                    _memory.Access<Reference>(location);
            }

            void Machine::OperateNumbers(Instructions cmd, Reference xop, Reference yop, Reference zop)
            {
                Number& x(Access<Number>(xop));
                Number& y(Access<Number>(yop));
                Number& z(Access<Number>(zop));

                switch (cmd)
                {
                    case Instructions::Add:             x = y + z;              break;
                    case Instructions::Cast:            x.Cast(y.Type());       break;
                    case Instructions::Compare:         x = y.Compare(z);       break;
                    case Instructions::Copy:            x = y;                  break;
                    case Instructions::Decrement:       x--;                    break;
                    case Instructions::Divide:          x = y / z;              break;
                    case Instructions::Increment:       x++;                    break;
                    case Instructions::Multiply:        x = y * z;              break;
                    case Instructions::Negate:          x = ~y;                 break;
                    case Instructions::Not:             x = !y;                 break;
                    case Instructions::Or:              x = y | z;              break;
                    case Instructions::Subtract:        x = y - z;              break;
                    case Instructions::Xor:             x = y ^ z;              break;
                    default:                                                    break;
                }
            }

            
            //void Machine::Call(double address, Variable& lhs, Variable& rhs)
            //{
            //    //StackFrame newFrame;
            //    ////newFrame.Registers.Access(0) = rhs;

            //    //_scopes.Push(newFrame);
            //    ////Execute(_memory->Call(address));
            //    //newFrame = _scopes.Pop();

            //    //Registers().Output = newFrame.Registers.Output;
            //}
        }
    }
}