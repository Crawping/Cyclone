#include "Console.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Interfaces/IRenderable.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Primitives/Scene3D.h"
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
        void GPU::Vertices(VertexBuffer* vertices)
        {
            _vertices = vertices;
            if (_vertices)
                _vertices->Bind();
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        GPU::GPU() : 
            _fov(90),
            _renderPipeline(nullptr),
            _renderTarget(nullptr),
            _renderWindow(nullptr),
            _vertices(nullptr)
        {
            
        }

        GPU::~GPU()
        {

        }



        /** RENDERING UTILITIES **/
        void GPU::Clear(const Color4& color)
        {
            RestoreRenderingDefaults();
            _renderTarget->Clear(color);
            glClearBufferfv(GL_COLOR, 0, color.ToArray());
        }

        void GPU::Input(const Scene3D& scene)
        {
            scene.Bind();

            if (_renderPipeline)
            {

            const char* vpstr = "ViewProjection";
            int id = glGetUniformLocation(_renderPipeline->ID(), vpstr);
            if (id == -1)
                Console::WriteLine("Failed to find the ViewProjection uniform ID.");
            else
                glUniformMatrix4fv(id, 1, GL_FALSE, scene._viewProjection().ToArray());
            }
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
        string GPU::ReportRendererStatus() const
        {
            glFinish();
            GLenum status = glGetError();
            switch (status)
            {
                case RenderErrors::InsufficientMemory:          return "Not enough GPU memory exists for the attempted operation.";
                case RenderErrors::InvalidEnum:                 return "An invalid enumerator value was detected.";
                case RenderErrors::InvalidFramebufferOperation: return "The framebuffer currently in use is incomplete.";
                case RenderErrors::InvalidIndex:                return "An invalid index was detected.";
                case RenderErrors::InvalidOperation:            return "An invalid operation was attempted.";
                case RenderErrors::InvalidValue:                return "An out-of-bounds numeric argument was detected.";
                case RenderErrors::Nothing:                     return "No errors were detected.";
                case RenderErrors::StackOverflow:               return "Internal stack overflow detected.";
                case RenderErrors::StackUnderflow:              return "Internal stack underflow detected.";
                default:                                        return "An unknown rendering error was detected.";
            }
        }
    }
}