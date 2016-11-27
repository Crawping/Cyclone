/* CHANGELOG
 * Written by Josh Grooms on 20161125
 */

#pragma once
#include "GraphicsSettings.h"
#include "Collections/List.h"
#include "Interfaces/IRenderStage.h"



namespace Cyclone
{
    namespace Utilities { struct ITransformation3D; }

    namespace OpenGL
    {
        class IGraphicsBuffer;
        class FrameBuffer;
        class GraphicsPipeline;


        struct RenderStage : public virtual IRenderStage
        {
            public:

                /** PROPERTIES **/
                List<BufferBinding> Buffers()                               const override { return _buffers; }
                const GraphicsSettings& Settings()                          const override { return _settings; }
                VertexTopologies Topology()                                 const override { return _topology; }

                OpenGLAPI RenderStage& IsBlendEnabled(bool value);
                OpenGLAPI RenderStage& IsDepthTestEnabled(bool value);
                OpenGLAPI RenderStage& IsStencilTestEnabled(bool value);
                OpenGLAPI RenderStage& CullingMode(CullingModes value);
                OpenGLAPI RenderStage& Pipeline(GraphicsPipeline* value);
                OpenGLAPI RenderStage& Projection(ITransformation3D* value);
                OpenGLAPI RenderStage& Settings(const GraphicsSettings& value);
                OpenGLAPI RenderStage& Target(FrameBuffer* value);
                OpenGLAPI RenderStage& Topology(VertexTopologies value);
                OpenGLAPI RenderStage& View(ITransformation3D* value);

                OpenGLAPI void Add(const BufferBinding& binding);
                OpenGLAPI void Add(const List<BufferBinding>& bindings);
                OpenGLAPI void ClearBuffers();

            protected:

                /** CONSTRUCTOR **/
                RenderStage() { }

            private:

                List<BufferBinding>     _buffers;
                GraphicsSettings        _settings;
                VertexTopologies        _topology;

        };
    }
}
