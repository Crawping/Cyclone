/* CHANGELOG
 * Written by Josh Grooms on 20160822
 */

#pragma once
#include "Spatial/Transform.h"



namespace Cyclone
{
    using namespace OpenGL;
    using namespace Utilities;
    namespace OpenGL
    {
        class FrameBuffer;
        class GraphicsPipeline;
    }

    namespace Platform
    {
        struct BlendSettings
        {

        };


        struct GraphicsSettings
        {
            BlendSettings       Blending;
            Transform           Projection;
            GraphicsPipeline*   Pipeline;
            FrameBuffer*        RenderTarget;
            Transform           View;
        };
    }
}
