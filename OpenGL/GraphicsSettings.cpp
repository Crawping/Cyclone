#include "GraphicsSettings.h"



namespace Cyclone
{
    namespace OpenGL
    {

        GraphicsSettings::GraphicsSettings() :
            IsBlendingEnabled(true),
            Pipeline(nullptr),
            Projection(nullptr),
            Target(nullptr),
            View(nullptr)
        {

        }
        
    }
}
