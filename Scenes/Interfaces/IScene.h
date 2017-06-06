/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "Interfaces/ISceneLayer.h"



namespace Cyclone
{
    namespace Utilities { struct ISpatialTransform; }

    namespace Scenes
    {
        class IScene : public virtual ISceneLayer
        {
            public:

                virtual const ISpatialTransform& Projection()   const = 0;
                virtual List<IRenderStage&> Stages()            const = 0;
                virtual const ISpatialTransform& View()         const = 0;

        };
    }
}
