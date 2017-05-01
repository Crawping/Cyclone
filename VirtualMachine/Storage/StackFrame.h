/* CHANGELOG
 * Written by Josh Grooms on 20170428
 */

#pragma once
#include "Collections/Vector.h"
#include "Storage/Address.h"
#include "Primitives/Number.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            struct RegisterFrame
            {
                Vector<Array, 256>      Arrays;
                Vector<Class, 256>      Classes;
                Vector<Function, 256>   Functions;
                Vector<Number, 256>     Numbers;
                Vector<Reference, 256>  References;

                Vector<Reference, 256>  Input;
                Vector<Reference, 256>  Output;

                /*template<typename T = Variable>
                VMAPI T& Access(Reference address);*/
                VMAPI Reference& Access(Reference location);

                void Reset()
                {
                    Reference r;
                    Input.Fill(r);
                    Output.Fill(r);
                }
            };

            struct StackFrame
            {
                RegisterFrame   Registers;
                uint            ReturnIndex;
            };

        }
    }
}
