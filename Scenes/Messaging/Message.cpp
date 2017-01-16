#include "Messaging/Message.h"



namespace Cyclone
{
    namespace Scenes
    {

        void Instruction::Execute()
        {
            switch (Command)
            {
                case Instructions::None:
                case Instructions::Add:
                case Instructions::Call:
                case Instructions::Compare:
                case Instructions::Get:
                case Instructions::Insert:
                case Instructions::Move:
                case Instructions::Remove:
                case Instructions::Set:
                case Instructions::Swap:
            }
        }
    }
}