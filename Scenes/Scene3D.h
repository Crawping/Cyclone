/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "SceneAPI.h"
#include "VirtualMachine.h"
#include "Interfaces/IScene.h"



namespace Cyclone
{
    namespace { using namespace VM; }
    namespace Scenes
    {

        class Scene3D
        {
            public:

                /** CONSTRUCTOR **/
                SceneAPI Scene3D();

            private:

                VirtualMemory   Data;
                VirtualMachine  VM;
                
        };

    }
}
