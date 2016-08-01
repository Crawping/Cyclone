/* CHANGELOG
 * Written by Josh Grooms on 20150918
 */

#include "Imaging/Color4.h"
#include "Console.h"
#include "EnumerationsGL.h"
#include "Utilities.h"

#include "Buffers/FrameBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Pipelines/Shader.h"
#include "Pipelines/ShaderPipeline.h"
#include "Spatial/Geometry.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /** CONSTRUCTORS & DESTRUCTOR **/
        ShaderPipeline::ShaderPipeline(const string& vsSource, const string& psSource) :
            Topology(VertexTopologies::Triangles),
            Vertices(Geometry::Quad)
        {
            CompileShaders(vsSource, psSource);
        }
        ShaderPipeline::~ShaderPipeline()
        {

        }



        /** PRIVATE UTILITIES **/
        /// <summary> Compiles individual shader programs and links them together to form a rendering pipeline. </summary>
        void ShaderPipeline::CompileShaders(const string& vsSource, const string& psSource)
        {
            // Compile the individual shader programs
            VertexShader = new Shader(vsSource, ShaderTypes::VertexShader);
            FragmentShader = new Shader(psSource, ShaderTypes::PixelShader);

            // Link the shader programs
            glAttachShader(ID(), VertexShader->ID());
            glAttachShader(ID(), FragmentShader->ID());

            // Check for errors during shader compilation & linking
            GLint successful = 0;
            glLinkProgram(ID());
            glGetProgramiv(ID(), GL_LINK_STATUS, &successful);
            if (!successful)
            {
                Console::WriteLine("Failed to link the shader pipeline programs.");
                Console::WriteLine(ReportShaderLog());
            }

            glValidateProgram(ID());
            glGetProgramiv(ID(), GL_VALIDATE_STATUS, &successful);
            if (!successful)
            {
                Console::WriteLine("Failed to validate the shader pipeline.");
                Console::WriteLine(ReportShaderLog());
            }
        }

        void ShaderPipeline::UpdateResources()
        {

        }



        /** BINDING METHODS **/
        void ShaderPipeline::BindResources()        const
        {
	        //Vertices.Bind();
            GraphicsPipeline::BindResources();
        }
        void ShaderPipeline::UnbindResources()      const
        {
            GraphicsPipeline::UnbindResources();
            //Vertices.Unbind();
        }



        /** PIPELINE UTILITIES **/
        void ShaderPipeline::Execute()
        {
            UpdateResources();
            //glDrawArraysInstanced(Topology, 0, Vertices.Count(), PerEntityBuffer.Count());
            //glDrawArraysInstanced(Topology, 0, Vertices.Count(), 1);
            //glDrawArrays(Topology, 0, Vertices.Count());
        }
        void ShaderPipeline::Reset()
        {
	        //Topology = VertexTopologies::Triangles;
	        //Vertices.Clear();
        }
    }
}
