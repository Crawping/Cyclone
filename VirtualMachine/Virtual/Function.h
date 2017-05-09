/* CHANGELOG
 * Written by Josh Grooms on 20170212
 */

#pragma once
#include "Collections/Vector.h"
#include "Execution/Instructions.h"



namespace Cyclone
{
    namespace Virtual
    {
        using namespace Utilities;

        class Function
        {
            public:

                /** PROPERTIES **/
                const Vector<Instruction>& Logic()  const { return _logic; }

                VMAPI Function& Logic(const ICollection<Instruction>& value);

            private:

                /** DATA **/
                Vector<Instruction>     _logic;

        };

    }
}
