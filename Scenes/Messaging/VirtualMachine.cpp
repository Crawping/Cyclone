#include "Messaging/VirtualMachine.h"



namespace Cyclone
{
    namespace Scenes
    {



        VirtualMachine::VirtualMachine()
        {

        }
        VirtualMachine::~VirtualMachine()
        {

        }


        void VirtualMachine::Execute(Vector<Instructions>& commands)
        {
            for (auto cmd : commands)
            {
                switch (cmd)
                {
                    case Instructions::Add:

                        Literal v1 = Pop(), v2 = Pop();
                        if (v1.Type == v2.Type)
                            Push( Pop() + Pop() );  
                    case Instructions::Call:
                    case Instructions::Compare:
                    case Instructions::Divide:
                    case Instructions::Get:
                    case Instructions::Insert:
                    case Instructions::Jump:
                    case Instructions::Move:
                    case Instructions::Multiply:
                    case Instructions::Remove:
                    case Instructions::Set:
                    case Instructions::Subtract:

                    case Instructions::Swap:

                    case Instructions::None:
                    default:
                }
            }
        }


        void VirtualMachine::Push(Literal parameter)
        {

        }
        Literal VirtualMachine::Pop()
        {
            Literal parameter(Parameters(0));
            Parameters.Remove(0);
            return parameter;
        }

    }
}