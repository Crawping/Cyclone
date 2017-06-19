/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/ITransformable3D.h"
#include "Resources/Resource.h"



namespace Cyclone
{
    namespace OpenGL 
    { 
        class IRenderable;
        class IRenderStage;
    }
    namespace Utilities
    {
        struct ISpatialTransform;
        struct LineSegment;
        struct String;
        struct Volume;
    }
    using namespace OpenGL;
    using namespace Utilities;

    namespace Scenes
    {
        /// <summary> An interface that represents a collection of renderable entities associated with one or more rendering stages. </summary>
        class ISceneComponent: 
            public virtual ITransformable3D
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets the bounding volume of the component in world space. </summary>
                virtual const Volume& Bounds()                              const = 0;

                virtual List<ISceneComponent*> Children()                   const = 0;
                /// <summary> Gets whether the scene component is visible in the rendered environment. </summary>
                virtual bool IsVisible()                                    const = 0;

                virtual Resource<IRenderable> Model()                       const = 0;
                /// <summary> Gets the parent layer that contains the scene component. </summary>
                virtual const ISceneComponent& Parent()                     const = 0;
                virtual const String& Tag()                                 const = 0;
                virtual const ISpatialTransform& Transform()                const = 0;

                /// <summary> Sets whether the scene component is visible in the rendered environment. </summary>
                virtual ISceneComponent& IsVisible(bool value)              = 0;
                virtual ISceneComponent& Parent(ISceneComponent& value)     = 0;
                virtual ISceneComponent& Tag(const String& value)           = 0;



                /** DESTRUCTOR **/
                virtual ~ISceneComponent() { }



                /** UTILITIES **/
                //virtual bool Contains(const Vector3& point)                         const = 0;
                virtual bool Contains(const ISceneComponent* child)             const = 0;
                virtual bool Intersects(const LineSegment& line)                const = 0;
                //virtual bool Intersects(const Volume& volume)                   const = 0;
                virtual ISceneComponent* Intersection(const LineSegment& line)  const = 0;
                //virtual bool Intersects(const Vector<Vector3, 2>& line)             const = 0;
                /// <summary> Determines whether the scene component contains a specific renderable entity. </summary>
                //virtual bool Contains(const IRenderable& entity)                    const = 0;
                /// <summary> Adds a renderable object to the scene component. </summary>
                //virtual uint Insert(const IRenderable& entity)                      = 0;

                //virtual void Remove(const IRenderable& entity)                      = 0;

                virtual void Update()                                       = 0;


            protected:

                virtual void Insert(ISceneComponent* child)                 = 0;
                virtual void Remove(ISceneComponent* child)                 = 0;



        };
    }
}
