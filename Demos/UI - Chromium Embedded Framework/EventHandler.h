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
        bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int x, int y, int& sx, int& sy)  override;
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                      override;

        CefRefPtr<CefDisplayHandler> GetDisplayHandler()                                    override { return this; }
        CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()                                  override { return this; }
        CefRefPtr<CefLoadHandler> GetLoadHandler()                                          override { return this; }
        CefRefPtr<CefRenderHandler> GetRenderHandler()                                      override { return this; }

        bool IsClosing()                                                                    const { return false; }



        /** CONSTRUCTOR **/
        EventHandler(Program& app);
        ~EventHandler();



        /** UTILITIES **/
        IMPLEMENT_REFCOUNTING(EventHandler);

        void CloseAllBrowsers(bool force) { }
        bool DoClose(CefRefPtr<CefBrowser> browser)                                             override
        {
            return true;
        }
        bool StartDragging(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> data, CefRenderHandler::DragOperationsMask allowedOps, int x, int y)                                   override
        {
            Console::WriteLine("Begin Drag");
            return false;
        }
        void UpdateDragCursor(CefRefPtr<CefBrowser> browser, CefRenderHandler::DragOperation operation)                                                                                 override
        {
            Console::WriteLine("Update Drag");
        }



        /** EVENT HANDLERS **/
        void OnAfterCreated(CefRefPtr<CefBrowser> browser)                                      override;
        void OnBeforeClose(CefRefPtr<CefBrowser> browser)                                       override;
        void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, CefRenderHandler::CursorType type, const CefCursorInfo& cursorInfo)  override
        {
            Console::WriteLine("Cursor");
        }
        void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser, const CefRange& range, const CefRenderHandler::RectList& bounds)               override
        {
            Console::WriteLine("Composition");
        }
        void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode code, const CefString& msg, const CefString& url)          override { }
        void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height)   override;
        void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)                              override
        {
            Console::WriteLine("Popup Show");
        }
        void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)                    override
        {
            Console::WriteLine("Popup Size");
        }
        void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser, double x, double y)           override
        {
            Console::WriteLine("Scroll Offset");
        }
        void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)               override { }

    private:

        CefRefPtr<CefBrowser>   _browser;
        //Texture3D*              _image;
        //Window3D*               _window;
        Program&                _app;


        void ProcessButtonPress(const PointerClickEvent& evt);
        void ProcessButtonRelease(const PointerClickEvent& evt);
        void ProcessKeyPress(const KeyboardEvent& evt);
        void ProcessKeyRelease(const KeyboardEvent& evt);
        void ProcessPointerMotion(const PointerMotionEvent& evt);

};