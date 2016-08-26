#include "BasicRenderer.h"
#include "CGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Spatial/Geometry.h"



namespace Renderers
{

    /** CONSTRUCTOR & DESTRUCTOR **/
    BasicRenderer::BasicRenderer(const string& title) : 
        _canContinue(true),
        ClearColor(Color4::Gray),
        Renderer(nullptr),
        RenderScene(nullptr),
        RenderPipeline(nullptr),
        RenderWindow(nullptr)
    {
        if (!cglLoadAPI())
        {
            _canContinue = false;
            return;
        }

        Renderer = new GPU();
        RenderWindow = new Window3D(Area(0, 0, 1024, 960), title);
        RenderPipeline = new ShaderPipeline("../../OpenGL/Shaders/Default.vsl", "../../OpenGL/Shaders/Default.psl");
        RenderScene = new Scene3D();

        Renderer->RenderPipeline(RenderPipeline);
        Renderer->RenderWindow(RenderWindow);
        Renderer->Scene(RenderScene);

        RenderWindow->OnClose.Register(this, &BasicRenderer::BreakEventLoop);
        RenderWindow->OnResize.Register(this, &BasicRenderer::CreateSizedResources);
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

            Renderer->Update();
            Renderer->Execute();
            Renderer->Present();
        }
    }



    /** UTILITIES **/
    void BasicRenderer::CreateSizedResources()
    {
        Area clientArea = RenderWindow->ClientArea();
        Transform view = Transform::Translation(Vector3(-clientArea.Scale() / 2.0f, -clientArea.Height / 2.0f));
        Transform projection = Transform::PerspectiveProjection
        (
            90,
            clientArea.Width / clientArea.Height,
            (clientArea.Height - 100.0f) / 2.0f,
            (clientArea.Height + 100.0f) / 2.0f
        );

        Renderer->Projection(projection);
        Renderer->View(view);
    }


}