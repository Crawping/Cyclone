/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "Virtual/Variable.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {
            class Workspace
            {
                public:

                    


                private:

                    Vector<Variable, 255> Input;
                    Vector<Variable, 255> Local;
                    Vector<Variable, 255> Output;
                    Vector<Variable, 255> Temporary;

            };
        }
    }
}
