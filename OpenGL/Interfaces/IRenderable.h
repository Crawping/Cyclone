/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"
#include "Collections/List.h"
#include "Collections/Vector.h"



namespace Cyclone
{

    /** FORWARD DECLARATIONS **/
    namespace Platform { class GPU; }
    namespace Utilities
    {
        struct Color4;
        struct ITransformation3D;
        struct Volume;
    }


    namespace OpenGL
    {
        using namespace Platform;
        using namespace Utilities;
        class Texture3D;
        class IRenderStage;



        /// <summary> An interface used to specify the properties of any three-dimensional geometric shape. </summary>
        /// <typeparam name="T"> The type of point object used to define a 3D geometric shape. </typeparam>
        template<typename T>
        class IGeometric3D
        {
            public:
                /// <summary> Gets the bounding volume of the 3D geometric shape. </summary>
                virtual const Volume& Bounds()                      const = 0;
                /// <summary> Gets an array of indices that define the order in which <see cref="Points"/> is rendered. </summary>
                /// <remarks>
                ///     Not all geometry will be composed of indexable control points or vertices. In those cases, this method will
                ///     return an empty array.
                /// </remarks>
                virtual const Vector<uint>& Indices()               const = 0;
                /// <summary> Gets an array of points that define a 3D geometric shape. </summary>
                /// <remarks>
                ///     This property is meant to be interpretted in one of a few possible ways. Most commonly, the name 'Points' will
                ///     refer to the array of vertices that make up the standard polygons, points, and lines that OpenGL is well-known
                ///     for rendering. However, it may also refer to the control points of either a 3D patch object or 2D path object
                ///     (note the lack of a 'c' in the latter; though similarly named, the two are very different things).
                /// </remarks>
                virtual const Vector<T>& Points()                   const = 0;
                /// <summary> Gets an enumerator that represents the type of primitive geometry defined by the <see cref="Points"/> property. </summary>
                virtual VertexTopologies Topology()                 const = 0;
                /// <summary> Gets a transformation data structure representing the orientation, position, and scaling of 3D geometric shape. </summary>
                virtual const ITransformation3D& World()            const = 0;

                virtual ~IGeometric3D() { }
        };



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

                virtual ~IMaterialEntity() { }
        };



        /// <summary> An interface that represents a generalized three-dimensional renderable object. </summary>
        /// <typeparam name="T"> The type of point object that is used to define the geometry of the object. </typeparam>
        template<typename T>
        class IRenderable3D :
            public virtual IGeometric3D<T>,
            public virtual IMaterialEntity
        {
            public:

                virtual const ICollection< IRenderable3D<T>* >& Components()    const = 0;

                /// <summary> Gets whether a renderable entity is currently visible in a scene. </summary>
                virtual bool IsVisible()                                        const = 0;
                virtual ~IRenderable3D() { }
        };



        template<typename T> class IRenderable2D :
            public virtual IRenderable3D<T>
        {
            public:
                virtual ~IRenderable2D() { }
                virtual void Render()                               const = 0;
        };

        class IRenderableScene
        {
            public:

                virtual List<IRenderStage*> Stages()                const = 0;

                virtual ~IRenderableScene() { }
                //virtual void Render(GPU* gpu)                       const = 0;
        };

    }
}
