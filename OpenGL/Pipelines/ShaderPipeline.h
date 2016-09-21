/* CHANGELOG
 * Written by Josh Grooms on 20150910
 */

#pragma once
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class ShaderPipeline : public GraphicsPipeline
        {

            public:

                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs an OpenGL rendering pipeline consisting of only a fragment shader program. </summary>
                /// <param name="psSource"> A string containing the full or relative path to a fragment shader source code file (e.g. *.psl). </param>
                OpenGLAPI ShaderPipeline(const string& psSource);
                /// <summary> Constructs an OpenGL rendering pipeline consisting of only vertex and fragment shading stages. </summary>
		        OpenGLAPI ShaderPipeline(const string& vsSource, const string& psSource);
                /// <summary> Destroys any active shader programs and the pipeline object linking them together. </summary>
		        OpenGLAPI ~ShaderPipeline();

            protected:

                /// <summary> Attaches the active shader programs to GPU and links them together into a single executable pipeline.  </summary>
                /// <returns> A Boolean <c>true</c> if linking is successful, or <c>false</c> otherwise. </returns>
                OpenGLAPI bool Link() override;

            private:

                /// <summary> A pointer to the active fragment shader program. </summary>
                Shader*     FragmentShader;
                /// <summary> A pointer to the active geometry shader program. </summary>
                Shader*     GeometryShader;
                /// <summary> A pointer to the active tessellation shader program. </summary>
                Shader*     TessellationShader;
                /// <summary> A pointer to the active vertex shader program. </summary>
                Shader*     VertexShader;

        };

    }
}
