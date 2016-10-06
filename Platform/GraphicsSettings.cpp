#include "GPU.h"
#include "GraphicsSettings.h"



namespace Cyclone
{
    namespace Platform
    {

        GraphicsSettings::GraphicsSettings() :
            IsBlendingEnabled(true),
            Pipeline(nullptr),
            Projection(nullptr),
            Target(nullptr),
            View(nullptr)
        {

        }

        void GraphicsSettings::Apply(GPU* gpu) const
        {
            if (IsBlendingEnabled)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
            else
                glDisable(GL_BLEND);

            if (FaceCulling)
            {
                glEnable(GL_CULL_FACE);
                glCullFace(FaceCulling);
            }
            else
                glDisable(GL_CULL_FACE);

            gpu->Pipeline(Pipeline);
            gpu->Projection(Projection);
            gpu->Target(Target);
            gpu->View(View);
        }
    }
}