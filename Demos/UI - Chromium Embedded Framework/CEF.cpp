/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#include "BasicRenderer.h"
#include "DisplayHandler.h"

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

        const Window3D* Window() const { return RenderWindow; }

        Program():
            BasicRenderer(Area(0, 0, 1024, 960), "UI - CEF"),
            Cube()
        {
            
            Initialize();
        }



    protected:

        Entity3D        Cube;
        //EventHandler    Events;

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

            RenderScene->Insert(Cube);
            RenderScene->Update(Cube);
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline
            (
                "../Renderers/Shaders/BlinnPhong.vsl",
                "../Renderers/Shaders/BlinnPhong.psl"
            );
        }
};


class ProgramCEF: 
    public CefApp, 
    public CefBrowserProcessHandler
{
    public:
        
        //ProgramCEF(const Program& app): Application(app) { }
        ProgramCEF() { }

        virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
        {
            return this;
        }

        void OnContextInitialized() override
        {
            //CefRefPtr<CefCommandLine> cmds = CefCommandLine::GetGlobalCommandLine();
            //bool useViews = cmds->HasSwitch("use-views");
            //cmds->AppendSwitch("off-screen-rendering-enabled");
            //cmds->AppendSwitch("enable-gpu");

            //CefRefPtr<DisplayHandler> handler(new DisplayHandler());
            //CefBrowserSettings settings;

            //string url = cmds->GetSwitchValue("url");
            //if (url.empty()) { url = "http://www.google.com"; }

            //CefWindowInfo winSettings;
            //winSettings.windowless_rendering_enabled = true;
            ////winSettings.SetAsWindowless((HWND)Application.Window()->ID());
            //winSettings.SetAsWindowless(nullptr);

            //CefBrowserHost::CreateBrowser(winSettings, handler, url, settings, nullptr);
        }

    private:

        //const Program& Application;

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
    //settings.external_message_pump = true;

    //CefRefPtr<ProgramCEF> cefApp(new ProgramCEF(app));
    CefRefPtr<ProgramCEF> cefApp(new ProgramCEF());
    CefInitialize(cefArgs, settings, cefApp.get(), nullptr);


    CefRefPtr<CefCommandLine> cmds = CefCommandLine::GetGlobalCommandLine();
    bool useViews = cmds->HasSwitch("use-views");
    cmds->AppendSwitch("off-screen-rendering-enabled");
    cmds->AppendSwitch("enable-gpu");

    CefRefPtr<DisplayHandler> handler(new DisplayHandler());
    CefBrowserSettings browserSettings;

    string url = cmds->GetSwitchValue("url");
    if (url.empty()) { url = "http://www.google.com"; }

    Program app;

    CefWindowInfo winSettings;
    winSettings.windowless_rendering_enabled = true;
    winSettings.SetAsWindowless((HWND)app.Window()->ID());
    //winSettings.SetAsWindowless(nullptr);

    CefBrowserHost::CreateBrowser(winSettings, handler, url, browserSettings, nullptr);


    //CefInitialize(cefArgs, settings, nullptr, nullptr);
    CefDoMessageLoopWork();

    app.Execute();
    CefShutdown();
    return 0;
}