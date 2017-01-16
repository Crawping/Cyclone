/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Collections/ListVector.h"
#include "Messaging/Message.h"



namespace Cyclone
{
    namespace Scenes
    {
        class VirtualMachine
        {
            public:

                SceneAPI VirtualMachine();
                SceneAPI ~VirtualMachine();


                SceneAPI void Insert(Instructions command, const Vector<LiteralTypes>& parameters);
                SceneAPI void Execute(Vector<Instructions>& commands);

            private:

                ListVector<Literal> Parameters;


                void Push(Literal parameter);
                Literal Pop();

        };
    }
}
