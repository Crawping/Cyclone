/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/IUpdatable.h"
#include <string>



namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace OpenGL
    {
        class IRenderStage;


        class ISceneComponent : public virtual IUpdatable
        {
            public:

                virtual List<ISceneComponent&> Components() const = 0;
                virtual const string& Name()                const = 0;
                virtual const GraphicsSettings* Settings()  const = 0;
                virtual List<IRenderStage&> Stages()        const = 0;


                virtual ~ISceneComponent() { }
        };


        class ISceneLayer : public virtual IUpdatable
        {
            public:

                virtual const string& Name()                const = 0;
                virtual List<ISceneComponent&> Stages()     const = 0;

                virtual ~ISceneLayer() { }
        };

        

        class IScene : public virtual IUpdatable
        {
            public:

                virtual List<ISceneLayer&> Layers() const = 0;

                virtual ~IScene() { }
        };
    }
}
