/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "EnumerationsGL.h"
#include "Interfaces/IRenderStage.h"
#include <map>



namespace Cyclone
{
    namespace OpenGL
    {
        class IGraphicsBuffer;
        struct GraphicsSettings;

        struct RenderStage3D : public IRenderStage
        {
            public:

                const IGraphicsBuffer* Data()                               const override { return _data; }
                const GraphicsSettings* Settings()                          const override { return _settings; }
                VertexTopologies Topology()                                 const override { return _topology; }

                RenderStage3D& Data(const IGraphicsBuffer* value)           { _data = value; return *this; }
                RenderStage3D& Settings(const GraphicsSettings* value)      { _settings = value; return *this; }
                RenderStage3D& Topology(VertexTopologies value)             { _topology = value; return *this; }

                OpenGLAPI RenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data, const GraphicsSettings* settings);

                OpenGLAPI void Render();

            private:

                const IGraphicsBuffer*  _data;
                const GraphicsSettings* _settings;
                VertexTopologies        _topology;

        };

        struct IndexedRenderStage3D : public RenderStage3D
        {
            public:

                IndexedRenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data, const GraphicsSettings* settings) : 
                    RenderStage3D(topology, data, settings)
                {

                }

                OpenGLAPI void Render() override;

        };

    }
}
