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

                virtual const string& Name()                                        const = 0;
                virtual List<IRenderStage&> Stages()                                const = 0;

                virtual ~ISceneComponent() { }

                virtual void Add(const string& name, const IRenderStage& stage)           = 0;
                virtual void Add(const string& stage, const ResourceMapping& entity)      = 0;
                virtual void Remove(const string& name, const IRenderStage& stage)        = 0;
                virtual void Remove(const string& stage, const ResourceMapping& entity)   = 0;

                virtual IRenderStage& operator [](const string& index)                    = 0;
                virtual const IRenderStage& operator [](const string& index)        const = 0;

        };



        class ISceneLayer : public virtual IUpdatable
        {
            public:

                virtual List<ISceneComponent&> Components() const = 0;
                virtual const string& Name()                const = 0;

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
