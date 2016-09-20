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
        struct  PerEntity;
        class   Texture2D;
        namespace Vertex { struct Standard; }



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
                virtual ~IMaterialEntity() { }

                virtual const Texture2D* Texture()			const = 0;
                virtual const Color4& Color()				const = 0;
        };



        template<typename T>
        class OpenGLAPI IRenderable3D :
            public IGeometric3D<T>,
            public IMaterialEntity
        {
            public:
                virtual bool IsVisible()                    const = 0;
                virtual ~IRenderable3D() { }
        };

        template<typename T>
        class OpenGLAPI IRenderable2D :
            public IRenderable3D<T>
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

        template<typename T>
        class OpenGLAPI IRenderablePath :
            public IRenderable3D<T>,
            public IRenderableScene
        {
            
        };

    }
}
