#include "VirtualMachine.h"



namespace Cyclone
{
    namespace VM
    {

        /** PROPERTIES **/
        VirtualMachine& VirtualMachine::Data(VirtualTable* value)
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
        /*void Insert(const Vec)*/
        void VirtualMachine::Execute(const Vector<Instruction>& instructions)
        {
            uint idx = 0;
            Literal v1, v2, v3, v4;

            while (idx < instructions.Count())
            {
                if (Interrupt == Instructions::Return)
                    break;

                const auto& cmd = instructions(idx);
                switch (cmd.Command)
                {
                    case Instructions::Add:
                    case Instructions::And:
                    case Instructions::Divide:
                    case Instructions::Multiply:
                    case Instructions::Negate:
                    case Instructions::Or:
                    case Instructions::Subtract:
                    case Instructions::Xor:
                        Push( Literal::Calculate(cmd.Command, Pop(), Pop()) );
                        break;

                    case Instructions::Call:
                        CallStack.Push(idx);
                        idx = cmd.Operands(0);
                        break;
                    case Instructions::Cast:
                        Push( Pop().Cast(cmd.Operands(0)) );
                        break;
                    case Instructions::Compare:
                        Push( Pop().Compare(Pop()) );
                        break;
                    case Instructions::Decrement:
                        Workspace.First().Value--;
                        break;
                    case Instructions::Delete:
                        _data->Delete(cmd.Operands(0));
                        break;
                    case Instructions::Get:
                        Push( _data->Get(cmd.Operands(0), cmd.Operands(1), cmd.Operands(2)) );
                        break;
                    case Instructions::Increment:
                        Workspace.First().Value++;
                        break;
                    case Instructions::Jump:
                        idx = cmd.Operands(0);
                        break;
                    case Instructions::JumpIf:
                        idx = (Pop() == Pop()) ? cmd.Operands(0) : cmd.Operands(1);
                        break;
                    case Instructions::Load:
                        Push( _data->Get(cmd.Operands(0)) );
                        break;
                    case Instructions::Remove:
                        Pop();
                        break;
                    case Instructions::Return:
                        idx = CallStack.Pop();
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

                    default:
                        break;
                }

                idx++;
            }
        }
        void VirtualMachine::Pause() { Interrupt = Instructions::Return; }
        void VirtualMachine::Resume() { Interrupt = Instructions::None; }
    }
}
