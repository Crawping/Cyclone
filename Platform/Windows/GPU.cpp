#include "CGL.h"
#include "Console.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Geometry/Scene3D.h"
#include "Interfaces/IBindable.h"
#include "Interfaces/IRenderable.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Windows/WGL.h"



namespace Cyclone
{
    using namespace Utilities;

    namespace Platform
    {

        /** PROPERTIES **/
        void GPU::Projection(const Transform& projection)
        {
            _projection = projection;
        }
        void GPU::RenderPipeline(GraphicsPipeline* pipeline)
        {
            _renderPipeline = pipeline;
            if (_renderPipeline)
                _renderPipeline->Bind();
        }
        void GPU::RenderTarget(FrameBuffer* framebuffer, int slot)
        {
            _renderTarget = framebuffer;
            if (_renderTarget)
                _renderTarget->Bind(slot);
        }
        void GPU::RenderWindow(Window3D* window)
        {
            _renderWindow = window;
            if (_renderWindow)
                _renderWindow->Bind();
        }
        void GPU::Scene(Scene3D* scene, int slot)
        {
            _renderScene = scene;
        }
        void GPU::View(const Transform& view)
        {
            _view = view;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        GPU::GPU() :
            _fov(90),
            _renderPipeline(nullptr),
            _renderTarget(nullptr),
            _renderWindow(nullptr),
            _renderScene(nullptr)
        {

        }
        GPU::~GPU()
        {

        }



        /** RENDERING UTILITIES **/
        void GPU::Clear(const Color4& color)
        {
            RestoreRenderingDefaults();
            if (_renderTarget)
                _renderTarget->Clear(color);
            else
                glClearBufferfv(GL_COLOR, 0, color.ToArray());
        }
        void GPU::Present()
        {
            if (!_renderWindow) { return; }

            if (_renderTarget)
                _renderTarget->Blit(0, _renderTarget->DisplayArea(), _renderWindow->ClientArea());

            _renderWindow->Present();
        }
        void GPU::Execute()
        {
            if (_renderScene)
                _renderScene->Render();
        }
        void GPU::Update()
        {
            PerFrameBuffer.Update();
            PerFrameBuffer.Bind(1);

            if (_renderScene)
                _renderScene->Update();
        }



        /** GENERAL UTILITIES **/        
        string GPU::Report() const
        {
            return ReportErrors();
        }
        bool GPU::SupportsExtension(const string& extension) const
        {
            int numExtensions = 0;
            glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
            for (int a = 0; a < numExtensions; a++)
            {
                const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, a);
                if (string(ext) == extension)
                    return true;
            }
            return false;
        }



        /** PRIVATE UTILITIES **/
        void GPU::RestoreRenderingDefaults()
        {
            PerFrame data =
            {
                _projection.ToArray(),
                _view.ToArray(),
                Vector3::One,
                0,
            };

            PerFrameBuffer.Set(0, data);

            if (_renderWindow)
                glViewport(0, 0, _renderWindow->ClientArea().Width, _renderWindow->ClientArea().Height);

            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_CULL_FACE);
        }
        string GPU::ReportErrors() const
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
