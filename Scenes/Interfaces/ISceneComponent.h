/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "Collections/List.h"



namespace Cyclone
{
    namespace 
    { 
        using namespace OpenGL;
        using namespace Utilities;
    }
    namespace OpenGL 
    { 
        class IRenderable;
        class IRenderStage;
        struct GraphicsSettings;
    }


    namespace Scenes
    {
        /// <summary> An interface that represents a collection of renderable entities associated with one or more rendering stages. </summary>
        class ISceneComponent //: public virtual IUpdatable
        {

            public:

                /** PROPERTIES **/
                virtual List<ISceneComponent&> Components()                         const = 0;
                /// <summary> Gets whether the scene component is visible in the rendered environment. </summary>
                virtual bool IsVisible()                                            const = 0;

                //virtual const string& Name()                                        const = 0;
                /// <summary> Gets the parent layer that contains the scene component. </summary>
                virtual ISceneComponent& Parent()                                   const = 0;
                /// <summary> Gets a list of all rendering stages that must be executed to display the scene component. </summary>
                virtual List<IRenderStage&> Stages()                                const = 0;
                /// <summary> Gets a structure containing all of the GPU settings needed to render the scene component. </summary>
                virtual const GraphicsSettings& Settings()                          const = 0;

                /// <summary> Sets whether the scene component is visible in the rendered environment. </summary>
                virtual ISceneComponent& IsVisible(bool value) = 0;
                /// <summary> Summarily sets all of the GPU settings needed to render the scene component. </summary>
                virtual ISceneComponent& Settings(const GraphicsSettings& value)    = 0;



                /** DESTRUCTOR **/
                virtual ~ISceneComponent() { }



                /** UTILITIES **/
                /// <summary> Determines whether the scene component contains a specific renderable entity. </summary>
                virtual bool Contains(uint entity)                                  const = 0;
                /// <summary> Adds a renderable object to the scene component. </summary>
                virtual uint Insert(const IRenderable& entity)                      = 0;

                virtual void Remove(uint entity)                                    = 0;

                virtual void Update()                                               = 0;

                //virtual void Update(const IRenderable& entity)                      = 0;

        };
    }
}
