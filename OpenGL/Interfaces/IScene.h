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

        /** FORWARD DECLARATIONS **/
        class IRenderable;
        class IRenderStage;
        class ISceneLayer;
        struct BufferBinding;
        struct GraphicsSettings;
        struct ResourceMapping;




        /// <summary> An interface that represents elements of a renderable scene with common rendering settings. </summary>
        class ISceneComponent : public virtual IUpdatable
        {

            public:
            
                /** PROPERTIES **/
                virtual bool IsVisible()                                            const = 0;
                virtual const string& Name()                                        const = 0;
                virtual ISceneLayer& Parent()                                       const = 0;
                virtual List<IRenderStage&> Stages()                                const = 0;
                virtual const GraphicsSettings& Settings()                          const = 0;

                virtual ISceneComponent& IsVisible(bool value)                      = 0;
                virtual ISceneComponent& Settings(const GraphicsSettings& value)    = 0;

                /** DESTRUCTOR **/
                virtual ~ISceneComponent() { }

                /** UTILITIES **/
                virtual bool Contains(const IRenderable& entity)                    const = 0;
                virtual void Insert(const IRenderable& entity)                      = 0;
                virtual void Update()                                               = 0;
                virtual void Update(const IRenderable& entity)                      = 0;

                virtual ResourceMapping& Register(const IRenderable& entity)        = 0;

        };


        /// <summary> An interface that represents a scene component that can also contain other scene components. </summary>
        class ISceneLayer : public virtual ISceneComponent
        {
            public:
                virtual List<BufferBinding> Buffers()                                           const = 0;
                virtual List<ISceneComponent&> Components()                                     const = 0;

                virtual ~ISceneLayer() { }

                virtual void Insert(const string& name, ISceneComponent& component)             = 0;
                virtual void Remove(const string& name)                                         = 0;
        };

        

        class IScene : public virtual ISceneLayer
        {
            public:

                virtual ~IScene() { }
        };
    }
}
