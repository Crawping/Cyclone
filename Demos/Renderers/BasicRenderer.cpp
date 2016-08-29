#include "BasicRenderer.h"
#include "CGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"
//#include "Spatial/Geometry.h"
//#include "Geometry/Geometry.h"



namespace Renderers
{

    /** CONSTRUCTOR & DESTRUCTOR **/
    BasicRenderer::BasicRenderer(const string& title) : 
        _canContinue(true),
        ClearColor(Color4::Gray),
        Renderer(nullptr),
        RenderScene(nullptr),
        RenderPipeline(nullptr),
        RenderWindow(nullptr),
        Title(title)
    {
        if (!cglLoadAPI())
        {
            _canContinue = false;
            return;
        }

        Renderer = new GPU();        
    }

    BasicRenderer::~BasicRenderer()
    {
        if (RenderScene)    { delete RenderScene; }
        if (RenderPipeline) { delete RenderPipeline; }
        if (RenderWindow)   { delete RenderWindow; }
        if (Renderer)       { delete Renderer; }

        cglClearAPI();
    }

    

    /** EVENT LOOP **/
    void BasicRenderer::Execute()
    {
        while (CanContinue())
        {
            RenderWindow->ProcessEvent();
            Renderer->Clear(ClearColor);

            UpdateScene();
            Renderer->Execute();
            Renderer->Present();
        }
    }



    /** INITIALIZATION UTILITIES **/
    void BasicRenderer::CreateRenderingWindow()
    {
        RenderWindow = new Window3D(Area(0, 0, 1024, 960), Title);
        Renderer->RenderWindow(RenderWindow);

        RenderWindow->OnClose.Register(this, &BasicRenderer::BreakEventLoop);
        RenderWindow->OnResize.Register(this, &BasicRenderer::CreateSizedResources);
    }
    void BasicRenderer::CreateSceneResources()
    {
        RenderScene = new Scene3D();
        Renderer->Scene(RenderScene);
    }
    void BasicRenderer::CreateShaderPipeline()
    {
        RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Default.psl");
        Renderer->RenderPipeline(RenderPipeline);
    }
    void BasicRenderer::CreateSizedResources()
    {
        Area clientArea = RenderWindow->ClientArea();
        Transform view = Transform::Translation(Vector3(-clientArea.Scale() / 2.0f, -clientArea.Height / 2.0f));
        Transform projection = Transform::PerspectiveProjection
        (
            90,
            clientArea.Width / clientArea.Height,
            (clientArea.Height - 500.0f) / 2.0f,
            (clientArea.Height + 1000.0f) / 2.0f
        );

        Renderer->Projection(projection);
        Renderer->View(view);
    }
    void BasicRenderer::Initialize()
    {
        CreateRenderingWindow();
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