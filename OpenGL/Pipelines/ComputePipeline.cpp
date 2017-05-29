#include "EnumerationsGL.h"
#include "GL/OpenGL.h"
#include "Pipelines/ComputePipeline.h"
#include "Pipelines/Shader.h"



namespace Cyclone
{
    namespace OpenGL
    {
        
        /** CONSTRUCTOR & DESTRUCTOR **/
        ComputePipeline::ComputePipeline(const string& source) :
            ComputeShader(new Shader(source, ShaderTypes::ComputeShader))
        {
            Link();
        }
        ComputePipeline::~ComputePipeline()
        {
            if (ComputeShader) { delete ComputeShader; }
        }



        /** PROTECTED UTILITIES **/
        bool ComputePipeline::Link()
        {
            if (ComputeShader)
                glAttachShader(ID(), ComputeShader->ID());
            else
                return false;

            return GraphicsPipeline::Link();
        }
    }
}