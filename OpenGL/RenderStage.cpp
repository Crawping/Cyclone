#include "RenderStage.h"
#include "Buffers/GraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {

        RenderStage3D::RenderStage3D() :
            _data(nullptr),
            _settings(nullptr)
        {

        }


        void RenderStage3D::Render()
        {
            glMultiDrawArraysIndirect(Topology(), 0, PipelineData()->Count(), 0);
        }

        void IndexedRenderStage3D::Render()
        {
            glMultiDrawElementsIndirect(Topology(), NumericFormats::UInt, 0, PipelineData()->Count(), 0);
        }
    }
}