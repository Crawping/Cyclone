#include "Console.h"
#include "VirtualMachine.h"



namespace Cyclone
{
    namespace VM
    {

        /** PROPERTIES **/
        VirtualMachine& VirtualMachine::Data(VirtualMemory* value)
        {
            _data = value;
            return *this;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        VirtualMachine::VirtualMachine() :
            _data(nullptr)
        {

        }
        VirtualMachine::~VirtualMachine()
        {

        }



        /** UTILITIES **/
        void VirtualMachine::Abort()    { Interrupt = Instructions::Abort; }
        void VirtualMachine::Pause()    { Interrupt = Instructions::Pause; }
        void VirtualMachine::Resume()   { Interrupt = Instructions::None; }

        void VirtualMachine::Execute(const Vector<Instruction>& instructions)
        {
            uint idx = 0;
            Literal v1, v2, v3, v4;
            int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
            StackFrame f1 = { instructions.Count(), { } };

            _frames.Push(f1);
            while (idx < instructions.Count())
            {
                if (Interrupt == Instructions::Return || Interrupt == Instructions::Abort)
                    return Resume();
                else if (Interrupt == Instructions::Pause)
                    continue;

                const auto& cmd = instructions(idx);
                switch (cmd.Command)
                {
                    case Instructions::Add:
                    case Instructions::And:
                    case Instructions::Divide:
                    case Instructions::Multiply:
                    case Instructions::Negate:
                    case Instructions::Not:
                    case Instructions::Or:
                    case Instructions::Subtract:
                    case Instructions::Xor:
                        Push( Literal::Calculate(cmd.Command, Pop(), Pop()) );
                        break;

                    case Instructions::AddSet:
                    case Instructions::AndSet:
                    case Instructions::DivideSet:
                    case Instructions::MultiplySet:
                    case Instructions::NegateSet:
                    case Instructions::NotSet:
                    case Instructions::OrSet:
                    case Instructions::SubtractSet:
                    case Instructions::XorSet:
                        v1 = Literal::Calculate(cmd.Command - 1, Pop(), Pop());
                        _data->Set(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2), v1);
                        break;

                    case Instructions::AddStore:
                    case Instructions::AndStore:
                    case Instructions::DivideStore:
                    case Instructions::MultiplyStore:
                    case Instructions::NegateStore:
                    case Instructions::NotStore:
                    case Instructions::OrStore:
                    case Instructions::SubtractStore:
                    case Instructions::XorStore:
                        _data->Set( cmd.Operands(0), Literal::Calculate(cmd.Command - 2, Pop(), Pop()) );
                        break;

                    case Instructions::Abort:
                        return;

                    case Instructions::Call:
                        _frames.Push({ idx, { } });
                        idx = cmd.Operands(0);
                        break;
                    case Instructions::CallRelative:
                        _frames.Push({ idx,  { } });
                        idx += cmd.Operands(0);
                        break;

                    case Instructions::Cast:
                        Push( Pop().Cast(cmd.Operands(0)) );
                        break;
                    case Instructions::CastStore:
                        _data->Set( cmd.Operands(0), Pop().Cast(cmd.Operands(1)) );
                        break;

                    case Instructions::Compare:
                        Push( Pop().Compare(Pop()) );
                        break;

                    case Instructions::Copy:
                        Push(Workspace().First());
                        break;
                    case Instructions::CopyMemory:
                        _data->Set( cmd.Operands(1), _data->Access(cmd.Operands(0)) );
                        break;

                    case Instructions::Decrement:
                        Workspace().First()--;
                        break;
                    case Instructions::DecrementMemory:
                        _data->Access(cmd.Operands(0))--;
                        break;
                    case Instructions::DecrementSet:
                        _data->Set( cmd.Operands(0), cmd.Operands(1), cmd.Operands(2), Pop()-- );
                        break;
                    case Instructions::DecrementStore:
                        _data->Set( cmd.Operands(0), Pop()-- );
                        break;

                    case Instructions::Delete:
                        _data->Delete(cmd.Operands(0));
                        break;

                    case Instructions::DefineClass:
                        _data->Insert(VirtualClass(cmd.Operands(0)));
                        break;
                    case Instructions::DefineProperty:
                        _data->Insert(cmd.Operands(0), VirtualProperty(cmd.Operands(1)));
                        break;

                    case Instructions::Get:
                        Push( _data->Get(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2)) );
                        break;

                    case Instructions::Increment:
                        Workspace().First()++;
                        break;
                    case Instructions::IncrementMemory:
                        _data->Access(cmd.Operands(0))++;
                        break;
                    case Instructions::IncrementSet:
                        _data->Set( cmd.Operands(0), cmd.Operands(1), cmd.Operands(2), Pop()++ );
                        break;
                    case Instructions::IncrementStore:
                        _data->Set( cmd.Operands(0), Pop()++ );
                        break;

                    case Instructions::Jump:
                        idx = cmd.Operands(0);
                        break;
                    case Instructions::JumpIf:
                        n1 = Pop().Compare(Pop()).Value();
                        idx = cmd.Operands(n1 + 1);
                        break;
                    case Instructions::JumpRelative:
                        idx += cmd.Operands(0);
                        break;
                    case Instructions::JumpRelativeIf:
                        v1 = Pop(); v2 = Pop();
                        n1 = v1.Compare(v2).Value();
                        idx += cmd.Operands(n1 + 1);
                        break;

                    case Instructions::Load:
                        Push( _data->Get(cmd.Operands(0)) );
                        break;
                    case Instructions::Print:
                        Console::WriteLine(_data->Find(cmd.Operands(0)));
                        break;
                    case Instructions::Remove:
                        Pop();
                        break;
                    case Instructions::Return:
                        f1 = _frames.Pop();
                        idx = f1.ReturnAddress;
                        break;
                    case Instructions::Set:
                        _data->Set(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2), Pop());
                        break;
                    case Instructions::Store:
                        _data->Set(cmd.Operands(0), Pop());
                        break;

                    case Instructions::Swap:
                        Push({ Pop(), Pop() });
                        break;
                    case Instructions::SwapMemory:
                        std::swap( _data->Access(cmd.Operands(0)), _data->Access(cmd.Operands(1)) );
                        break;

                    default:
                        break;
                }

                idx++;
            }
        }

    }
}
