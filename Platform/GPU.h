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
        class ShaderPipeline;
    }

    using namespace OpenGL;


    namespace Platform
    {

        class Window3D;

        class GPU
        {
            public:

                /** PROPERTIES **/
                const ShaderPipeline* RenderPipeline() const { return _renderPipeline; }
                const FrameBuffer* RenderTarget() const { return _renderTarget; }
                const Window3D* RenderWindow() const { return _renderWindow; }

                PlatformAPI void RenderPipeline(const ShaderPipeline* pipeline);
                PlatformAPI void RenderTarget(const FrameBuffer* framebuffer);
                PlatformAPI void RenderWindow(const Window3D* window);



                /** CONSTRUCTOR **/
                PlatformAPI GPU();
                PlatformAPI ~GPU();



                /** RENDERING UTILITIES **/
                PlatformAPI void Clear();
                PlatformAPI void Present();



            private:

                struct              _gpu;
                _gpu*               Internals;



                /** PROPERTY DATA **/
                float                   _fov;
                const ShaderPipeline*   _renderPipeline;
                FrameBuffer*            _renderTarget;
                const Window3D*         _renderWindow;



                /** PRIVATE UTILITIES **/
                void RestoreRenderingDefaults();
        };
    }
}
