#include "Console.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Windows/WGL.h"



namespace Cyclone
{
    using namespace Utilities;

    namespace Platform
    {
        /** PROPERTIES **/
        void GPU::RenderPipeline(GraphicsPipeline* pipeline)
        {
            _renderPipeline = pipeline;
            if (_renderPipeline)
                _renderPipeline->Bind();
        }
        void GPU::RenderTarget(FrameBuffer* framebuffer)
        {
            _renderTarget = framebuffer;
            if (_renderTarget)
                _renderTarget->Bind();
        }
        void GPU::RenderWindow(Window3D* window)
        {
            _renderWindow = window;
            if (_renderWindow)
                _renderWindow->Bind();
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        GPU::GPU() : 
            _fov(90),
            _renderPipeline(nullptr),
            _renderTarget(nullptr),
            _renderWindow(nullptr)
        {
            
        }

        GPU::~GPU()
        {

        }



        /** RENDERING UTILITIES **/
        void GPU::Clear()
        {
            RestoreRenderingDefaults();
            glClearBufferfv(GL_COLOR, 0, Color4::Red.ToArray());
        }

        void GPU::Present()
        {
            if (_renderWindow)
                _renderWindow->Present();
        }

        void GPU::Render()
        {
            if (_renderPipeline)
                _renderPipeline->Execute();
        }


        /** PRIVATE UTILITIES **/
        void GPU::RestoreRenderingDefaults()
        {            
            if (_renderWindow)
                glViewport(0, 0, _renderWindow->Width(), _renderWindow->Height());
            glActiveTexture(GL_TEXTURE0);
        }
    }
}