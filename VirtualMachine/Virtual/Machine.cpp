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

                        case Instructions::Copy:
                            switch (ops(0).Type())
                            {
                                case ReferenceTypes::Array:     Access<Array>(ops(0)) = Access<Array>(ops(1));          break;
                                case ReferenceTypes::Number:    Access<Number>(ops(0)) = Access<Number>(ops(1));        break;
                                case ReferenceTypes::Reference: Access<Reference>(ops(0)) = Access<Reference>(ops(1));  break;
                                default:                        break;
                            }
                            break;
                    //    //case Instructions::Delete:              xop = Variable();                               break;
                    //    //case Instructions::Get:                 xop = yop;                                      break;
                    //    //case Instructions::Index:                                                               break;

                        case Instructions::Jump:                a = ops(0).Offset();                                    break;
                        case Instructions::JumpIf:

                            if (ops(0).Type() == ReferenceTypes::Reference)
                                a = Access<Reference>(ops(0)) ? ops(1).Offset() : ops(2).Offset();
                            else
                                a = Access<Number>(ops(0)) ? ops(1).Offset() : ops(2).Offset();
                            break;

                        case Instructions::Load:                Load(ops(0), ops(1));                                   break;
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
            //template<> Reference& Machine::Access<Reference>(Reference location)
            //{
            //    return location.Storage() ? 
            //        Registers().Access(location) : 
            //        _memory.Access<Reference>(location);
            //}
            void Machine::Load(Reference x, Reference y)
            {
                switch (x.Type())
                {
                    case ReferenceTypes::Array:         Workspace().Insert(x, Access<Array>(y));        break;
                    //case ReferenceTypes::Object:        Workspace().Insert(x, Access<Class>(y));        break;
                    //case ReferenceTypes::Function:      Workspace().Insert(x, Access<Function>(y));     break;
                    case ReferenceTypes::Number:        Workspace().Insert(x, Access<Number>(y));       break;
                    case ReferenceTypes::Reference:     Workspace().Insert(x, Access<Reference>(y));    break;
                    case ReferenceTypes::String:        Workspace().Insert(x, Access<string>(y));       break;
                    default:                            break;
                }
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