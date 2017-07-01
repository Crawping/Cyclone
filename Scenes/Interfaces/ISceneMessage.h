/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "TypeDefinitions.h"
#include "Collections/Array.h"
#include "Enumerator.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Scenes
    {



        struct IInstruction
        {
            virtual void Execute() = 0;
        };

        


    }
}
