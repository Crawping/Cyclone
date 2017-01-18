/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Event.h"
#include "Collections/ListVector.h"
#include "Messaging/Literal.h"
#include "Scripting/VirtualTable.h"



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



                /** PROPERTIES **/
                const VirtualTable& Data() const { return _data; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                SceneAPI VirtualMachine();
                SceneAPI ~VirtualMachine();



                /** UTILITIES **/
                void Insert(const Vector<Literal>& values)  { Workspace.Prepend(values); }
                void Clear()                                { Workspace.Clear(); }
                SceneAPI void Execute(Vector<Instructions>& commands);

            private:

                ListVector<Literal> Workspace;

                VirtualTable _data;

                void Push(Literal parameter);
                Literal Pop();

        };
    }
}
