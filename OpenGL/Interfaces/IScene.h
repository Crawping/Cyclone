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

        /// <summary> An interface that represents a collection of renderable entities associated with one or more rendering stages. </summary>
        class ISceneComponent : public virtual IUpdatable
        {

            public:
            
                /** PROPERTIES **/
                /// <summary> Gets whether the scene component is visible in the rendered environment. </summary>
                virtual bool IsVisible()                                            const = 0;

                virtual const string& Name()                                        const = 0;
                /// <summary> Gets the parent layer that contains the scene component. </summary>
                virtual ISceneLayer& Parent()                                       const = 0;
                /// <summary> Gets a list of all rendering stages that must be executed to display the scene component. </summary>
                virtual List<IRenderStage&> Stages()                                const = 0;
                /// <summary> Gets a structure containing all of the GPU settings needed to render the scene component. </summary>
                virtual const GraphicsSettings& Settings()                          const = 0;

                /// <summary> Sets whether the scene component is visible in the rendered environment. </summary>
                virtual ISceneComponent& IsVisible(bool value)                      = 0;
                /// <summary> Summarily sets all of the GPU settings needed to render the scene component. </summary>
                virtual ISceneComponent& Settings(const GraphicsSettings& value)    = 0;



                /** DESTRUCTOR **/
                virtual ~ISceneComponent() { }



                /** UTILITIES **/
                /// <summary> Determines whether the scene component contains a specific renderable entity. </summary>
                virtual bool Contains(const IRenderable& entity)                    const = 0;
                /// <summary> Adds a renderable object to the scene component. </summary>
                virtual void Insert(const IRenderable& entity)                      = 0;

                virtual void Update()                                               = 0;

                virtual void Update(const IRenderable& entity)                      = 0;

                virtual ResourceMapping& Register(const IRenderable& entity)        = 0;

        };


        /// <summary> An interface that represents a collection of scene components. </summary>
        class ISceneLayer : public virtual ISceneComponent
        {
            public:

                virtual List<BufferBinding> Buffers()                               const = 0;
                /// <summary> Gets a list of all components that are stored within the scene layer. </summary>
                virtual List<ISceneComponent&> Components()                         const = 0;

                virtual ~ISceneLayer() { }

                virtual void Insert(const string& name, ISceneComponent& component) = 0;
                virtual void Remove(const string& name)                             = 0;
        };

        

        class IScene : public virtual ISceneLayer
        {
            public:

                virtual ~IScene() { }
        };
    }
}
