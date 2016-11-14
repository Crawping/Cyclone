/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "EnumerationsGL.h"
#include "Interfaces/IRenderStage.h"
#include <map>



namespace Cyclone
{
    namespace Utilities { struct ITransformation3D; }

    namespace OpenGL
    {
        class IGraphicsBuffer;
        class FrameBuffer;
        class GraphicsPipeline;
        struct GraphicsSettings;

        struct RenderStage3D : public virtual IRenderStage
        {
            public:

                /** PROPERTIES **/
                const IGraphicsBuffer* Data()                               const override { return _data; }
                const GraphicsSettings& Settings()                          const override { return *_settings; }
                VertexTopologies Topology()                                 const override { return _topology; }

                OpenGLAPI RenderStage3D& IsBlendEnabled(bool value);
                OpenGLAPI RenderStage3D& IsDepthTestEnabled(bool value);
                OpenGLAPI RenderStage3D& IsStencilTestEnabled(bool value);
                OpenGLAPI RenderStage3D& CullingMode(CullingModes value);
                OpenGLAPI RenderStage3D& Pipeline(GraphicsPipeline* value);
                OpenGLAPI RenderStage3D& Projection(ITransformation3D* value);
                OpenGLAPI RenderStage3D& Target(FrameBuffer* value);
                OpenGLAPI RenderStage3D& View(ITransformation3D* value);



                /** CONSTRUCTOR **/
                OpenGLAPI RenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data, GraphicsSettings* settings);



                /** UTILITIES **/
                OpenGLAPI void Render();

            private:

                const IGraphicsBuffer*  _data;
                GraphicsSettings*       _settings;
                VertexTopologies        _topology;

        };

        struct IndexedRenderStage3D : public RenderStage3D
        {
            public:

                IndexedRenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data, GraphicsSettings* settings) : 
                    RenderStage3D(topology, data, settings)
                {

                }

                OpenGLAPI void Render() override;

        };

    }
}
