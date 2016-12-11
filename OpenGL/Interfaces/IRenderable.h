/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/IGeometric3D.h"



namespace Cyclone
{
    namespace OpenGL
    {        
        class IMaterial;
        class IRenderStage;

        template <typename T> 
        class IRenderable : public virtual IGeometric3D<T>
        {
            public:
                /// <summary> Gets whether a renderable entity is currently visible in a scene. </summary>
                virtual bool IsVisible()                            const = 0;
                virtual const IMaterial& Material()                 const = 0;

                virtual ~IRenderable() { }
        };


        /// <summary> An interface that represents a generalized three-dimensional renderable object. </summary>
        /// <typeparam name="T"> The type of point object that is used to define the geometry of the object. </typeparam>
        template<typename T> 
        class IRenderable3D : public virtual IRenderable<T>
        {
            public:

                virtual const ICollection< IRenderable3D<T>* >& Components()    const = 0;
                
                virtual ~IRenderable3D() { }
        };


        class IRenderableScene
        {
            public:

                virtual List<IRenderStage*> Stages() const = 0;

                virtual ~IRenderableScene() { }

                virtual void Update() = 0;
        };

    }
}
