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
                        Push( Pop() + Pop() );
                        break;

                    case Instructions::Call:

                    case Instructions::Compare:

                    case Instructions::Divide:
                        Push( Pop() / Pop() );
                        break;
                    case Instructions::Get:
                        Push( Get.Invoke(Pop(), Pop()) );
                        break;
                    case Instructions::Insert:

                    case Instructions::Jump:

                    case Instructions::Move:
                        
                    case Instructions::Multiply:
                        Push( Pop() * Pop() );
                        break;
                    case Instructions::Remove:

                    case Instructions::Set:
                        Set.Invoke( Pop(), Pop() );
                        break;
                    case Instructions::Subtract:
                        Push( Pop() - Pop() );
                        break;
                    case Instructions::Swap:

                    case Instructions::None:
                    default:
                        break;
                }
            }
        }


        void VirtualMachine::Push(Literal parameter)
        {
            Parameters.Prepend(parameter);
        }
        Literal VirtualMachine::Pop()
        {
            Literal parameter(Parameters(0));
            Parameters.Remove(0);
            return parameter;
        }

    }
}