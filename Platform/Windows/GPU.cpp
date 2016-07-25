#include "Console.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Interfaces/IRenderable.h"
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
        void GPU::Clear(const Color4& color)
        {
            RestoreRenderingDefaults();
            glClearBufferfv(GL_COLOR, 0, color.ToArray());
        }

        void GPU::Input(const IRenderableEntity& entity)
        {
            //uint idx;
            //PerEntity data;
            //const void* entKey = (const void*)&entity;

            //if (BufferIndices.count(entKey))
            //{
            //    idx = BufferIndices[entKey];
            //    data = PerEntityBuffer[idx];
            //}
            //else
            //    idx = PerEntityBuffer.Count();

            //BufferIndices[entKey] = idx;
            ////if (entity.GetEntityData(data))
            ////    PerEntityBuffer.Set(idx, data);
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