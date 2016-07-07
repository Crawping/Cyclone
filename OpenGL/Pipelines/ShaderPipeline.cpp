/* CHANGELOG
 * Written by Josh Grooms on 20150918
 */

#include "Color4.h"
#include "Console.h"
#include "Geometry.h"
#include "EnumerationsGL.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include "ShaderPipeline.h"
#include "Transform.h"
#include "Utilities.h"
#include "VertexBuffer.h"



/** CONSTRUCTORS & DESTRUCTOR **/
ShaderPipeline::ShaderPipeline(const string& vsSource, const string& psSource) :
	_renderTarget(nullptr),
    Topology(VertexTopologies::Triangles),
    Vertices(Geometry::Quad)
{
    if (!ID())
    {
        Console::WriteLine("Failed to initialize the OpenGL shader program.");
        return;
    }

    CompileShaders(vsSource, psSource);
}
ShaderPipeline::~ShaderPipeline()
{
    /*if (Vertices)
        delete Vertices;*/
}



/** PRIVATE UTILITIES **/
/// <summary> Compiles individual shader programs and links them together to form a rendering pipeline. </summary>
void ShaderPipeline::CompileShaders(const string& vsSource, const string& psSource)
{
    // Compile the individual shader programs
    Shader vs(vsSource, ShaderTypes::VertexShader);
    Shader ps(psSource, ShaderTypes::PixelShader);

    // Link the shader programs
    glAttachShader(ID(), vs.ID());
    glAttachShader(ID(), ps.ID());

    // Check for errors during shader compilation & linking
    GLint successful = 0;
    glLinkProgram(ID());
    glGetProgramiv(ID(), GL_LINK_STATUS, &successful);
    if (!successful)
    {
        Console::WriteLine("Failed to link the shader pipeline programs.");
        //PostShaderProgramLog();
    }

    glValidateProgram(ID());
    glGetProgramiv(ID(), GL_VALIDATE_STATUS, &successful);
    if (!successful)
    {
        Console::WriteLine("Failed to validate the shader pipeline.");
        //PostShaderProgramLog();
    }
}

void ShaderPipeline::UpdateResources()
{

}


/** BINDING METHODS **/
void ShaderPipeline::BindResources()        const
{
	if (_renderTarget)
		_renderTarget->Bind();
	Vertices.Bind();
    GraphicsPipeline::BindResources();
}
void ShaderPipeline::UnbindResources()      const
{
    GraphicsPipeline::UnbindResources();
    Vertices.Unbind();
	if (_renderTarget)
		_renderTarget->Unbind();
}



/** PIPELINE UTILITIES **/
void ShaderPipeline::Execute()
{
    UpdateResources();
    glDrawArraysInstanced(Topology, 0, Vertices.Count(), PerEntityBuffer.Count());
}

void ShaderPipeline::Input(const IRenderableEntity& entity)
{
    uint idx;
    PerEntity data;
    const void* entKey = (const void*)&entity;

    if (BufferIndices.count(entKey))
    {
        idx = BufferIndices[entKey];
        data = PerEntityBuffer[idx];
    }
    else
        idx = PerEntityBuffer.Count();

    BufferIndices[entKey] = idx;
    //if (entity.GetEntityData(data))
    //    PerEntityBuffer.Set(idx, data);
}

void ShaderPipeline::Input(const PerFrame& frameData)
{
    PerFrameBuffer.Set(0, frameData);
}

void ShaderPipeline::Reset()
{
	_renderTarget = nullptr;
	Topology = VertexTopologies::Triangles;
	
    BufferIndices.clear();
    PerEntityBuffer.Clear();
    PerFrameBuffer.Clear();
	Vertices.Clear();
}
