#include "CGL.h"
#include "Console.h"
#include "GPU.h"
#include "GraphicsSettings.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Interfaces/IBindable.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/IRenderStage.h"
#include "Interfaces/ITransformation3D.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Scenes/Scene3D.h"
#include "Windows/WGL.h"



namespace Cyclone
{
    using namespace Utilities;

    namespace Platform
    {

        /** PROPERTIES **/
        GPU& GPU::CullingMode(CullingModes value)
        {
            if (value == CullingMode())         { return *this; }

            if (value && CullingMode())
                glCullFace(value);
            else if (!value && CullingMode())
                glDisable(GL_CULL_FACE);
            else
            {
                glEnable(GL_CULL_FACE);
                glCullFace(value);
            }
            
            _settings.CullingMode = value;
            return *this;
        }
        GPU& GPU::IsBlendEnabled(bool value)
        {
            if (value == IsBlendEnabled())          { return *this; }
            else if (!value && IsBlendEnabled())    { glDisable(GL_BLEND); }
            else
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            _settings.IsBlendEnabled = value;
            return *this;
        }
        GPU& GPU::IsDepthTestEnabled(bool value)
        {
            if (value == IsDepthTestEnabled())      { return *this; }
            else if (!value && IsDepthTestEnabled())
            {
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_DEPTH_CLAMP);
            }
            else
            {
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_DEPTH_CLAMP);
                glDepthFunc(GL_LESS);
            }

            _settings.IsDepthTestEnabled = value;
            return *this;
        }
        GPU& GPU::IsStencilTestEnabled(bool value)
        {
            if (value == _settings.IsStencilTestEnabled) { return *this; }

            if (!_settings.IsStencilTestEnabled && value)
            {
                glStencilMask(~0);
                glEnable(GL_STENCIL_TEST);
                glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
            }
            else if (_settings.IsStencilTestEnabled && !value)
                glDisable(GL_STENCIL_TEST);

            _settings.IsStencilTestEnabled = value;
            return *this;
        }
        void GPU::Pipeline(GraphicsPipeline* pipeline)
        {
            if (pipeline == _settings.Pipeline) { return; }

            _settings.Pipeline = pipeline;
            if (_settings.Pipeline)
                _settings.Pipeline->Bind();
        }
        void GPU::Projection(ITransformation3D* projection)
        {
            _settings.Projection = projection;
        }
        void GPU::Scene(IScene* scene, int slot)
        {
            _renderScene = scene;
        }
        void GPU::Target(FrameBuffer* target, int slot)
        {
            if (target == _settings.Target) { return; }

            _settings.Target = target;
            if (_settings.Target)
                _settings.Target->Bind(slot);
        }
        void GPU::View(ITransformation3D* view)
        {
            _settings.View = view;
        }
        void GPU::Window(Window3D* window)
        {
            if (window == _renderWindow) { return; }

            _renderWindow = window;
            if (_renderWindow)
                _renderWindow->Bind();
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        GPU::GPU() :
            _renderWindow(nullptr),
            _renderScene(nullptr)
        {
            _settings.IsBlendEnabled        = false;
            _settings.IsDepthTestEnabled    = false;
            _settings.IsStencilTestEnabled  = false;
        }
        GPU::~GPU()
        {

        }



        /** RENDERING UTILITIES **/
        void GPU::Clear(const Color4& color, float depth, int stencil)
        {
            RestoreRenderingDefaults();
            if (_settings.Target)
                _settings.Target->Clear(color);
            else
            {
                glClearBufferfv(GL_COLOR, 0, color.ToArray());
                glClearBufferfv(GL_DEPTH, 0, &depth);
            }
        }
        void GPU::Configure(const GraphicsSettings& settings)
        {            
            CullingMode(settings.CullingMode);
            IsBlendEnabled(settings.IsBlendEnabled);
            IsDepthTestEnabled(settings.IsDepthTestEnabled);
            IsStencilTestEnabled(settings.IsStencilTestEnabled);
            Pipeline(settings.Pipeline);
            Projection(settings.Projection);
            Target(settings.Target);
            View(settings.View);
        }
        void GPU::Present()
        {
            if (!_renderWindow) { return; }

            if (_settings.Target)
                _settings.Target->Blit(0, _settings.Target->DisplayArea(), _renderWindow->ClientArea());

            _renderWindow->Present();
        }
        void GPU::Execute()
        {
            if (_renderScene)
            {
                const auto& stages = _renderScene->Stages();
                for (uint a = 0; a < stages.Count(); a++)
                {
                    IRenderStage& ctStage = stages(a);
                    Configure(ctStage.Settings());

                    for (BufferBinding b : ctStage.Buffers())
                        b.Buffer.Bind(b.Slot);
                    
                    ctStage.Render();
                }
            }
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

        List<string> GPU::QueryExtensions() const
        {
            List<string> extensions;

            int numExtensions = 0;
            glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
            for (int a = 0; a < numExtensions; a++)
                extensions.Append(string((const char*)glGetStringi(GL_EXTENSIONS, a)));

            return extensions;
        }



        /** UNIFORM DATA ACCESSORS **/
        int GPU::GetUniformID(const string& name)                                   const
        {
            return glGetUniformLocation(Pipeline()->ID(), name.c_str());
        }
        void GPU::SetUniform(const string& name, const Color4& value)               const
        {
            int varID = GetUniformID(name);
            if (varID != -1)
                glUniform4f(varID, value.R, value.G, value.B, value.A);
        }
        void GPU::SetUniform(const string& name, const ITransformation3D& value)    const
        {
            int varID = GetUniformID(name);
            if (varID != -1)
                glUniformMatrix4fv(varID, 1, false, value.ToMatrix4x4().ToArray());
        }



        /** PRIVATE UTILITIES **/
        void GPU::RestoreRenderingDefaults()
        {
            if (_settings.Projection && _settings.View)
            {
                PerFrame data =
                {
                    _settings.Projection->ToMatrix4x4(),
                    _settings.View->ToMatrix4x4(),
                    Vector3::One,
                    0,
                };

                PerFrameBuffer.Set(0, data);
            }

            if (_renderWindow)
                glViewport(0, 0, _renderWindow->ClientArea().Width, _renderWindow->ClientArea().Height);

            glActiveTexture(GL_TEXTURE0);
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
