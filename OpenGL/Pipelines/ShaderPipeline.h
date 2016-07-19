/* CHANGELOG
 * Written by Josh Grooms on 20150910
 */

#pragma once
#include "EnumerationsGL.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Textures/Texture2D.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformBuffers.h"
#include "Buffers/VertexBuffer.h"
#include <map>

struct Color4;
struct Transform;


namespace Cyclone
{
    namespace OpenGL
    {
        class ShaderPipeline : public GraphicsPipeline
        {

            public:

		        /** PROPERTIES **/
		        FrameBuffer* RenderTarget()							const { return _renderTarget; }
		        void RenderTarget(FrameBuffer* target)					  { _renderTarget = target; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs an OpenGL rendering pipeline consisting only vertex and fragment shading stages. </summary>
		        OpenGLAPI ShaderPipeline(const string& vsSource, const string& psSource);
		        OpenGLAPI ~ShaderPipeline();



                /** BINDING METHODS **/
		        /// <summary> Activates any stored uniform shader variables for immediate use on the GPU. </summary>
		        OpenGLAPI void BindResources()						const override;
		        /// <summary> Deactivates any resources associated with this rendering pipeline on the GPU. </summary>
		        OpenGLAPI void UnbindResources()					const override;



                /** PIPELINE UTILITIES **/
		        OpenGLAPI void Execute()								override;
		        OpenGLAPI void Input(const IRenderableEntity& entity)   override;
		        OpenGLAPI void Input(const PerFrame& frameData)			override;
		        OpenGLAPI void Reset()									override;

		

            private:
		        FrameBuffer*				_renderTarget;

                VertexTopologies            Topology;

                std::map<const void*, uint> BufferIndices;
		        UniformBuffer<PerEntity>    PerEntityBuffer;
		        UniformBuffer<PerFrame>     PerFrameBuffer;
		        VertexBuffer				Vertices;

                void CompileShaders(const string& vsSource, const string& psSource);
		        void UpdateResources();
        };

    }
}