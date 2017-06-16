/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#include "CEF.h"
#include "EventHandler.h"
#include "GPU.h"



Program::Program():
    AdvancedRenderer(Area(0, 0, 1920, 1080), "UI - CEF"),
    _isNavigationEnabled(false)
{
    IsFreeLookEnabled = false;
    RenderWindow->IsTrackingKeyRepeat(true);
    RenderWindow->OnButtonPress.Register(this, &Program::ProcessButtonPress);
    RenderWindow->OnButtonRelease.Register(this, &Program::ProcessButtonRelease);

    Initialize();
}



/** UTILITIES **/
void Program::Execute()
{
    bool runCEF = true;
    while (CanContinue())
    {
        RenderWindow->ProcessEvent();
        CefDoMessageLoopWork();
        UpdateScene();
        Render();
        Renderer->Present();
    }
}



/** PROTECTED UTILITIES **/
void Program::CreateSceneResources()
{
    AdvancedRenderer::CreateSceneResources();

    _cube = Create<Entity3D>("Cube");
    _cube->
         Geometry(Mesh3D::Cube(true))
        .PrimaryColor(Color4::Gray)
        .SecondaryColor(Color4::White)
        .SpecularPower(10)
        .Translate(Vector3(RenderWindow->ClientArea().Scale() / 2.0f, 50))
        .Scale(200)
        .Pitch(Constants::Pi<float> / 4)
        .Yaw(Constants::Pi<float> / 4);

    _image = Create<Texture3D, Vector4, TextureFormats, TextureTargets>
    (
        "Browser", Constructor<Texture3D, Vector4, TextureFormats, TextureTargets>(),
        Vector4(RenderWindow->ClientArea().Scale()),
        TextureFormats::Byte4,
        TextureTargets::Texture2D
    );
    _image->MakeResident();

    _browser = Create<Entity3D>("Browser");
    _browser->
         Ambience(1)
        .Geometry(Mesh3D::Quad(true))
        .Position(Vector3(RenderWindow->ClientArea().Scale() / 2.0f, -1.0f))
        .PrimaryColor(Color4::White)
        .SecondaryColor(Color4::White)
        .SpecularPower(1)
        .Scale(RenderWindow->ClientArea().Scale())
        .Texture(&*_image);

    RenderScene->Insert(*_cube);
    RenderScene->Insert(*_browser);
}
void Program::UpdateScene()
{
    _cube->Rotate(Vector3(0.0f, 0.01f, 0.0f));
    RenderScene->Update(*_cube);
    AdvancedRenderer::UpdateScene();
}
void Program::ProcessButtonPress(const PointerClickEvent& evt)
{
    if (evt.Button == PointerButtons::Button002)
        IsFreeLookEnabled = true;
}
void Program::ProcessButtonRelease(const PointerClickEvent& evt)
{
    if (evt.Button == PointerButtons::Button002)
        IsFreeLookEnabled = false;
}
void Program::ProcessKeyPress(const KeyboardEvent& evt)
{
    if (_isNavigationEnabled || evt.Key == KeyboardKeys::F1)
        AdvancedRenderer::ProcessKeyPress(evt);
    else if (evt.Key == KeyboardKeys::Alt)
        _isNavigationEnabled = true;
}
void Program::ProcessKeyRelease(const KeyboardEvent& evt)
{
    if (evt.Key == KeyboardKeys::Alt)
        _isNavigationEnabled = false;
    else if (_isNavigationEnabled || evt.Key == KeyboardKeys::F1)
        AdvancedRenderer::ProcessKeyRelease(evt);
}
void Program::ProcessPointerMotion(const PointerMotionEvent& evt)
{
    AdvancedRenderer::ProcessPointerMotion(evt);
    _cursorPosition = CalculatePointerInWorld( (_browser->Position() - View.Position()).Norm() );
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
