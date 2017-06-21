/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/ITransformable3D.h"
#include "IO/Event.h"
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
        class ISpatialTransform;
        struct LineSegment3D;
        struct String;
        struct Volume;
    }
    using namespace OpenGL;
    using namespace Utilities;

    namespace Scenes
    {
        /// <summary> An interface that represents a collection of renderable entities associated with one or more rendering stages. </summary>
        class IComponent: 
            public virtual ITransformable3D
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets the bounding volume of the component in world space. </summary>
                virtual const Volume& Bounds()                              const = 0;

                virtual List<IComponent*> Children()                        const = 0;

                virtual bool IsEmpty()                                      const = 0;
                /// <summary> Gets whether the scene component is visible in the rendered environment. </summary>
                virtual bool IsVisible()                                    const = 0;

                virtual Resource<IRenderable> Model()                       const = 0;
                /// <summary> Gets the parent layer that contains the scene component. </summary>
                //virtual const IComponent* Parent()                     const = 0;
                virtual const String& Tag()                                 const = 0;

                virtual const ISpatialTransform& Transform()                const = 0;

                /// <summary> Sets whether the scene component is visible in the rendered environment. </summary>
                virtual IComponent& IsVisible(bool value)              = 0;
                //virtual IComponent& Parent(IComponent& value)     = 0;
                virtual IComponent& Tag(const String& value)           = 0;



                /** DESTRUCTOR **/
                virtual ~IComponent() { }



                /** UTILITIES **/
                //virtual 
                //virtual bool Contains(const Vector3& point)                         const = 0;
                virtual bool Contains(const IComponent* child)                  const = 0;
                virtual bool Intersects(const LineSegment3D& line)              const = 0;
                //virtual bool Intersects(const Volume& volume)                   const = 0;
                virtual IComponent* Intersection(const LineSegment3D& line)     const = 0;
                //virtual bool Intersects(const Vector<Vector3, 2>& line)             const = 0;
                /// <summary> Determines whether the scene component contains a specific renderable entity. </summary>
                //virtual bool Contains(const IRenderable& entity)                    const = 0;
                /// <summary> Adds a renderable object to the scene component. </summary>
                //virtual uint Insert(const IRenderable& entity)                      = 0;

                //virtual void Remove(const IRenderable& entity)                      = 0;

                virtual void Update()                                       = 0;


                /** EVENTS **/
                //virtual Subscription<const IComponent&, const ISpatialTransform&> 
                //    OnTransformUpdate(const ICallback<void, const IComponent&, const ISpatialTransform&>& callback) = 0;
                


            protected:

                virtual void Insert(IComponent* child)                 = 0;
                virtual void Remove(IComponent* child)                 = 0;

                virtual void ProcessTransformUpdate(const IComponent& src, const ISpatialTransform& evt) = 0;



        };
    }
}
