/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Messaging/Literal.h"
#include "Scripting/VirtualProperty.h"



namespace Cyclone
{
    namespace Scenes
    {

        class VirtualTable
        {
            public:


                /** UTILITIES **/
                SceneAPI void Insert(const Literal& value);

                

            private:

                
                BST<uint, VirtualClass>     Objects;
                BST<uint, VirtualFunction>  Functions;

        };

    }
}
