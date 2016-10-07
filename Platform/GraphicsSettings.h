/* CHANGELOG
 * Written by Josh Grooms on 20160822
 */

#pragma once
#include "EnumerationsGL.h"
#include "PlatformAPI.h"
#include "Interfaces/IGraphicsSettings.h"



namespace Cyclone
{
    using namespace OpenGL;
    using namespace Utilities;
    namespace OpenGL
    {
        class FrameBuffer;
        class GraphicsPipeline;
    }
    namespace Utilities
    {
        class ITransformation3D;
    }



    namespace Platform
    {

        struct BlendSettings
        {
            bool IsEnabled;

        };


        struct GraphicsSettings //: public IGraphicsSettings
        {
            //BlendSettings       Blending;
            bool                IsBlendingEnabled;
            FaceCullModes       FaceCulling;

            GraphicsPipeline*   Pipeline;
            ITransformation3D*  Projection;
            FrameBuffer*        Target;
            ITransformation3D*  View;

            /** CONSTRUCTOR **/
            PlatformAPI GraphicsSettings();
        };
    }
}
