/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#pragma once
#include "IO/Console.h"
#include "include/cef_render_handler.h"

using namespace Cyclone::Utilities;



class EventHandler: public CefRenderHandler
{
    public:

        bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                override
        {
            rect.x = 0;
            rect.y = 0;
            rect.width = 3840;
            rect.height = 2160;
            return true;
            //return false;
        }
        bool GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& info)              override
        {
            CefRect rect; GetRootScreenRect(browser, rect);
            info.rect = rect;
            return true;
            //return false;
        }
        bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int x, int y, int& sx, int& sy)  override
        {
            return false;
        }
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                      override
        {
            rect.x = 0;
            rect.y = 0;
            rect.width = 1024;
            rect.height = 960;
            return true;
            //return false;
        }


        EventHandler() { }


        void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, CefRenderHandler::CursorType type, const CefCursorInfo& cursorInfo) override
        {
            Console::WriteLine("Cursor");
        }

        void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser, const CefRange& range, const CefRenderHandler::RectList& bounds) override
        {
            Console::WriteLine("Composition");
        }

        void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height)   override
        {
            Console::WriteLine("Paint");
        }

        void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)                                                                                                                      override
        {
            Console::WriteLine("Popup");
        }

        void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)                                                                                                            override
        {

        }
        void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser, double x, double y)                                                                                                   override
        {

        }

        bool StartDragging(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> data, CefRenderHandler::DragOperationsMask allowedOps, int x, int y)                                   override
        {
            return false;
        }
        void UpdateDragCursor(CefRefPtr<CefBrowser> browser, CefRenderHandler::DragOperation operation)                                                                                 override
        {

        }


        IMPLEMENT_REFCOUNTING(EventHandler);

    private:

        
};