/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "PlatformAPI.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformBuffers.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer;
        class GraphicsPipeline;
        class IRenderableEntity;
    }

    using namespace OpenGL;


    namespace Platform
    {
        class Window3D;



        class GPU
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets a pointer to the shader pipeline currently being used to render images. </summary>
                const GraphicsPipeline* RenderPipeline() const { return _renderPipeline; }
                /// <summary> Gets a pointer to the framebuffer to which all rendering currently occurs. </summary>
                const FrameBuffer* RenderTarget() const { return _renderTarget; }
                /// <summary> Gets a pointer to the window currently being used to display the render target. </summary>
                const Window3D* RenderWindow() const { return _renderWindow; }

                /// <summary> Sets the shader pipeline that will be used by the GPU to render images. </summary>
                PlatformAPI void RenderPipeline(GraphicsPipeline* pipeline);
                /// <summary> Sets the framebuffer to which all subsequent rendering will occur. </summary>
                PlatformAPI void RenderTarget(FrameBuffer* framebuffer);
                /// <summary> Sets the window that will be used to display the images in the render target. </summary>
                PlatformAPI void RenderWindow(Window3D* window);



                /** CONSTRUCTOR **/
                PlatformAPI GPU();
                PlatformAPI ~GPU();



                /** RENDERING UTILITIES **/
                /// <summary> Clears the depth-stencil and render target buffers in preparation for a new render loop iteration. </summary>
                /// <remarks> This method should be among the first called within the rendering loop. </remarks>
                PlatformAPI void Clear(const Color4& color);

                PlatformAPI void Input(const IRenderableEntity& entity);

                PlatformAPI void Input(const PerFrame& frameData);


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
                /// <summary> Executes the shader pipeline programs currently bound to the GPU. </summary>
                PlatformAPI void Render();



            private:

                /** PROPERTY DATA **/
                float                       _fov;
                GraphicsPipeline*           _renderPipeline;
                FrameBuffer*                _renderTarget;
                Window3D*                   _renderWindow;

                UniformBuffer<PerEntity>    PerEntityBuffer;
                UniformBuffer<PerFrame>     PerFrameBuffer;




                /** PRIVATE UTILITIES **/
                void RestoreRenderingDefaults();
        };
    }
}
