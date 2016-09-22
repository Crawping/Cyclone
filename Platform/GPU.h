/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "PlatformAPI.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Collections/List.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Spatial/Transform.h"



namespace Cyclone
{

    /** FORWARD DECLARATIONS **/
    using namespace OpenGL;
    namespace OpenGL
    {
        class FrameBuffer;
        //class GraphicsPipeline;
        class IRenderableEntity;
        class Scene3D;
    }



    namespace Platform
    {
        class Window3D;



        class GPU
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets a reference to the projection transformation being used by the rendering pipeline. </summary>
                const Transform& Projection()               const { return _projection; }
                /// <summary> Gets a pointer to the shader pipeline currently being used to render images. </summary>
                const GraphicsPipeline* RenderPipeline()    const { return _renderPipeline; }

                uint RenderPipelineID()                     const { return _renderPipeline ? _renderPipeline->ID() : 0; }
                /// <summary> Gets a pointer to the framebuffer to which all rendering currently occurs. </summary>
                const FrameBuffer* RenderTarget()           const { return _renderTarget; }
                /// <summary> Gets a pointer to the window currently being used to display the render target. </summary>
                const Window3D* RenderWindow()              const { return _renderWindow; }
                /// <summary> Gets a reference to the view transformation being used by the rendering pipeline. </summary>
                const Transform& View()                     const { return _view; }




                /// <summary> Sets the projection transformation matrix that will be used by GPU shader pipeline. </summary>
                PlatformAPI void Projection(const Transform& projection);
                /// <summary> Sets the shader pipeline that will be used by the GPU to render images. </summary>
                PlatformAPI void RenderPipeline(GraphicsPipeline* pipeline);
                /// <summary> Sets the framebuffer to which all subsequent rendering will occur. </summary>
                PlatformAPI void RenderTarget(FrameBuffer* framebuffer, int slot = 0);
                /// <summary> Sets the window that will be used to display the images in the render target. </summary>
                PlatformAPI void RenderWindow(Window3D* window);
                /// <summary> Sets the 3D rendering scene that will be displayed for the user. </summary>
                PlatformAPI void Scene(Scene3D* scene, int slot = 0);
                /// <summary> Sets the view transformation matrix that will be used by the GPU shader pipeline. </summary>
                PlatformAPI void View(const Transform& view);



                /** CONSTRUCTOR **/
                PlatformAPI GPU();
                PlatformAPI ~GPU();



                /** RENDERING UTILITIES **/
                /// <summary> Clears the depth-stencil and render target buffers in preparation for a new render loop iteration. </summary>
                /// <param name="color"> The color value that will be used to nullify or replace all contents of the render target. </param>
                /// <remarks> This method should be among the first called within the rendering loop. </remarks>
                PlatformAPI void Clear(const Color4& color);
                /// <summary> Swaps the front and back rendering buffers, displaying the contents of the backbuffer to the user. </summary>
                /// <remarks>
                ///     On Windows, and in particular within DirectX, the rendering buffer associated with a window is often
                ///     called a 'swap-chain'. The same construct exists OpenGL, although the term 'swap-chain' is somewhat
                ///     less common in that domain. It represents two separate framebuffers on which rendering occurs that are
                ///     constantly being cycled or swapped with one another in order to present drawings on-screen to the user.
                ///     One of these framebuffers is called a 'front' buffer, while the other is called the 'back' buffer.
                ///
                ///     The front-buffer contains image data from a previous iteration of the rendering loop. In other words,
                ///     it holds rendering outputs that are currently on the computer monitor being displayed for the user.
                ///     Typically, whichever framebuffer is currently the front-buffer is immutable. The back-buffer, however,
                ///     is modifiable and is usually where any new rendering occurs. Thus, as a program proceeds through its
                ///     rendering loop and a shader pipeline produces new outputs, the back-buffer is where they are stored.
                ///     On completion of a rendering loop iteration, the front- and back-buffers swap positions, and what was
                ///     originally the front-buffer now becomes the back-buffer and vice versa. Its contents are also usually
                ///     cleared at this point, providing a fresh blank surface on which the next iteration can draw.
                ///
                ///     Such a scheme is usually referred to as 'double-buffering' and is the typical mode of operation for
                ///     rendering on most popular platforms. Other schemes, such as triple-buffering, are also sometimes used,
                ///     but are not discussed here.
                /// </remarks>
                PlatformAPI void Present();
                /// <summary> Executes the shader pipeline currently bound to the GPU. </summary>
                PlatformAPI void Execute();
                /// <summary> Performs any necessary updates to buffer objects currently bound to the GPU. </summary>
                PlatformAPI void Update();

                

                /** GENERAL UTILITIES **/
                /// <summary> Generates a human-readable string detailing the internal state of the GPU object and any OpenGL errors encountered. </summary>
                /// <remarks>
                ///     Calls to this method impose a significant performance penalty and therefore should only be made sparingly, if 
                ///     at all. Prefer invoking this functionality only while debugging.
                /// </remarks>
                PlatformAPI string Report() const;
                /// <summary> Determines whether a specific OpenGL extension is available on the current system. </summary>
                /// <returns> A Boolean <c>true</c> if the given extension is supported, or <c>false</c> otherwise. </returns>
                /// <param name="extension"> A string containing the name of extension for which support is being queried. </param>
                PlatformAPI bool SupportsExtension(const string& extension) const;

                PlatformAPI List<string> QueryExtensions() const;



                PlatformAPI int GetUniformID(const string& name) const;
                PlatformAPI void SetUniform(const string& name, const Color4& value)    const;
                PlatformAPI void SetUniform(const string& name, const Transform& value) const;

            private:

                /** PROPERTY DATA **/
                float                       _fov;
                Transform                   _projection;
                GraphicsPipeline*           _renderPipeline;
                FrameBuffer*                _renderTarget;
                Window3D*                   _renderWindow;
                Scene3D*                    _renderScene;
                Transform                   _view;



                /** PRIVATE DATA **/
                UniformBuffer<PerFrame>     PerFrameBuffer;
                


                /** PRIVATE UTILITIES **/
                void RestoreRenderingDefaults();
                string ReportErrors() const;
                
        };
    }
}
