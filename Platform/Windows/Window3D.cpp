#include "Console.h"
#include "Math/Vector2.h"
#include "Utilities.h"
#include "Window3D.h"
#include "Windows/WGL.h"
#include <Windows.h>

using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;



/** INTERNAL DATA **/
const static PIXELFORMATDESCRIPTOR DefaultPixelFormat =
{
    sizeof(PIXELFORMATDESCRIPTOR),                                  // nSize
    1,                                                              // nVersion
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,     // dwFlags
    PFD_TYPE_RGBA,                                                  // iPixelType
    32,                                                             // cColorBits
    8,                                                              // cRedBits;
    0,                                                              // cRedShift;
    8,                                                              // cGreenBits;
    0,                                                              // cGreenShift;
    8,                                                              // cBlueBits;
    0,                                                              // cBlueShift;
    8,                                                              // cAlphaBits;
    0,                                                              // cAlphaShift;
    0,                                                              // cAccumBits;
    0,                                                              // cAccumRedBits
    0,                                                              // cAccumGreenBi
    0,                                                              // cAccumBlueBit
    0,                                                              // cAccumAlphaBi
    24,                                                             // cDepthBits;
    8,                                                              // cStencilBits;
    0,                                                              // cAuxBuffers;
    PFD_MAIN_PLANE,                                                 // iLayerType;
    0,                                                              // bReserved;
    0,                                                              // dwLayerMask;
    0,                                                              // dwVisibleMask
    0,                                                              // dwDamageMask;
};

const static int DefaultContextSettings[] =
{
    WGL_CONTEXT_FLAGS_ARB,          WGL_CONTEXT_DEBUG_BIT_ARB,
    WGL_CONTEXT_MAJOR_VERSION_ARB,  4,
    WGL_CONTEXT_MINOR_VERSION_ARB,  4,
    WGL_CONTEXT_PROFILE_MASK_ARB,   WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    NULL,
};



/** INTERNAL FUNCTIONS **/
/// <summary> Handles any events posted to a specific window on the Windows platform. </summary>
/// <param name="win"> The handle of the window to which the event is being posted. </param>
/// <param name="msg"> The type of event that is being posted. </param>
/// <param name="wparam"> An argument of unknown significance. </param>
/// <param name="lparam"> An argument of unknown significance. </param>
/// <returns> An argument of unknown significance. </returns>
static LRESULT CALLBACK WindowMessageLoop(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Window3D* win3D = (Window3D*)GetWindowLong(win, GWLP_USERDATA);

    if (win3D)
    {
        switch (msg)
        {
            case WM_CLOSE:
                win3D->Close();
                break;
            case WM_DESTROY:
                break;

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                break;

            case WM_KEYUP:
            case WM_SYSKEYUP:
                break;

            case WM_LBUTTONDBLCLK:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
                break;

            case WM_MBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
                break;

            case WM_RBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
                break;

            case WM_XBUTTONDBLCLK:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
                break;

            case WM_MOUSEMOVE:
                POINTS pts = MAKEPOINTS(lparam);
                win3D->UpdatePointerPosition(pts.x, pts.y);
                break;

            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
                break;

            case WM_SIZE:
                win3D->UpdateSize();
                break;

            default:            break;
        }
    }

    return DefWindowProc(win, msg, wparam, lparam);
}
/// <summary> Converts a standard text string into an equivalent wide-character one. </summary>
/// <param name="text"> A standard string of text. </param>
/// <returns> A string that is identical to the inputted one except composed of wide-characters. </returns>
static std::wstring str2wstr(const std::string& text)
{
    int length = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
    if (!length)
    {
        PostInfo("Failed to convert the inputted text.");
        return L"";
    }

    WCHAR* wtext = (WCHAR*)calloc(length + 1, sizeof(WCHAR));
    if (!MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wtext, length + 1))
    {
        free(wtext);
        PostInfo("Failed to convert the inputted text.");
        return L"";
    }

    return std::wstring(wtext);        
}



namespace Cyclone
{
    namespace Platform
    {

        struct Window3D::_window3D
        {
            HDC     DeviceContext;
            /// <summary> The native handle of the window. </summary>
            HWND    ID;
            HGLRC   RenderContext;
        };



        /** PROPERTIES **/
        Window3D& Window3D::Title(const string& title)
        {
            _title = title;
            SetWindowText(Internals->ID, str2wstr(title).c_str());
            return *this;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        Window3D::Window3D(const Area& displayArea, const string& title) :
            Internals(new _window3D{ NULL, NULL, NULL }),
            _isBordered(true),
            _isTrackingPointer(true),
            _title(title)
        {
            WNDCLASS winClass;
            
            ZeroMemory(&winClass, sizeof(winClass));

            winClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            winClass.lpfnWndProc    = WindowMessageLoop;
            winClass.hInstance      = GetModuleHandle(NULL);
            winClass.lpszClassName  = TEXT("OpenGL");

            RegisterClass(&winClass); 

            Internals->ID = CreateWindowEx
            (
                WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
                TEXT("OpenGL"),
                str2wstr(title).c_str(),
                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                (int)displayArea.X,     (int)displayArea.Y,
                (int)displayArea.Width, (int)displayArea.Height,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                NULL
            );

            SetWindowLong(Internals->ID, GWLP_USERDATA, (long)this);
            Internals->DeviceContext = GetDC(Internals->ID);

            int idxPixelFormat = ChoosePixelFormat(Internals->DeviceContext, &DefaultPixelFormat);
            if (!SetPixelFormat(Internals->DeviceContext, idxPixelFormat, &DefaultPixelFormat))
            {
                Console::WriteLine("Failed to set the pixel format for the 3D rendering window.");
                return;
            }

            UpdateSize();
            ShowWindow(Internals->ID, SW_SHOW);
        }

        Window3D::~Window3D()
        {
            if (Internals->RenderContext)
                wglDeleteContext(Internals->RenderContext);
            if (Internals->DeviceContext)
                ReleaseDC(Internals->ID, Internals->DeviceContext);

            if (Internals->ID)  { DestroyWindow(Internals->ID); }
            if (Internals)      { delete Internals; }

            UnregisterClass(TEXT("OpenGL"), GetModuleHandle(NULL));
        }


        
        /** PUBLIC UTILITIES **/
        void Window3D::Close()
        {
            PostQuitMessage(0);
            OnClose();
        }
        void Window3D::Fill(const Area& displayArea)
        {
            SetWindowPos(Internals->ID, 0, displayArea.X, displayArea.Y, displayArea.Width, displayArea.Height, SWP_NOZORDER);
        }
        bool Window3D::ProcessEvent()
        {
            MSG msg;
            if (PeekMessage(&msg, Internals->ID, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                    return false;
            }

            return true;
        }        



        /** INTERNAL UTILITIES **/
        void Window3D::UpdateSize()
        {
            RECT displayRect;
            GetWindowRect(Internals->ID, &displayRect);

            Area displayArea = Area
            (
                displayRect.left, displayRect.top,
                displayRect.right - displayRect.left,
                displayRect.bottom - displayRect.top
            );

            if (_displayArea == displayArea) { return; }
            
            RECT renderRect;
            GetClientRect(Internals->ID, &renderRect);

            _displayArea = displayArea;
            _clientArea = Area
            (
                renderRect.left, renderRect.top,
                renderRect.right - renderRect.left,
                renderRect.bottom - renderRect.top
            );

            OnResize();
        }
        void Window3D::UpdatePointerPosition(int x, int y)
        {
            if (!IsTrackingPointer())                                   { return; }
            if (x == PointerPosition().X && y == PointerPosition().Y)   { return; }

            Vector2 oldPosition = PointerPosition();
            _pointerPosition = Vector2(x, y);

            PointerMotion evt =
            {
                PointerPosition() - oldPosition,
                PointerPosition(),
            };
            OnPointerMotion(evt);
        }

        /** RENDERING UTILITIES **/
        void Window3D::Bind()               const { wglMakeCurrent(Internals->DeviceContext, LoadingRenderContext); }
        void Window3D::Present()            const { SwapBuffers(Internals->DeviceContext); }
        void Window3D::Unbind()             const { wglMakeCurrent(LoadingDeviceContext, LoadingRenderContext); }
    }
}