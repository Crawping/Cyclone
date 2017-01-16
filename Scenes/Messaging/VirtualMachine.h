/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Event.h"
#include "Collections/ListVector.h"
#include "Messaging/Message.h"



namespace Cyclone
{
    namespace Scenes
    {
        class VirtualMachine
        {
            public:

                /** DELEGATES **/
                Function<Literal, Literal, Literal> Get;
                Function<void, Literal, Literal>    Set;



                /** CONSTRUCTOR & DESTRUCTOR **/
                SceneAPI VirtualMachine();
                SceneAPI ~VirtualMachine();



                /** UTILITIES **/
                SceneAPI void Insert(Instructions command, const Vector<LiteralTypes>& parameters);
                SceneAPI void Execute(Vector<Instructions>& commands);

            private:

                ListVector<Literal> Parameters;


                void Push(Literal parameter);
                Literal Pop();

        };
    }
}
