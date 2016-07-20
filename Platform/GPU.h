/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "PlatformAPI.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer;
        class GraphicsPipeline;
    }

    using namespace OpenGL;


    namespace Platform
    {
        class Window3D;



        class GPU
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets a pointer to the shader pipeline currently bound to the GPU. </summary>
                const GraphicsPipeline* RenderPipeline() const { return _renderPipeline; }
                /// <summary> Gets a pointer to the framebuffer currently bound to the GPU. </summary>
                const FrameBuffer* RenderTarget() const { return _renderTarget; }
                /// <summary> Gets a pointer to the window currently being used as the rendering surface. </summary>
                const Window3D* RenderWindow() const { return _renderWindow; }

                PlatformAPI void RenderPipeline(const GraphicsPipeline* pipeline);
                PlatformAPI void RenderTarget(const FrameBuffer* framebuffer);
                PlatformAPI void RenderWindow(const Window3D* window);



                /** CONSTRUCTOR **/
                PlatformAPI GPU();
                PlatformAPI ~GPU();



                /** RENDERING UTILITIES **/
                PlatformAPI void Clear();
                PlatformAPI void Present();



            private:

                /** PROPERTY DATA **/
                float                   _fov;
                const GraphicsPipeline* _renderPipeline;
                const FrameBuffer*      _renderTarget;
                const Window3D*         _renderWindow;



                /** PRIVATE UTILITIES **/
                void RestoreRenderingDefaults();
        };
    }
}
