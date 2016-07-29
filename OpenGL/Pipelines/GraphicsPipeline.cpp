#include "Pipelines/GraphicsPipeline.h"
#include "Pipelines/Shader.h"
#include "Utilities.h"


namespace Cyclone
{
    namespace OpenGL
    {
        /** CONSTRUCTORS & DESTRUCTOR **/
        GraphicsPipeline::GraphicsPipeline() :
            _id(0),
            VertexShader(nullptr),
            FragmentShader(nullptr)
        {
            _id = glCreateProgram();
            if (!_id)
                Console::WriteLine("Failed to create the shader pipeline object.");
        }
        GraphicsPipeline::~GraphicsPipeline()
        {
            if (VertexShader)   { delete VertexShader; }
            if (FragmentShader) { delete FragmentShader; }
            if (_id) { glDeleteProgram(_id); }
        }



        /** BINDING UTILITIES **/
        void GraphicsPipeline::Bind(int slot)		const
        {
            BindEntity();
            BindResources();
        }
        void GraphicsPipeline::BindEntity(int slot) const
        {
            glUseProgram(ID());
        }

        void GraphicsPipeline::Unbind()				const
        {
            UnbindResources();
            UnbindEntity();
        }
        void GraphicsPipeline::UnbindEntity()		const
        {
            glUseProgram(0);
        }



        /** PROTECTED UTILITIES **/
        string GraphicsPipeline::ReportShaderLog()  const
        {
            string msg;
            GLint nchars = 0;
            glGetProgramiv(ID(), GL_INFO_LOG_LENGTH, &nchars);
            if (nchars > 0)
            {
                msg.reserve(nchars);
                glGetProgramInfoLog(ID(), nchars, 0, &msg[0]);
            }

            return msg;
        }
    }
}