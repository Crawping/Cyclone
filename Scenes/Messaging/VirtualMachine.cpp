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



        /** UTILITIES **/
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

                        break;
                    case Instructions::Compare:

                        break;
                    case Instructions::Divide:
                        Push( Pop() / Pop() );
                        break;
                    case Instructions::Get:
                        Push( Get.Invoke(Pop(), Pop()) );
                        break;
                    case Instructions::Insert:

                        break;
                    case Instructions::Jump:

                        break;
                    case Instructions::Move:
                        
                        break;
                    case Instructions::Multiply:
                        Push( Pop() * Pop() );
                        break;
                    case Instructions::Remove:

                        break;
                    case Instructions::Set:
                        Set.Invoke( Pop(), Pop() );
                        break;
                    case Instructions::Subtract:
                        Push( Pop() - Pop() );
                        break;
                    case Instructions::Swap:
                        Literal v1 = Pop(), v2 = Pop();
                        Push(v1); Push(v2);
                        break;
                    case Instructions::None:
                    default:
                        break;
                }
            }
        }


        void VirtualMachine::Push(Literal parameter)
        {
            Workspace.Prepend(parameter);
        }
        Literal VirtualMachine::Pop()
        {
            Literal value(Workspace(0));
            Workspace.Remove(0);
            return value;
        }

    }
}