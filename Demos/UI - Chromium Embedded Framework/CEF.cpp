/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#include "BasicRenderer.h"
#include "EventHandler.h"
#include "GPU.h"

#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "include/cef_app.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;



class Program: public BasicRenderer
{
    public:

        Texture3D* Image()          { return BrowserImage; }
        const Window3D* Window()    const { return RenderWindow; }

        Program():
            BasicRenderer(Area(0, 0, 1024, 960), "UI - CEF"),
            BrowserImage(nullptr),
            Cube()
        {
            Initialize();
        }
        ~Program() { if (BrowserImage) { delete BrowserImage; } }


        void Execute() override
        {
            while (CanContinue())
            {
                RenderWindow->ProcessEvent();
                CefDoMessageLoopWork();
                UpdateScene();
                Render();
                Renderer->Present();

                Console::WriteLine(Renderer->Report());
            }
        }



    protected:

        Entity3D        Cube;
        Entity3D        BrowserPage;
        Texture3D*      BrowserImage;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Cube
                .Geometry(Mesh3D::Cube(true))
                .PrimaryColor(Color4::Blue)
                .Translate(Vector3(512, 480, 50))
                .Scale(Vector3(200, 200, 200))
                .Pitch(Constants::Pi<float> / 4)
                .Yaw(Constants::Pi<float> / 4);

            BrowserImage = new Texture3D
            (
                Vector4(RenderWindow->ClientArea().Scale()), 
                TextureFormats::Byte4, 
                TextureTargets::Texture2D
            );

            BrowserImage->MakeResident();

            BrowserPage
                .Geometry(Mesh3D::Quad(true))
                .Position(Vector3(RenderWindow->ClientArea().Scale() / 2.0f, 10.0f))
                .PrimaryColor(Color4::Green)
                .Scale(RenderWindow->ClientArea().Scale())
                .Texture(BrowserImage);

            RenderScene->Insert(Cube);
            RenderScene->Insert(BrowserPage);
        }

        void CreateShaderPipeline() override
        {
            //RenderPipeline = new ShaderPipeline
            //(
            //    "../Renderers/Shaders/BlinnPhong.vsl",
            //    "../Renderers/Shaders/BlinnPhong.psl"
            //);
            RenderPipeline = new ShaderPipeline
            (
                "../Renderers/Shaders/Default.vsl",
                "../3D - Image Display/TexturedShading.psl"
            );
        }

        void UpdateScene() override
        {
            Cube.Rotate(Vector3(0.0f, 0.01f, 0.0f));
            RenderScene->Update(Cube);
            BasicRenderer::UpdateScene();
        }
};


class ProgramCEF: 
    public CefApp, 
    public CefBrowserProcessHandler
{
    public:
        
        ProgramCEF() { }

        virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
        {
            return this;
        }

        void OnContextInitialized() override
        {

        }

    private:

        IMPLEMENT_REFCOUNTING(ProgramCEF);
};



int main(int nargs, char** args)
{
    CefEnableHighDPISupport();
    
    CefMainArgs cefArgs;
    if (CefExecuteProcess(cefArgs, nullptr, nullptr) >= 0) { return 0; }

    CefSettings settings;
    settings.no_sandbox = true;
    settings.windowless_rendering_enabled = true;

    CefRefPtr<ProgramCEF> cefApp(new ProgramCEF());
    CefInitialize(cefArgs, settings, cefApp.get(), nullptr);

    CefRefPtr<CefCommandLine> cmds = CefCommandLine::GetGlobalCommandLine();
    bool useViews = cmds->HasSwitch("use-views");

    Program app;

    CefRefPtr<EventHandler> handler(new EventHandler(app.Image()));
    CefBrowserSettings browserSettings;

    string url = cmds->GetSwitchValue("url");
    if (url.empty()) { url = "http://www.google.com"; }


    CefWindowInfo winSettings;
    winSettings.windowless_rendering_enabled = true;
    winSettings.SetAsWindowless((HWND)app.Window()->ID());

    CefBrowserHost::CreateBrowser(winSettings, handler, url, browserSettings, nullptr);

    app.Execute();
    CefShutdown();
    return 0;
}