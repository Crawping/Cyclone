#include "GraphicsSettings.h"



namespace Cyclone
{
    namespace OpenGL
    {

        GraphicsSettings::GraphicsSettings() :
            IsBlendEnabled(true),
            IsDepthTestEnabled(true),
            IsStencilTestEnabled(false),
            Pipeline(nullptr),
            Projection(nullptr),
            Target(nullptr),
            View(nullptr)
        {

        }
        
    }
}
