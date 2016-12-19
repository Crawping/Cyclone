/* CHANGELOG
 * Written by Josh Grooms on 20161125
 */

#pragma once
#include "GraphicsSettings.h"
#include "Collections/List.h"
#include "Interfaces/IRenderStage.h"



namespace Cyclone
{
    namespace Utilities { struct ITransformation3D; }

    namespace OpenGL
    {
        class IGraphicsBuffer;
        class FrameBuffer;
        class GraphicsPipeline;


        struct RenderStage : public virtual IRenderStage
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets a list of buffers that are used by the rendering stage. </summary>
                List<BufferBinding> Buffers()                               const override { return _buffers; }
                /// <summary> Gets the GPU configuration settings that are used by the rendering stage. </summary>
                const GraphicsSettings& Settings()                          const override { return _settings; }
                /// <summary> Gets the primitive topology of the points that are used by the rendering stage. </summary>
                VertexTopologies Topology()                                 const override { return _topology; }

                /// <summary> Sets whether alpha blending is enabled for the rendering stage. </summary>
                OpenGLAPI RenderStage& IsBlendEnabled(bool value);
                /// <summary> Sets whether depth testing is enabled for the rendering stage. </summary>
                OpenGLAPI RenderStage& IsDepthTestEnabled(bool value);
                /// <summary> Sets whether stencil testing is enabled for the rendering stage. </summary>
                OpenGLAPI RenderStage& IsStencilTestEnabled(bool value);
                /// <summary> Sets the type of geometric face culling to be used by the rendering stage. </summary>
                OpenGLAPI RenderStage& CullingMode(CullingModes value);
                /// <summary> Sets the OpenGL rendering pipeline to be used by the rendering stage. </summary>
                OpenGLAPI RenderStage& Pipeline(GraphicsPipeline* value);
                /// <summary> Sets the perspective projection transformation to be used by the rendering stage. </summary>
                OpenGLAPI RenderStage& Projection(ITransformation3D* value);
                /// <summary> Sets the overall GPU configuration settings that are used by the rendering stage. </summary>
                OpenGLAPI RenderStage& Settings(const GraphicsSettings& value);
                /// <summary> Sets the target framebuffer object to be used by the rendering stage. </summary>
                OpenGLAPI RenderStage& Target(FrameBuffer* value);
                /// <summary> Sets the primitive topology of the points that are used by the rendering stage. </summary>
                OpenGLAPI RenderStage& Topology(VertexTopologies value);
                /// <summary> Sets the view transformation to be used by the rendering stage. </summary>
                OpenGLAPI RenderStage& View(ITransformation3D* value);



                /** UTILITIES **/
                /// <summary> Adds a new buffer to the list of those used by the rendering stage. </summary>
                /// <param name="binding"> A binding configuration containing the buffer and its associated attachment point. </param>
                OpenGLAPI void Add(const BufferBinding& binding);
                /// <summary> Adds a collection of buffers to the list of those used by the rendering stage. </summary>
                /// <param name="bindings"> A list of binding configurations containing the buffers and their associated attachment points. </param>
                OpenGLAPI void Add(const List<BufferBinding>& bindings);
                /// <summary> Clears the list of buffers used by the rendering stage. </summary>
                OpenGLAPI void ClearBuffers();

            protected:

                /** CONSTRUCTOR **/
                /// <summary> Constructs a new empty rendering stage whose settings can be populated externally. </summary>
                RenderStage() { }

            private:

                /** DATA **/
                List<BufferBinding>     _buffers;
                GraphicsSettings        _settings;
                VertexTopologies        _topology;

        };
    }
}
