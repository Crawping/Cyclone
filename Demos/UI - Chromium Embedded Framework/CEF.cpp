/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#include "CEF.h"
#include "EventHandler.h"
#include "GPU.h"



Program::Program():
    AdvancedRenderer(Area(0, 0, 1024, 960), "UI - CEF"),
    BrowserImage(nullptr),
    Cube()
{
    IsFreeLookEnabled = false;
    RenderWindow->OnButtonPress.Register(this, &Program::ProcessButtonPress);
    RenderWindow->OnButtonRelease.Register(this, &Program::ProcessButtonRelease);

    Initialize();
}

void Program::Execute()
{
    bool runCEF = true;
    while (CanContinue())
    {
        RenderWindow->ProcessEvent();
        //if (runCEF) { CefDoMessageLoopWork(); }
        runCEF = !runCEF;
        CefDoMessageLoopWork();

        UpdateScene();
        Render();
        Renderer->Present();

        //Console::WriteLine(Renderer->Report());
    }
}

void Program::CreateSceneResources() 
{
    AdvancedRenderer::CreateSceneResources();

    Cube
        .Geometry(Mesh3D::Cube(true))
        .PrimaryColor(Color4::Blue)
        .Translate(Vector3(512, 480, 50))
        .Scale(200)
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
        .Position(Vector3(RenderWindow->ClientArea().Scale() / 2.0f, -1.0f))
        .PrimaryColor(Color4::Green)
        .Scale(RenderWindow->ClientArea().Scale())
        .Texture(BrowserImage);

    RenderScene->Insert(Cube);
    RenderScene->Insert(BrowserPage);
}
void Program::CreateShaderPipeline() 
{
    RenderPipeline = new ShaderPipeline
    (
        "../Renderers/Shaders/Default.vsl",
        "../3D - Image Display/TexturedShading.psl"
    );
}
void Program::UpdateScene() 
{
    Cube.Rotate(Vector3(0.0f, 0.01f, 0.0f));
    RenderScene->Update(Cube);
    //RenderScene->Update(BrowserPage);
    AdvancedRenderer::UpdateScene();
}
void Program::ProcessButtonPress(const PointerClickEvent& evt)
{
    if (evt.Button == PointerButtons::Button003)
        IsFreeLookEnabled = true;
}
void Program::ProcessButtonRelease(const PointerClickEvent& evt)
{
    if (evt.Button == PointerButtons::Button003)
        IsFreeLookEnabled = false;
}
void Program::ProcessPointerMotion(const PointerMotionEvent& evt)
{
    AdvancedRenderer::ProcessPointerMotion(evt);
    _cursorPosition = CalculatePointerInWorld( (BrowserPage.Position() - View.Position()).Norm() );
    Console::WriteLine("Cursor Position: " + _cursorPosition.ToString());
}

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

    CefRefPtr<EventHandler> handler(new EventHandler(app));
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