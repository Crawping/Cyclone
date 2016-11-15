#include "RenderStage3D.h"
#include "Buffers/GraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        
        /** PROPERTIES **/
        RenderStage3D& RenderStage3D::IsBlendEnabled(bool value) 
        { 
            _settings.IsBlendEnabled = value; 
            return *this;
        }
        RenderStage3D& RenderStage3D::IsDepthTestEnabled(bool value) 
        { 
            _settings.IsDepthTestEnabled = value; 
            return *this;
        }
        RenderStage3D& RenderStage3D::IsStencilTestEnabled(bool value)
        { 
            _settings.IsStencilTestEnabled = value; 
            return *this;
        }
        RenderStage3D& RenderStage3D::CullingMode(CullingModes value)
        {
            _settings.CullingMode = value;
            return *this;
        }
        RenderStage3D& RenderStage3D::Pipeline(GraphicsPipeline* value)
        { 
            _settings.Pipeline = value;
            return *this;
        }
        RenderStage3D& RenderStage3D::Projection(ITransformation3D* value) 
        { 
            _settings.Projection = value;
            return *this;
        }
        RenderStage3D& RenderStage3D::Settings(const GraphicsSettings& value)
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
        RenderStage3D& RenderStage3D::Target(FrameBuffer* value)
        { 
            _settings.Target = value; 
            return *this;
        }
        RenderStage3D& RenderStage3D::View(ITransformation3D* value) 
        { 
            _settings.View = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        RenderStage3D::RenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data) :
            _data(data),
            _topology(topology)
        {

        }
        RenderStage3D::RenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data, const GraphicsSettings& settings) :
            _data(data),
            _settings(settings),
            _topology(topology)
        {

        }



        /** UTILITIES **/
        void RenderStage3D::Render()
        {
            glMultiDrawArraysIndirect(Topology(), 0, Data()->Count(), 0);
        }

        void IndexedRenderStage3D::Render()
        {
            glMultiDrawElementsIndirect(Topology(), NumericFormats::UInt, 0, Data()->Count(), 0);
        }

    }
}