#include "VirtualMachine.h"



namespace Cyclone
{
    namespace VM
    {

        /** PROPERTIES **/
        VirtualMachine& VirtualMachine::Data(const VirtualTable* value)
        {
            _data = value;
            return *this;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        VirtualMachine::VirtualMachine()
        {

        }
        VirtualMachine::~VirtualMachine()
        {

        }



        /** UTILITIES **/
        void VirtualMachine::Execute(Vector<Instructions>& commands)
        {
            auto cmd = commands.begin();
            while (cmd != commands.end())
            {
                switch (*cmd)
                {
                    case Instructions::Add:
                        Push( Pop() + Pop() );
                        break;
                    case Instructions::Call:
                        
                        //_data.Call( Pop(), )
                        break;
                    case Instructions::Compare:

                        break;
                    case Instructions::Divide:
                        Push( Pop() / Pop() );
                        break;
                    case Instructions::Get:
                        //Push( Get.Invoke(Pop(), Pop()) );
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
                    case Instructions::Return:

                        break;
                    case Instructions::Set:
                        //Set.Invoke( Pop(), Pop() );
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

                cmd++;
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