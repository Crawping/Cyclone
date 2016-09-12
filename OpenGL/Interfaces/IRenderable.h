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

        struct  PerEntity;
        class   Texture2D;
        namespace Vertex { struct Standard; }
        using namespace Utilities;



        class OpenGLAPI IGeometricEntity
        {
	        public:

		        virtual ~IGeometricEntity() { }

                virtual const Array<uint>& Indices()                const = 0;
		        virtual const Array<Vertex::Standard>& Vertices()	const = 0;
		        virtual const Transform& World()			        const = 0;
		        virtual VertexTopologies Topology()			        const = 0;
        };



        class OpenGLAPI IMaterialEntity
        {
	        public:
		        virtual ~IMaterialEntity() { }

		        virtual const Texture2D* Texture()			const = 0;
		        virtual const Color4& Color()				const = 0;
        };



        class OpenGLAPI IRenderableEntity :
	        public IGeometricEntity,
	        public IMaterialEntity
        {
	        public:
		        virtual ~IRenderableEntity() { }

		        virtual bool IsVisible()					const = 0;
        };

    }
}
