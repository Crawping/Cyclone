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
    OnButtonPress = RenderWindow->OnButtonPress.Subscribe(this, &Program::ProcessButtonPress);
    OnButtonRelease = RenderWindow->OnButtonRelease.Subscribe(this, &Program::ProcessButtonRelease);

    Initialize();
}
Program::~Program()
{
    OnButtonPress.Cancel();
    OnButtonRelease.Cancel();
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

    auto cube = Create("Cube", Function<Mesh3D, bool>(&Mesh3D::Cube), true);
    auto browser = Create("Browser", Function<Mesh3D, bool>(&Mesh3D::Quad), true);

    _cube = Create<Entity3D>("Cube");
    _cube->
         Material(Create<Material3D>("Cube"))
        .Model(Create<Model3D>("Cube"))
        .Geometry(cube)
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
         Material(Create<Material3D>("Browser"))
        .Model(Create<Model3D>("Browser"))
        .Ambience(1)
        .Geometry(browser)
        .Position(Vector3(RenderWindow->ClientArea().Scale() / 2.0f, -1.0f))
        .PrimaryColor(Color4::White)
        .SecondaryColor(Color4::Black)
        .SpecularPower(1)
        .Scale(Vector3(RenderWindow->ClientArea().Scale(), RenderWindow->Width()))
        .Texture(_image);

    RenderScene->Insert(_cube);
    RenderScene->Insert(_browser);
}
void Program::UpdateScene()
{
    _cube->Rotate(Vector3(0.0f, 0.01f, 0.0f));
    RenderScene->Update(_cube);
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
    //_cursorRay = _browser()->Transform().Inverse() * LineSegment{ PointerWorldRay(0), PointerWorldRay(1) };
    _cursorPosition = CalculatePointerInWorld( (_browser->Position() - View.Position()).Norm() );

}



/** MAIN ENTRY POINT **/
int main(int nargs, char** args)
{
    CefEnableHighDPISupport();

    CefMainArgs cefArgs;
    if (CefExecuteProcess(cefArgs, nullptr, nullptr) >= 0) { return 0; }

    CefSettings settings;
    settings.no_sandbox = true;
    settings.windowless_rendering_enabled = true;

    Program app;
    CefRefPtr<EventHandler> handler(new EventHandler(app));
    CefInitialize(cefArgs, settings, handler.get(), nullptr);

    CefRefPtr<CefCommandLine> cmds = CefCommandLine::GetGlobalCommandLine();
    bool useViews = cmds->HasSwitch("use-views");

    string url = cmds->GetSwitchValue("url");
    if (url.empty()) { url = "http://www.google.com"; }

    CefWindowInfo winSettings;
    winSettings.windowless_rendering_enabled = true;
    winSettings.SetAsWindowless((HWND)app.Window()->ID());

    CefBrowserSettings browserSettings;
    CefBrowserHost::CreateBrowser(winSettings, handler, url, browserSettings, nullptr);

    app.Execute();
    CefShutdown();
    return 0;
}
