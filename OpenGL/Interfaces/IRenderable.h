/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/IGeometric3D.h"



namespace Cyclone
{

    /** FORWARD DECLARATIONS **/
    namespace { using namespace Utilities; }    
    namespace Utilities { struct Color4; }
    
    namespace OpenGL
    {   
        class Texture3D;
        class IRenderStage;

        /// <summary> An interface used to specify the material properties of an entity. </summary>
        class IMaterialEntity
        {
            public:
                /// <summary> Gets a pointer to the texture used to render the visible surface of a material. </summary>
                /// <remarks>
                ///     Not all materials or material-like entities will have textured associated with them. In those cases, this
                ///     method will return a <c>nullptr</c>.
                /// </remarks>
                virtual const Texture3D* Texture()			        const = 0;
                /// <summary> Gets a reference to the base color of a material. </summary>
                virtual const Color4& Color()				        const = 0;
                /// <summary> Gets a reference to the primary color of the material. </summary>
                virtual const Color4& PrimaryColor()                const = 0;
                /// <summary> Gets a reference to the secondary color of the material. </summary>
                virtual const Color4& SecondaryColor()              const = 0;

                virtual ~IMaterialEntity() { }
        };



        template <typename T> class IRenderable :
            public virtual IGeometric3D<T>,
            public virtual IMaterialEntity
        {
            public:
                /// <summary> Gets whether a renderable entity is currently visible in a scene. </summary>
                virtual bool IsVisible()                            const = 0;

                virtual ~IRenderable() { }
        };


        /// <summary> An interface that represents a generalized three-dimensional renderable object. </summary>
        /// <typeparam name="T"> The type of point object that is used to define the geometry of the object. </typeparam>
        template<typename T> class IRenderable3D : 
            public virtual IRenderable<T>
        {
            public:

                virtual const ICollection< IRenderable3D<T>* >& Components()    const = 0;
                
                virtual ~IRenderable3D() { }
        };


        class IRenderableScene
        {
            public:

                virtual const ICollection<IRenderStage*>& Stages()              const = 0;

                virtual ~IRenderableScene() { }

                virtual void Update() = 0;
        };

    }
}
