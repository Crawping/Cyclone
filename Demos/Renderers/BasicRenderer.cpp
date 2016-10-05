#include "BasicRenderer.h"
#include "CGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Spatial/Camera.h"



namespace Renderers
{

    /** CONSTRUCTOR & DESTRUCTOR **/
    BasicRenderer::BasicRenderer(const Area& displayArea, const string& title, int nsamples) :
        _canContinue(true),
        ClearColor(Color4::Gray),
        Renderer(nullptr),
        RenderPipeline(nullptr),
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

		RenderWindow->OnClose.Register(this, &BasicRenderer::BreakEventLoop);
		RenderWindow->OnResize.Register(this, &BasicRenderer::CreateSizedResources);
		Renderer->Window(RenderWindow);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_CLAMP);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    BasicRenderer::~BasicRenderer()
    {
        if (RenderScene)    { delete RenderScene; }
        if (RenderPipeline) { delete RenderPipeline; }
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
            Renderer->Clear(ClearColor);

            UpdateScene();
            Renderer->Execute();
            Renderer->Present();
        }
    }



    /** INITIALIZATION UTILITIES **/
    void BasicRenderer::CreateRenderTarget()
    {
        if (RenderTarget)
            delete RenderTarget;

        RenderTarget = new FrameBuffer
		(
			RenderWindow->ClientArea().Scale(),
			TextureFormats::Byte4,
			TextureFormats::DepthStencil,
			SamplesMSAA ? TextureTargets::Texture2DMS : TextureTargets::Texture2D
		);
        Renderer->Target(RenderTarget);
    }
    void BasicRenderer::CreateSceneResources()
    {
        RenderScene = new Scene3D();
        Renderer->Scene(RenderScene);
    }
    void BasicRenderer::CreateShaderPipeline()
    {
        RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Default.psl");
        Renderer->Pipeline(RenderPipeline);
    }
    void BasicRenderer::CreateSizedResources()
    {
        CreateRenderTarget();
        CreateTransformations();
    }
    void BasicRenderer::CreateTransformations()
    {
        Area clientArea = RenderWindow->ClientArea();
        View
            .Orientation(Vector3::Zero)
            .Position(Vector3(clientArea.Scale() / 2.0f, clientArea.Height / 2.0f));

        Projection = Transform::PerspectiveProjection
        (
            90,
            clientArea.Width / clientArea.Height,
            1,
            4.0f * clientArea.Width
        );

        Renderer->Projection(&Projection);
        Renderer->View(&View);
    }
    void BasicRenderer::Initialize()
    {
        CreateShaderPipeline();
        CreateSizedResources();
        CreateSceneResources();
    }



    /** PROTECTED UTILITIES **/
    void BasicRenderer::UpdateScene()
    {
        Renderer->Update();
    }

}
