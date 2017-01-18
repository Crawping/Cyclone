/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Event.h"
#include "Collections/ListVector.h"
#include "Storage/VirtualTable.h"



namespace Cyclone
{
    namespace VM
    {
        class VirtualMachine
        {
            public:

                /** PROPERTIES **/
                const VirtualTable* Data() const { return _data; }

                VMAPI VirtualMachine& Data(const VirtualTable* value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                VMAPI VirtualMachine();
                VMAPI ~VirtualMachine();



                /** UTILITIES **/
                void Insert(const Vector<Literal>& values)  { Workspace.Prepend(values); }
                void Clear()                                { Workspace.Clear(); }
                VMAPI void Execute(Vector<Instructions>& commands);
                VMAPI void Pause();
                VMAPI void Resume();

            private:

                const VirtualTable* _data;
                ListVector<Literal> Workspace;



                /** UTILITIES **/
                void Push(Literal parameter);
                Literal Pop();

        };
    }
}
