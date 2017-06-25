#include "BasicRenderer.h"
#include "CGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Models/Model3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "Spatial/Camera.h"



namespace Cyclone
{
    namespace Renderers
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        BasicRenderer::BasicRenderer(const Area& displayArea, const string& title, uint nsamples) :
            _canContinue(true),
            ClearColor(Color4::Gray),
            Renderer(nullptr),
            RenderScene(nullptr),
            RenderTarget(nullptr),
            RenderWindow(nullptr),
		    SamplesMSAA(nsamples),
            Title(title)
        {
            Renderer		= new GPU();
		    RenderWindow	= new Window3D(displayArea, title, nsamples);

		    if (!cglLoadAPI())
		    {
			    _canContinue = false;
			    return;
		    }

		    RenderWindow->OnClose.Subscribe(this, &BasicRenderer::BreakEventLoop);
		    RenderWindow->OnResize.Subscribe(this, &BasicRenderer::CreateSizedResources);
		    Renderer->Window(RenderWindow);
        }
        BasicRenderer::~BasicRenderer()
        {
            if (RenderScene)    { delete RenderScene; }
            if (RenderTarget)   { delete RenderTarget; }
            if (RenderWindow)   { delete RenderWindow; }
            if (Renderer)       { delete Renderer; }

            cglClearAPI();
        }



        /** EVENT LOOP **/
        void BasicRenderer::Execute()
        {
            while (_canContinue)
            {
                RenderWindow->ProcessEvent();
                UpdateScene();
                Render();
                Renderer->Present();
            }
        }



        /** INITIALIZATION UTILITIES **/
        void BasicRenderer::CreateRenderTarget()
        {
            if (RenderTarget)
                delete RenderTarget;

            Vector2 szWin = RenderWindow->ClientArea().Scale();
            RenderTarget = new FrameBuffer
		    (
			    Vector4(szWin.X, szWin.Y, 1.0f, SamplesMSAA),
			    TextureFormats::Byte4,
			    TextureFormats::DepthStencil,
			    SamplesMSAA ? TextureTargets::Texture2DMS : TextureTargets::Texture2D
		    );
        }
        void BasicRenderer::CreateScene()
        {
            RenderScene = new Scene3D();
            RenderScene->
                 IsBlendEnabled(true)
                .IsDepthTestEnabled(true)
                .IsStencilTestEnabled(false)
                .Pipeline(&*_pipeline)
                .Projection(&Projection)
                .Target(RenderTarget)
                .View(&View);
        }
        void BasicRenderer::CreateSceneResources()
        {

        }
        void BasicRenderer::CreateShaderPipeline()
        {
            _pipeline = Create
            (
                "BlinnPhong", Constructor<ShaderPipeline, string, string>(),
                string("../../Renderers/Shaders/BlinnPhong.vsl"),
                string("../../Renderers/Shaders/BlinnPhong.psl")
            );
        }
        void BasicRenderer::CreateSizedResources()
        {
            CreateRenderTarget();
            CreateTransformations();

            if (RenderScene)
                RenderScene->Target(RenderTarget);
        }
        void BasicRenderer::CreateTransformations()
        {
            Area clientArea = RenderWindow->ClientArea();
            View
                .Orientation(Vector3::Zero)
                .Position(Vector3(clientArea.Scale() / 2.0f, clientArea.Height / 2.0f));

            Projection = Transform3D::PerspectiveProjection
            (
                90,
                clientArea.Width / clientArea.Height,
                1,
                4.0f * clientArea.Width
            );
        }
        void BasicRenderer::Initialize()
        {
            CreateShaderPipeline();
            CreateSizedResources();
            CreateScene();
            CreateSceneResources();
        }



        /** PROTECTED UTILITIES **/
        void BasicRenderer::Render()
        {
            if (RenderScene)
            {
                Renderer->Scene(RenderScene);
                Renderer->Update();
                Renderer->Clear(ClearColor);
                Renderer->Execute();
            }
        }
        void BasicRenderer::UpdateScene()
        {

        }

    }
}