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
        struct ResourceMapping;


        class ISceneComponent : public virtual IUpdatable
        {
            public:

                virtual List<IRenderStage&> Stages()                                const = 0;
                virtual const GraphicsSettings& Settings()                          const = 0;

                virtual ISceneComponent& Settings(const GraphicsSettings& value)    = 0;

                virtual ~ISceneComponent() { }

                virtual void Insert(const ResourceMapping& resources)               = 0;
                virtual void Remove(const ResourceMapping& stage)                   = 0;

        };



        class ISceneLayer : public virtual ISceneComponent
        {
            public:

                virtual List<ISceneComponent&> Components() const = 0;

                virtual ~ISceneLayer() { }


                virtual void Insert(const string& name, ISceneComponent& component)             = 0;
                virtual void Associate(const string& name, const ResourceMapping& entity)       = 0;
                virtual void Dissociate(const string& name, const ResourceMapping& entity)      = 0;
                virtual void Remove(const string& name)                                         = 0;


                virtual ISceneComponent& operator [](const string& index)                       = 0;
                virtual const ISceneComponent& operator[](const string& index)                  const = 0;
        };

        

        class IScene : public virtual IUpdatable
        {
            public:

                virtual List<IRenderStage&> Stages() const = 0;

                virtual ~IScene() { }
        };
    }
}
