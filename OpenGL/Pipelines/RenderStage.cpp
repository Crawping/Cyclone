#include "Pipelines/RenderStage.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        RenderStage& RenderStage::IsBlendEnabled(bool value) 
        { 
            _settings.IsBlendEnabled = value; 
            return *this;
        }
        RenderStage& RenderStage::IsDepthTestEnabled(bool value) 
        { 
            _settings.IsDepthTestEnabled = value; 
            return *this;
        }
        RenderStage& RenderStage::IsStencilTestEnabled(bool value)
        { 
            _settings.IsStencilTestEnabled = value; 
            return *this;
        }
        RenderStage& RenderStage::CullingMode(CullingModes value)
        {
            _settings.CullingMode = value;
            return *this;
        }
        RenderStage& RenderStage::Pipeline(IGraphicsPipeline* value)
        { 
            _settings.Pipeline = value;
            return *this;
        }
        RenderStage& RenderStage::Projection(ISpatialTransform* value) 
        { 
            _settings.Projection = value;
            return *this;
        }
        RenderStage& RenderStage::Settings(const GraphicsSettings& value)
        {
            return this->
                 IsBlendEnabled(value.IsBlendEnabled)
                .IsDepthTestEnabled(value.IsDepthTestEnabled)
                .IsStencilTestEnabled(value.IsStencilTestEnabled)
                .CullingMode(value.CullingMode)
                .Pipeline(value.Pipeline)
                .Projection(value.Projection)
                .Target(value.Target)
                .View(value.View);
        }
        RenderStage& RenderStage::Target(FrameBuffer* value)
        { 
            _settings.Target = value; 
            return *this;
        }
        RenderStage& RenderStage::Topology(PointTopologies value)
        {
            _topology = value;
            return *this;
        }
        RenderStage& RenderStage::View(ISpatialTransform* value) 
        { 
            _settings.View = value;
            return *this;
        }



        /** PUBLIC UTILITIES **/
        void RenderStage::Append(const BufferBinding& binding)
        {
            _buffers.Append(binding);
        }
        void RenderStage::Append(const List<BufferBinding>& bindings)
        {
            for (const auto& b : bindings)
                Append(b);
        }
        void RenderStage::ClearBuffers()
        {
            _buffers.Clear();
        }

    }
}