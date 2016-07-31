/* CHANGELOG
 * Written by Josh Grooms on 20150910
 *      20151106:   Updated the error logging system, removed obsolete code, and filled out important documentation.
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"
#include "TypeDefinitions.h"


namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A class that creates and manages one individual GPU shader program. </summary>
        /// <remarks>
        ///		The shader class is responsible for creating compiled binaries from OpenGL Shading Language (GLSL) source code.
        ///		Multiple instances of these binaries, each representing a discrete stage of the programmable GPU rendering pipeline,
        ///		can then be linked together to form a complete program useful for rendering geometry. Typically, this process is
        ///	    handled automatically within the 'ShaderPipeline' class.
        /// </remarks>
        class Shader
        {

            public:

                /** PROPERTIES **/
                /// <summary> The numeric handle representing the shader program on the GPU. </summary>
		        OpenGLAPI uint ID()                   const { return _id; }
		        /// <summary> Gets the full path string pointing to the GLSL source code file for this shader program. </summary>
		        OpenGLAPI const string& SourcePath()  const { return _location; }
		        /// <summary> The stage of the GPU rendering pipeline to which this program belongs. </summary>
		        OpenGLAPI ShaderTypes Type()          const { return _type; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new shader program that can be plugged into the programmable GPU rendering stages. </summary>
                /// <param name="fileName"> A string containing the name or path of the shader program source code file to be compiled. </param>
                /// <param name="type">
                ///     One of the shader type enumerators. This argument dictates where in the GPU pipeline the compiled shader program will be.
                /// </param>
		        OpenGLAPI Shader(string fileName, ShaderTypes type);
                /// <summary> Destroys the shader program on the GPU. </summary>
		        OpenGLAPI ~Shader();



                /** UTILITIES **/
                /// <summary> Generates a human-readable string detailing the current internal state of this shader program. </summary>
                OpenGLAPI string Report() const;



            private:

                /** PROPERTY DATA **/
                uint            _id;
                string          _location;
                ShaderTypes     _type;



                /** PRIVATE UTILITIES **/
                void Compile(string src);
                string Preprocess(string src);
                string ReportShaderLog() const;

        };

    }
}
