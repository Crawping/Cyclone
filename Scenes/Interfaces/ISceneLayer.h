/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "Interfaces/ISceneComponent.h"



namespace Cyclone
{
    namespace
    {
        using namespace OpenGL;
        using namespace Utilities;
    }
    namespace OpenGL
    {
        struct GraphicsSettings;
    }



    namespace Scenes
    {
        class ISceneLayer : public IComponent
        {
            public:

                //virtual const GraphicsSettings& Settings()      const = 0;


        };
    }
}
