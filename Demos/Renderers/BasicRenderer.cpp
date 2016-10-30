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
    BasicRenderer::BasicRenderer(const Area& displayArea, const string& title, uint nsamples) :
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
    void BasicRenderer::CreateSceneResources()
    {
        RenderScene = new Scene3D();
        RenderScene->IsStencilTestEnabled(false)
            .Pipeline(RenderPipeline)
            .Projection(&Projection)
            .Target(RenderTarget)
            .View(&View);
    }
    void BasicRenderer::CreateShaderPipeline()
    {
        RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Default.psl");
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
    }
    void BasicRenderer::Initialize()
    {
        CreateShaderPipeline();
        CreateSizedResources();
        CreateSceneResources();
    }



    /** PROTECTED UTILITIES **/
    void BasicRenderer::Render()
    {
        if (RenderScene)
        {
            Renderer->Scene(RenderScene);
            Renderer->Update();
            Renderer->Execute();
        }
        //Renderer->Execute();
    }
    void BasicRenderer::UpdateScene()
    {

    }

}
