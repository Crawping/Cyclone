#include "VirtualMachine.h"
#include "IO/Console.h"



namespace Cyclone
{
    namespace Virtual
    {
        namespace Virtual
        {

            /** PROPERTIES **/
            //VirtualMachine& VirtualMachine::Data(Memory* value)
            //{
            //    _data = value;
            //    return *this;
            //}



            ///** CONSTRUCTOR & DESTRUCTOR **/
            //VirtualMachine::VirtualMachine() :
            //    _data(nullptr)
            //{

            //}
            //VirtualMachine::~VirtualMachine()
            //{

            //}



            ///** UTILITIES **/
            //void VirtualMachine::Abort()    { Interrupt = Instructions::Abort; }
            //void VirtualMachine::Pause()    { Interrupt = Instructions::Pause; }
            //void VirtualMachine::Resume()   { Interrupt = Instructions::None; }

            //void VirtualMachine::Execute(const Vector<Instruction>& instructions)
            //{
            //    uint idx = 0;
            //    Variable v1, v2, v3, v4;
            //    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
            //
            //    StackFrame f1 = { instructions.Count(), &instructions, { } };
            //    _frames.Push(f1);

            //    while (idx < f1.Instructions->Count())
            //    {
            //        if (Interrupt == Instructions::Return || Interrupt == Instructions::Abort)
            //            return Resume();
            //        else if (Interrupt == Instructions::Pause)
            //            continue;

            //        const auto& cmd = f1.Instructions->operator ()(idx);
            //        switch (cmd.Command)
            //        {
            //            case Instructions::Add:
            //            case Instructions::And:
            //            case Instructions::Divide:
            //            case Instructions::Multiply:
            //            case Instructions::Negate:
            //            case Instructions::Not:
            //            case Instructions::Or:
            //            case Instructions::Subtract:
            //            case Instructions::Xor:
            //                Push( Variable::Calculate(cmd.Command, Pop(), Pop()) );
            //                break;

            //            case Instructions::AddVariables:
            //            case Instructions::AndVariables:
            //            case Instructions::DivideVariables:
            //            case Instructions::MultiplyVariables:
            //            case Instructions::NegateVariable:
            //            case Instructions::NotVariable:
            //            case Instructions::OrVariables:
            //            case Instructions::SubtractVariables:
            //            case Instructions::XorVariables:
            //                v1 = _data->GetVariable(cmd.Operands(1)); 
            //                v2 = _data->GetVariable(cmd.Operands(2));
            //                _data->SetVariable( cmd.Operands(0), Variable::Calculate(cmd.Command - 2, v1, v2) );
            //                break;

            //            case Instructions::Abort:
            //                return;

            //            case Instructions::Call:
            //                _frames.Push(f1);
            //                f1 = { idx, &(_data->Call(Pop())), { } };
            //                idx = cmd.Operands(0);
            //                break;
            //            case Instructions::CallFunction:
            //                _frames.Push(f1);
            //                f1 = { idx, &(_data->CallFunction(cmd.Operands(1))), { } };
            //                idx = 0;
            //                break;
            //            case Instructions::CallMethod:
            //                _frames.Push(f1);
            //                f1 = { idx, &(_data->CallMethod(cmd.Operands(1), cmd.Operands(2))), { } };
            //                idx = 0;
            //                break;
            //            case Instructions::CallRelative:
            //                _frames.Push(f1);
            //                f1 = { idx, &instructions, { } };
            //                idx += cmd.Operands(0);
            //                break;

            //            case Instructions::Cast:
            //                Push( Pop().Cast(cmd.Operands(0)) );
            //                break;

            //            case Instructions::Compare:
            //                Push( Pop().Compare(Pop()) );
            //                break;
            //            case Instructions::CompareArrays:

            //                break;
            //            case Instructions::CompareVariables:
            //                v1 = _data->GetVariable(cmd.Operands(1));
            //                _data->SetVariable( cmd.Operands(0), v1.Compare(_data->GetVariable(cmd.Operands(2))) );
            //                break;

            //            case Instructions::Copy:
            //                Push(Workspace().First());
            //                break;
            //            case Instructions::CopyArray:
            //                _data->CopyArray( cmd.Operands(0), cmd.Operands(1) );
            //                break;
            //            case Instructions::CopyObject:

            //                break;
            //            case Instructions::CopyVariable:
            //                _data->SetVariable( cmd.Operands(1), _data->GetVariable(cmd.Operands(0)) );
            //                break;

            //            case Instructions::Decrement:
            //                Workspace().First()--;
            //                break;
            //            case Instructions::DecrementObject:
            //                _data->GetObject(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2))--;
            //                break;
            //            case Instructions::DecrementVariable:
            //                _data->GetVariable(cmd.Operands(0))--;
            //                break;

            //            case Instructions::Delete:
            //                _data->Delete(Pop());
            //                break;
            //            case Instructions::DeleteArray:
            //                _data->DeleteArray(cmd.Operands(0));
            //                break;
            //            case Instructions::DeleteObject:
            //                _data->DeleteObject(cmd.Operands(0), cmd.Operands(1));
            //                break;
            //            case Instructions::DeleteStructure:

            //                break;
            //            case Instructions::DeleteVariable:
            //                _data->DeleteVariable(cmd.Operands(0));
            //                break;

            //            case Instructions::Get:
            //                Push( _data->Get(Pop(), Pop()) );
            //                break;
            //            case Instructions::GetArray:
            //                Push( _data->GetArray(cmd.Operands(0), cmd.Operands(1)) );
            //                break;
            //            case Instructions::GetObject:
            //                Push( _data->GetObject(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2)) );
            //                break;
            //            case Instructions::GetVariable:
            //                Push( _data->GetVariable(cmd.Operands(0)) );
            //                break;

            //            case Instructions::Increment:
            //                Workspace().First()++;
            //                break;
            //            case Instructions::IncrementObject:
            //                _data->GetObject(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2))++;
            //                break;
            //            case Instructions::IncrementVariable:
            //                _data->GetVariable(cmd.Operands(0))++;
            //                break;

            //            case Instructions::Jump:
            //                idx = cmd.Operands(0);
            //                break;
            //            case Instructions::JumpIf:
            //                n1 = Pop().Compare(Pop()).Value();
            //                idx = cmd.Operands(n1 + 1);
            //                break;
            //            case Instructions::JumpRelative:
            //                idx += cmd.Operands(0);
            //                break;
            //            case Instructions::JumpRelativeIf:
            //                v1 = Pop(); v2 = Pop();
            //                n1 = v1.Compare(v2).Value();
            //                idx += cmd.Operands(n1 + 1);
            //                break;

            //            case Instructions::Load:
            //                Push( _data->Get(Pop(), Pop()) );
            //                break;
            //            case Instructions::LoadArray:
            //                Push( Variable(ReferenceTypes::Array, cmd.Operands(0)) );
            //                break;
            //            case Instructions::LoadObject:
            //                Push( Variable(ReferenceTypes::Object, cmd.Operands(0), cmd.Operands(1)) );
            //                break;

            //            case Instructions::Print:
            //                Console::WriteLine(_data->Find(cmd.Operands(0)));
            //                break;
            //            case Instructions::Remove:
            //                Pop();
            //                break;
            //            case Instructions::Return:
            //                idx = f1.Index;
            //                f1 = _frames.Pop();
            //                break;

            //            case Instructions::Set:
            //                _data->Set( Pop(), Pop(), Pop() );
            //                break;
            //            case Instructions::SetArray:
            //                _data->SetArray(cmd.Operands(0), cmd.Operands(1), Pop());
            //                break;
            //            case Instructions::SetObject:
            //                _data->SetObject(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2), Pop());
            //                break;
            //            case Instructions::SetVariable:
            //                _data->SetVariable(cmd.Operands(0), Pop());
            //                break;

            //            case Instructions::Swap:
            //                Push({ Pop(), Pop() });
            //                break;
            //            case Instructions::SwapArray:

            //                break;
            //            case Instructions::SwapVariables:
            //                std::swap( _data->GetVariable(cmd.Operands(0)), _data->GetVariable(cmd.Operands(1)) );
            //                break;

            //            default:
            //                break;
            //        }

            //        idx++;
            //    }
            //}

        }
    }
}
