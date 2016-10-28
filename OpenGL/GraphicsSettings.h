/* CHANGELOG
 * Written by Josh Grooms on 20160822
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Utilities { class ITransformation3D; }


    namespace OpenGL
    {
        class FrameBuffer;
        class GraphicsPipeline;

        

        struct GraphicsSettings
        {
            bool                IsBlendEnabled;
            bool                IsDepthTestEnabled;
            bool                IsStencilTestEnabled;

            CullingModes        CullingMode;
            GraphicsPipeline*   Pipeline;
            ITransformation3D*  Projection;
            FrameBuffer*        Target;
            ITransformation3D*  View;

            /** CONSTRUCTOR **/
            OpenGLAPI GraphicsSettings();
        };
    }
}
