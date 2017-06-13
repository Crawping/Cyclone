/* CHANGELOG
 * Written by Josh Grooms on 20170613
 */

#pragma once
#include "EventHandler.h"
#include "include/cef_client.h"



class DisplayHandler:
    public CefClient,
    public CefDisplayHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler
{
    public:
        
        DisplayHandler():
            _renderHandler(new EventHandler())
        { 

        }
        ~DisplayHandler() { }


        CefRefPtr<CefDisplayHandler> GetDisplayHandler()    override { return this; }
        CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()  override { return this; }
        CefRefPtr<CefLoadHandler> GetLoadHandler()          override { return this; }
        CefRefPtr<CefRenderHandler> GetRenderHandler()      override { return _renderHandler; }

        void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override { }
        void OnAfterCreated(CefRefPtr<CefBrowser> browser) override { }
        bool DoClose(CefRefPtr<CefBrowser> browser) override
        {
            return true;
            //return false;
        }
        void OnBeforeClose(CefRefPtr<CefBrowser> browser) override { }
        void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode code, const CefString& msg, const CefString& url) override { }

        void CloseAllBrowsers(bool force) { }
        bool IsClosing() const { return false; }

    private:
        
        //EventHandler _renderHandler;
        CefRefPtr<CefRenderHandler> _renderHandler;

        IMPLEMENT_REFCOUNTING(DisplayHandler);
};
