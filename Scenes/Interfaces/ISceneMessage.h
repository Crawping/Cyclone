/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "TypeDefinitions.h"
#include "Collections/Vector.h"
#include "Enumerator.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Scenes
    {

        struct Instructions : public Enumerator
        {
            enum Types
            {
                None        = 0,
                Add         = 1,
                Call        = 2,
                Compare     = 3,
                Divide      = 4,
                Get         = 5,
                Insert      = 6,
                Jump        = 7,
                Move        = 8,
                Multiply    = 9,
                Remove      = 10,
                Set         = 11,
                Subtract    = 12,
                Swap        = 13,
            };

            constexpr Instructions(enum Types t = None) : Enumerator((int)t) { }
        };

        struct IInstruction
        {
            virtual void Execute() = 0;
        };

        


    }
}
