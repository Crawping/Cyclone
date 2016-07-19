#include "Console.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Pipelines/ShaderPipeline.h"
#include "Windows/WGL.h"



namespace Cyclone
{
    using namespace Utilities;

    namespace Platform
    {
        /** PROPERTIES **/
        void GPU::RenderPipeline(const ShaderPipeline* pipeline)
        {
            _renderPipeline = pipeline;
            _renderPipeline->Bind();
        }
        void GPU::RenderWindow(const Window3D* window)
        {
            _renderWindow = window;
            if (window)
                window->Bind();
        }


        /** CONSTRUCTOR & DESTRUCTOR **/
        GPU::GPU() : 
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


        /** PRIVATE UTILITIES **/

        void GPU::RestoreRenderingDefaults()
        {            
            if (_renderWindow)
                glViewport(0, 0, _renderWindow->Width(), _renderWindow->Height());
            glActiveTexture(GL_TEXTURE0);
        }
    }
}