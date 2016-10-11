#include "RenderStage.h"
#include "Buffers/GraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {

        RenderStage3D::RenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data, const GraphicsSettings* settings) :
            _data(data),
            _settings(settings),
            _topology(topology)
        {

        }


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