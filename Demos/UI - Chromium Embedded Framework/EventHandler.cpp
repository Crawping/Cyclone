#include "CEF.h"
#include "EventHandler.h"
#include "GL/OpenGL.h"



/** INTERNAL UTILITIES **/
static int TranslateModifiers(const KeyboardEvent evt)
{
    int mods = 0;
    if (evt.State.IsPressed(KeyboardKeys::Alt))         { mods |= EVENTFLAG_ALT_DOWN; }
    if (evt.State.IsPressed(KeyboardKeys::Control))     { mods |= EVENTFLAG_CONTROL_DOWN; }
    if (evt.State.IsPressed(KeyboardKeys::Shift))       { mods |= EVENTFLAG_SHIFT_DOWN; }
    return mods;
}




/** PROPERTIES **/
bool EventHandler::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    rect.x = 0;
    rect.y = 0;
    //rect.width = 2560;
    //rect.height = 1440;
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
    rect.width = _app.Image()->Width();
    rect.height = _app.Image()->Height();
    return true;
}



/** CONSTRUCTOR **/
EventHandler::EventHandler(Program& app):
    _app(app),
    _browser(nullptr)
{
    _app.Window()->OnButtonPress.Register(this, &EventHandler::ProcessButtonPress);
    _app.Window()->OnButtonRelease.Register(this, &EventHandler::ProcessButtonRelease);
    _app.Window()->OnKeyPress.Register(this, &EventHandler::ProcessKeyPress);
    _app.Window()->OnKeyRelease.Register(this, &EventHandler::ProcessKeyRelease);
    _app.Window()->OnPointerMotion.Register(this, &EventHandler::ProcessPointerMotion);
}
EventHandler::~EventHandler()
{
    _browser = nullptr;
    _app.Window()->OnButtonPress.Remove(this, &EventHandler::ProcessButtonPress);
    _app.Window()->OnButtonRelease.Remove(this, &EventHandler::ProcessButtonRelease);
    _app.Window()->OnKeyPress.Remove(this, &EventHandler::ProcessKeyPress);
    _app.Window()->OnKeyRelease.Remove(this, &EventHandler::ProcessKeyRelease);
    _app.Window()->OnPointerMotion.Remove(this, &EventHandler::ProcessPointerMotion);
}



/** EVENT HANDLERS **/
void EventHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    _browser = browser;
    _browser->GetHost()->SetWindowlessFrameRate(60);
}
void EventHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    _browser = nullptr;
}
void EventHandler::OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height)
{
    CEF_REQUIRE_UI_THREAD();
    if (!_app.Image()->ID()) { return; }

    for (auto& r : dirtyRects)
    {
        glTextureSubImage2D
        (
            _app.Image()->ID(),
            0, r.x, r.y,
            width, height,
            GL_BGRA,
            GL_UNSIGNED_INT_8_8_8_8_REV,
            buffer
        );
    }

    _app.UpdateBrowser();
}




void EventHandler::ProcessButtonPress(const PointerClickEvent& evt)
{
    if (!_browser || evt.Button == PointerButtons::Button002) { return; }
    auto btn = (evt.Button == PointerButtons::Button001) ? MBT_LEFT : 
        (evt.Button == PointerButtons::Button003) ? MBT_RIGHT : MBT_MIDDLE;

    const Vector2& ppos = _app.Window()->PointerPosition();

    CefMouseEvent cevt;
    cevt.x = ppos.X;
    cevt.y = ppos.Y;

    if (btn != MBT_MIDDLE)  { _browser->GetHost()->SendMouseClickEvent(cevt, btn, false, 1); }
    else
    {
        int delta = evt.Button == PointerButtons::Button004 ? -100 : 100;
        _browser->GetHost()->SendMouseWheelEvent(cevt, 0, delta);
    }
}
void EventHandler::ProcessButtonRelease(const PointerClickEvent& evt)
{
    if (!_browser || evt.Button == PointerButtons::Button002) { return; }
    auto btn = (evt.Button == PointerButtons::Button001)    ? MBT_LEFT : 
        (evt.Button == PointerButtons::Button003)           ? MBT_RIGHT : MBT_MIDDLE;

    const Vector2& ppos = _app.Window()->PointerPosition();

    CefMouseEvent cevt;
    cevt.x = ppos.X;
    cevt.y = ppos.Y;

    if (btn == MBT_MIDDLE)  { _browser->GetHost()->SendMouseWheelEvent(cevt, 0, 1); }
    else                    { _browser->GetHost()->SendMouseClickEvent(cevt, btn, true, 1); }
}
void EventHandler::ProcessKeyPress(const KeyboardEvent& evt)
{
    if (!_browser || _app.IsNavigationEnabled()) { return; }

    CefKeyEvent cevt;
    cevt.is_system_key      = false;
    cevt.modifiers          = TranslateModifiers(evt);
    cevt.native_key_code    = evt.Native;
    cevt.windows_key_code   = evt.Code;
    cevt.type               = (evt.Message == WM_CHAR) ? KEYEVENT_CHAR : KEYEVENT_RAWKEYDOWN;

    _browser->GetHost()->SendKeyEvent(cevt);

    Console::WriteLine("Key Down Dispatched!");
}
void EventHandler::ProcessKeyRelease(const KeyboardEvent& evt)
{
    if (!_browser || _app.IsNavigationEnabled()) { return; }

    CefKeyEvent cevt;
    cevt.is_system_key      = false;
    cevt.modifiers          = TranslateModifiers(evt);
    cevt.native_key_code    = evt.Native;
    cevt.windows_key_code   = evt.Code;
    cevt.type               = KEYEVENT_KEYUP;

    _browser->GetHost()->SendKeyEvent(cevt);
}
void EventHandler::ProcessPointerMotion(const PointerMotionEvent& evt)
{
    if (!_browser) { return; }
    CefMouseEvent cevt;

    cevt.x = evt.Position.X;
    cevt.y = evt.Position.Y;
    _browser->GetHost()->SendMouseMoveEvent(cevt, false);
}
