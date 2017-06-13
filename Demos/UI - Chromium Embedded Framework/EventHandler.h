/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#pragma once
#include "include/cef_render_handler.h"



class EventHandler: public CefRenderHandler
{
    public:

        bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                override
        {
            return false;
        }
        bool GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& info)              override
        {
            return false;
        }
        bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int x, int y, int& sx, int& sy)  override
        {
            return false;
        }
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)                      override
        {
            return false;
        }

        void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, CefRenderHandler::CursorType type, const CefCursorInfo& cursorInfo) override
        {

        }

        void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser, const CefRange& range, const CefRenderHandler::RectList& bounds) override
        {

        }

        void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height)   override
        {

        }

        void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)                                                                                                                      override
        {

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



    private:

        
};