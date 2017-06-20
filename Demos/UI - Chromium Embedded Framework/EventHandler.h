/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */
#pragma once

#include "Window3D.h"
#include "Imaging/Bitmap.h"
#include "IO/Console.h"
#include "Spatial/Volume.h"
#include "Textures/Texture3D.h"

#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"
#include "include/cef_render_handler.h"

using namespace Cyclone::Utilities;
using namespace Cyclone::OpenGL;
using namespace Cyclone::Platform;



class EventHandler: 
    public CefApp,
    public CefBrowserProcessHandler,
    public CefClient,
    public CefDisplayHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler,
    public CefRenderHandler
{
    public:

        /** PROPERTIES **/
        bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                override;
        bool GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& info)              override;
        /// <summary> Converts 2D client-space pixel coordinates into screen-space. </summary>
        bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int x, int y, int& sx, int& sy)  override;
        /// <summary> Gets a rectangle describing the window's client area in window-space pixel coordinates. </summary>
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                      override;

        CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()                      override { return this; }
        CefRefPtr<CefDisplayHandler> GetDisplayHandler()                                    override { return this; }
        CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()                                  override { return this; }
        CefRefPtr<CefLoadHandler> GetLoadHandler()                                          override { return this; }
        CefRefPtr<CefRenderHandler> GetRenderHandler()                                      override { return this; }



        /** CONSTRUCTOR **/
        EventHandler(Program& app);
        ~EventHandler();



        /** UTILITIES **/
        IMPLEMENT_REFCOUNTING(EventHandler);

        bool DoClose(CefRefPtr<CefBrowser> browser)                                             override;
        bool StartDragging(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> data, CefRenderHandler::DragOperationsMask allowedOps, int x, int y)   override;
        void UpdateDragCursor(CefRefPtr<CefBrowser> browser, CefRenderHandler::DragOperation operation)                                                 override;



        /** EVENT HANDLERS **/
        void OnAfterCreated(CefRefPtr<CefBrowser> browser)                                      override;
        void OnBeforeClose(CefRefPtr<CefBrowser> browser)                                       override;
        void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, CefRenderHandler::CursorType type, const CefCursorInfo& cursorInfo)  override;
        void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser, const CefRange& range, const CefRenderHandler::RectList& bounds)               override;
        void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode code, const CefString& msg, const CefString& url)          override;
        void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height)   override;
        void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)                              override;
        void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)                    override;
        void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser, double x, double y)           override;
        void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)               override;
        bool OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text)                          override;

    private:

        Program&                _app;
        CefRefPtr<CefBrowser>   _browser;

        Subscription<const PointerClickEvent&>      OnButtonPress;
        Subscription<const PointerClickEvent&>      OnButtonRelease;
        Subscription<const KeyboardEvent&>          OnKeyPress;
        Subscription<const KeyboardEvent&>          OnKeyRelease;
        Subscription<const PointerMotionEvent&>     OnPointerMotion;


        void ProcessButtonPress(const PointerClickEvent& evt);
        void ProcessButtonRelease(const PointerClickEvent& evt);
        void ProcessKeyPress(const KeyboardEvent& evt);
        void ProcessKeyRelease(const KeyboardEvent& evt);
        void ProcessPointerMotion(const PointerMotionEvent& evt);

};