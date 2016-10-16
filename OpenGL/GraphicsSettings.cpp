#include "GraphicsSettings.h"



namespace Cyclone
{
    namespace OpenGL
    {

        GraphicsSettings::GraphicsSettings() :
            IsBlendEnabled(true),
            IsDepthTestEnabled(true),
            IsStencilTestEnabled(true),
            Pipeline(nullptr),
            Projection(nullptr),
            Target(nullptr),
            View(nullptr)
        {

        }
        
    }
}
