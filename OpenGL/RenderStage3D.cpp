#include "RenderStage3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        template<> void RenderStage3D<DrawCommand>::Render() const
        {
            if (Commands.IsEmpty()) { return; }
            glMultiDrawArraysIndirect(Topology(), 0, Commands.Count(), 0);
        }

        template<> void RenderStage3D<IndexedDrawCommand>::Render() const
        {
            if (Commands.IsEmpty()) { return; }
            glMultiDrawElementsIndirect(Topology(), NumericFormats::UInt, 0, Commands.Count(), 0);
        }


        template struct RenderStage3D<DrawCommand>;
        template struct RenderStage3D<IndexedDrawCommand>;

    }
}