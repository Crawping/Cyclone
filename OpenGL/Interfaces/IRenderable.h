/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"
#include "Math/Array.h"



namespace Cyclone
{
    namespace Platform { class GPU; }
    namespace Utilities
    {
        struct  Color4;
        struct  Transform;
    }


    namespace OpenGL
    {

        using namespace Platform;
        using namespace Utilities;
        class Texture2D;


        /// <summary> An interface used to specify the properties of any three-dimensional geometric shape. </summary>
        template<typename T>
        class OpenGLAPI IGeometric3D
        {
            public:
                /// <summary> Gets an array of indices that define the order in which <see cref="Points"/> is rendered. </summary>
                virtual const Array<uint>& Indices()        const = 0;
                /// <summary> Gets an array of points that define a 3D geometric shape. </summary>
                /// <remarks>
                ///     This property is meant to be interpretted in one of a few possible ways. Most commonly, the name 'Points' will 
                ///     refer to the array of vertices that make up the standard polygons, points, and lines that OpenGL is well-known 
                ///     for rendering. However, it may also refer to the control points of either a 3D patch object or 2D path object 
                ///     (note the lack of a 'c' in the latter; though similarly named, the two are very different things). 
                /// </remarks>
                virtual const Array<T>& Points()            const = 0;
                /// <summary> Gets an enumerator that represents the type of primitive geometry defined by the <see cref="Points"/> property. </summary>
                virtual VertexTopologies Topology()         const = 0;
                /// <summary> Gets a transformation data structure representing the orientation, position, and scaling of 3D geometric shape. </summary>
                virtual const Transform& World()            const = 0;

                virtual ~IGeometric3D() { }
        };

        class OpenGLAPI IMaterialEntity
        {
            public:
                virtual const Texture2D* Texture()			const = 0;
                virtual const Color4& Color()				const = 0;

                virtual ~IMaterialEntity() { }
        };

        template<typename T>
        class OpenGLAPI IRenderable3D :
            public virtual IGeometric3D<T>,
            public virtual IMaterialEntity
        {
            public:
                virtual bool IsVisible()                    const = 0;
                virtual ~IRenderable3D() { }
        };

        template<typename T>
        class OpenGLAPI IRenderable2D :
            public virtual IRenderable3D<T>
        {
            public:
                virtual ~IRenderable2D() { }
                virtual void Render(const GPU* gpu)         const = 0;
        };

        class OpenGLAPI IRenderableScene
        {
            public:
                virtual ~IRenderableScene() { }
                virtual void Render(const GPU* gpu)         const = 0;
        };

    }
}
