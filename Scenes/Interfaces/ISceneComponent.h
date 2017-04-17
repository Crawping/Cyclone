/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/ITransformable.h"



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
    namespace Utilities
    {
        struct Volume;
    }


    namespace Scenes
    {
        /// <summary> An interface that represents a collection of renderable entities associated with one or more rendering stages. </summary>
        class ISceneComponent //: public virtual ITransformable
        {

            public:

                /** PROPERTIES **/
                virtual const Volume& Bounds()                                      const = 0;

                virtual List<ISceneComponent&> Children()                           const = 0;
                /// <summary> Gets whether the scene component is visible in the rendered environment. </summary>
                virtual bool IsVisible()                                            const = 0;

                virtual const IRenderable* Model()                                  const = 0;
                /// <summary> Gets the parent layer that contains the scene component. </summary>
                virtual const ISceneComponent& Parent()                             const = 0;

                virtual const string& Tag()                                         const = 0;

                virtual const ISpatialTransform& Transformation()                   const = 0;

                /// <summary> Sets whether the scene component is visible in the rendered environment. </summary>
                virtual ISceneComponent& IsVisible(bool value)                      = 0;



                /** DESTRUCTOR **/
                virtual ~ISceneComponent() { }



                /** UTILITIES **/
                virtual bool Contains(const Vector3& point)                         const = 0;
                virtual bool Intersects(const Vector<Vector3, 2>& line)             const = 0;
                /// <summary> Determines whether the scene component contains a specific renderable entity. </summary>
                //virtual bool Contains(const IRenderable& entity)                    const = 0;
                /// <summary> Adds a renderable object to the scene component. </summary>
                //virtual uint Insert(const IRenderable& entity)                      = 0;

                //virtual void Remove(const IRenderable& entity)                      = 0;

                virtual void Update()                                               = 0;

        };
    }
}
