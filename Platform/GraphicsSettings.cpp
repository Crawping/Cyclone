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
        
    }
}
