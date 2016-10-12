#include "RenderStage2D.h"
#include "Interfaces/IGraphicsBuffer.h"

//using namespace Cyclone::OpenGL;



namespace Cyclone
{
    namespace SVG
    {

        void RenderStage2D::Render()
        {
            if (Data()->Count())
            {
                glStencilMask(~0);
                glEnable(GL_STENCIL_TEST);
                glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

                //for (const auto* p : PathBuffer)
                //    p->Render();

                glDisable(GL_STENCIL_TEST);
            }
        }
    }
}