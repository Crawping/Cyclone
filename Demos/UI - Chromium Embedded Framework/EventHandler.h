/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#pragma once
#include "GL/OpenGL.h"
#include "Imaging/Bitmap.h"
#include "IO/Console.h"
#include "Spatial/Volume.h"
#include "Textures/Texture3D.h"

#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"
#include "include/cef_render_handler.h"

using namespace Cyclone::Utilities;
using namespace Cyclone::OpenGL;



class EventHandler: 
    public CefClient,
    public CefDisplayHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler,
    public CefRenderHandler
{
    public:

        bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                override
        {
            rect.x = 0;
            rect.y = 0;
            rect.width = 3840;
            rect.height = 2160;
            return true;
        }
        bool GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& info)              override
        {
            CefRect rect; GetRootScreenRect(browser, rect);
            info.rect = rect;
            info.available_rect = rect;
            return true;
        }
        bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int x, int y, int& sx, int& sy)  override
        {
            return false;
        }
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                      override
        {
            rect.x = 0;
            rect.y = 0;
            rect.width = _image->Width();
            rect.height = _image->Height();
            return true;
        }

        CefRefPtr<CefDisplayHandler> GetDisplayHandler()                                    override { return this; }
        CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()                                  override { return this; }
        CefRefPtr<CefLoadHandler> GetLoadHandler()                                          override { return this; }
        CefRefPtr<CefRenderHandler> GetRenderHandler()                                      override { return this; }



        EventHandler(Texture3D* image): _image(image) { }



        void OnAfterCreated(CefRefPtr<CefBrowser> browser)                                      override { }
        void OnBeforeClose(CefRefPtr<CefBrowser> browser)                                       override { }
        void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, CefRenderHandler::CursorType type, const CefCursorInfo& cursorInfo)  override
        {
            Console::WriteLine("Cursor");
        }
        void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser, const CefRange& range, const CefRenderHandler::RectList& bounds)               override
        {
            Console::WriteLine("Composition");
        }
        void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode code, const CefString& msg, const CefString& url)          override { }
        void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height)   override
        {
            CEF_REQUIRE_UI_THREAD()
            if (type != PET_VIEW || !_image->ID()) { return; }

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

                _image->Update();
            }
        }
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


        void CloseAllBrowsers(bool force) { }
        bool DoClose(CefRefPtr<CefBrowser> browser)                                             override
        {
            return true;
        }
        bool IsClosing() const { return false; }
        bool StartDragging(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> data, CefRenderHandler::DragOperationsMask allowedOps, int x, int y)                                   override
        {
            Console::WriteLine("Begin Drag");
            return false;
        }
        void UpdateDragCursor(CefRefPtr<CefBrowser> browser, CefRenderHandler::DragOperation operation)                                                                                 override
        {
            Console::WriteLine("Update Drag");
        }


        IMPLEMENT_REFCOUNTING(EventHandler);

    private:

        Texture3D* _image;
};