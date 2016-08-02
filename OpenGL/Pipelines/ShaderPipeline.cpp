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
            FragmentShader(new Shader(psSource, ShaderTypes::PixelShader)),
            GeometryShader(nullptr),
            TessellationShader(nullptr),
            VertexShader(new Shader(vsSource, ShaderTypes::VertexShader))
        {
            Link();
        }
        ShaderPipeline::~ShaderPipeline()
        {
            if (VertexShader)       { delete VertexShader; }
            if (TessellationShader) { delete TessellationShader; }
            if (GeometryShader)     { delete GeometryShader; }
            if (FragmentShader)     { delete FragmentShader; }
        }



        /** PROTECTED UTILITIES **/
        bool ShaderPipeline::Link()
        {
            if (FragmentShader)         { glAttachShader(ID(), FragmentShader->ID()); }
            if (GeometryShader)         { glAttachShader(ID(), GeometryShader->ID()); }
            if (TessellationShader)     { glAttachShader(ID(), TessellationShader->ID()); }
            if (VertexShader)           { glAttachShader(ID(), VertexShader->ID()); }

            return GraphicsPipeline::Link();
        }
        
    }
}
