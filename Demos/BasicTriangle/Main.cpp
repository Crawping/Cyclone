
#include "CGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Spatial/Geometry.h"

using namespace Cyclone::OpenGL;
using namespace Cyclone::Platform;



class Program
{
    public:
        Program() : 
            _canContinue(true),
            Renderer(nullptr),
            RenderWindow(nullptr),
            RenderPipeline(nullptr)
        {
            if (!cglLoadAPI())
            {
                _canContinue = false;
                return;
            }

            Renderer = new GPU();
            RenderWindow = new Window3D(Area(0, 0, 1024, 960), "Basic Triangle Rendering");
            RenderPipeline = new ShaderPipeline("../../OpenGL/Shaders/Default.vsl", "../../OpenGL/Shaders/Default.psl");
            RenderScene = new Scene3D();

            Renderer->RenderPipeline(RenderPipeline);
            Renderer->RenderWindow(RenderWindow);
            Renderer->Scene(RenderScene);

            CreateSizedResources();

            Triangle = new Mesh3D(Geometry::Triangle());
            Triangle->Scale(100, 100).Translate(512 - 50, 480 - 50);

            RenderScene->Add(*Triangle);

            RenderWindow->OnClose.Register(this, &Program::BreakEventLoop);
            RenderWindow->OnResize.Register(this, &Program::CreateSizedResources);
        }

        ~Program()
        {
            if (RenderPipeline) { delete RenderPipeline; }
            if (RenderWindow) { delete RenderWindow; }
            if (Renderer) { delete Renderer; }

            cglClearAPI();
        }


        void BreakEventLoop()
        {
            _canContinue = false;
        }
        void CreateSizedResources()
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
        void Execute()
        {
            while (_canContinue)
            {
                RenderWindow->ProcessEvent();
                Renderer->Clear(Color4::Blue);
                Renderer->Update();
                Renderer->Execute();
                Renderer->Present();
            }
        }


    private:
        bool _canContinue;

        GPU*            Renderer;
        Scene3D*        RenderScene;
        ShaderPipeline* RenderPipeline;
        Window3D*       RenderWindow;
        Mesh3D*         Triangle;


};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}