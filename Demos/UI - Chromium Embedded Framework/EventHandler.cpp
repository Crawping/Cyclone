#include "EventHandler.h"
#include "GL/OpenGL.h"



/** PROPERTIES **/
bool EventHandler::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    rect.x = 0;
    rect.y = 0;
    rect.width = 3840;
    rect.height = 2160;
    return true;
}
bool EventHandler::GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& info)
{
    CefRect rect; GetRootScreenRect(browser, rect);
    info.rect = rect;
    info.available_rect = rect;
    return true;
}
bool EventHandler::GetScreenPoint(CefRefPtr<CefBrowser> browser, int x, int y, int& sx, int& sy)
{
    return false;
}
bool EventHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    rect.x = 0;
    rect.y = 0;
    rect.width = _image->Width();
    rect.height = _image->Height();
    return true;
}



/** CONSTRUCTOR **/
EventHandler::EventHandler(Window3D* window, Texture3D* image):
    _browser(nullptr),
    _image(image),
    _window(window)
{
    _window->OnButtonPress.Register(this, &EventHandler::ProcessButtonPress);
    _window->OnButtonRelease.Register(this, &EventHandler::ProcessButtonRelease);
    _window->OnKeyPress.Register(this, &EventHandler::ProcessKeyPress);
    _window->OnKeyRelease.Register(this, &EventHandler::ProcessKeyRelease);
    _window->OnPointerMotion.Register(this, &EventHandler::ProcessPointerMotion);
}
EventHandler::~EventHandler()
{
    _browser = nullptr;
    _window->OnButtonPress.Remove(this, &EventHandler::ProcessButtonPress);
    _window->OnButtonRelease.Remove(this, &EventHandler::ProcessButtonRelease);
    _window->OnKeyPress.Remove(this, &EventHandler::ProcessKeyPress);
    _window->OnKeyRelease.Remove(this, &EventHandler::ProcessKeyRelease);
    _window->OnPointerMotion.Remove(this, &EventHandler::ProcessPointerMotion);
}



/** EVENT HANDLERS **/
void EventHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    _browser = browser;
}
void EventHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    _browser = nullptr;
}
void EventHandler::OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height)
{
    CEF_REQUIRE_UI_THREAD();
    if (!_image->ID()) { return; }

    for (auto& r : dirtyRects)
    {
        glTextureSubImage2D
        (
            _image->ID(),
            0, r.x, r.y,
            width, height,
            GL_BGRA,
            GL_UNSIGNED_INT_8_8_8_8_REV,
            buffer
        );
    }
}




void EventHandler::ProcessButtonPress(const PointerClickEvent& evt)
{
    if (!_browser) { return; }
    auto btn = (evt.Button == PointerButtons::Button001) ? MBT_LEFT : MBT_RIGHT;
    
    CefMouseEvent cevt;
    const Vector2& ppos = _window->PointerPosition();

    cevt.x = ppos.X;
    cevt.y = ppos.Y;
    
    _browser->GetHost()->SendMouseClickEvent(cevt, btn, false, 1);
    Console::WriteLine("Button Down Dispatched!");
}
void EventHandler::ProcessButtonRelease(const PointerClickEvent& evt)
{
    if (!_browser) { return; }
    auto btn = (evt.Button == PointerButtons::Button001) ? MBT_LEFT : MBT_RIGHT;

    CefMouseEvent cevt;
    const Vector2& ppos = _window->PointerPosition();

    cevt.x = ppos.X;
    cevt.y = ppos.Y;

    _browser->GetHost()->SendMouseClickEvent(cevt, btn, true, 1);
    Console::WriteLine("Button Up Dispatched!");
}
void EventHandler::ProcessKeyPress(const KeyboardEvent& evt)
{

}
void EventHandler::ProcessKeyRelease(const KeyboardEvent& evt)
{

}
void EventHandler::ProcessPointerMotion(const PointerMotionEvent& evt)
{

}