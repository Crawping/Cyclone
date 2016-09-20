/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"
#include "Math/Array.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct  Color4;
        struct  Transform;
    }

    namespace OpenGL
    {

        using namespace Utilities;
        class Texture2D;



        template<typename T>
        class OpenGLAPI IGeometric3D
        {
            public:
                virtual const Array<uint>& Indices()        const = 0;
                virtual const Array<T>& Points()            const = 0;
                virtual VertexTopologies Topology()         const = 0;
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
                virtual void Render()                       const = 0;
        };

        class OpenGLAPI IRenderableScene
        {
            public:
                virtual ~IRenderableScene() { }
                virtual void Render()                       const = 0;
        };

    }
}
