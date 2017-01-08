/* CHANGELOG
 * Written by Josh Grooms on 20160822
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Utilities { class ISpatialTransform; }


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
            ISpatialTransform*  Projection;
            FrameBuffer*        Target;
            ISpatialTransform*  View;

            /** CONSTRUCTOR **/
            GraphicsSettings() : 
                IsBlendEnabled(true),
                IsDepthTestEnabled(true),
                IsStencilTestEnabled(false),
                Pipeline(nullptr),
                Projection(nullptr),
                Target(nullptr),
                View(nullptr)
            {

            }

        };
    }
}
