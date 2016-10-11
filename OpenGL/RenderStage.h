/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "EnumerationsGL.h"
#include "GraphicsSettings.h"
#include "Interfaces/IRenderingStage.h"
#include <map>



namespace Cyclone
{
    namespace OpenGL
    {
        struct RenderStage3D : public IRenderingStage3D
        {
            public:

                const IGraphicsBuffer* PipelineData()                       const override { return _data; }
                const GraphicsSettings* Settings()                          const override { return _settings; }
                VertexTopologies Topology()                                 const override { return _topology; }

                RenderStage3D& PipelineData(const IGraphicsBuffer* value)   { _data = value; return *this; }
                RenderStage3D& Settings(const GraphicsSettings* value)      { _settings = value; return *this; }
                RenderStage3D& Topology(VertexTopologies value)             { _topology = value; return *this; }

                OpenGLAPI RenderStage3D();

                OpenGLAPI void Render();

            private:

                const IGraphicsBuffer*  _data;
                const GraphicsSettings* _settings;
                VertexTopologies        _topology;

        };

        struct IndexedRenderStage3D : public RenderStage3D
        {
            public:

                OpenGLAPI void Render() override;

        };



        //struct RenderPacket
        //{
        //    public:



        //    private:
        //        
        //        std::map<VertexTopologies
        //};
    }
}
