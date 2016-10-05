/* CHANGELOG
 * Written by Josh Grooms on 20161005
 */

#pragma once
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class ComputePipeline : public GraphicsPipeline
        {

            public:

                OpenGLAPI ComputePipeline(const string& source);
                OpenGLAPI ~ComputePipeline();


            protected:

                OpenGLAPI bool Link() override;

            private:
                /// <summary> A pointer to the active compute shader program. </summary>
                Shader*     ComputeShader;
        };
    }
}
