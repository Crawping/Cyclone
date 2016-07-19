#include "Console.h"
#include "Math/Vector2.h"
#include "Window3D.h"
#include "Windows/WGL.h"
#include <Windows.h>



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
    WGL_CONTEXT_MAJOR_VERSION_ARB,  3,
    WGL_CONTEXT_MINOR_VERSION_ARB,  2,
    WGL_CONTEXT_PROFILE_MASK_ARB,   WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    NULL,
};



static LRESULT CALLBACK WindowMessageLoop(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_SIZE:       break;
        case WM_CLOSE:      PostQuitMessage(0); return 0;
        default:            break;
    }

    return DefWindowProc(win, msg, wparam, lparam);
}



namespace Cyclone
{
    namespace Platform
    {

        struct Window3D::_window3D
        {
            HDC     DeviceContext;
            HWND    ID;
            HGLRC   RenderContext;
        };



        /** CONSTRUCTOR & DESTRUCTOR **/
        Window3D::Window3D(const Area& displayArea, const string& title) : 
            Internals(new _window3D{ NULL }),
            _displayArea(displayArea),
            _isBordered(true),
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
                TEXT("OpenGL Window"),
                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                (int)displayArea.X, (int)displayArea.Y,
                (int)displayArea.Width, (int)displayArea.Height,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                NULL
            );

            Internals->DeviceContext = GetDC(Internals->ID);

            int idxPixelFormat = ChoosePixelFormat(Internals->DeviceContext, &DefaultPixelFormat);
            SetPixelFormat(Internals->DeviceContext, idxPixelFormat, &DefaultPixelFormat);

            Internals->RenderContext = wglCreateContextAttribs(Internals->DeviceContext, NULL, DefaultContextSettings);
            if (!Internals->RenderContext)
                Console::WriteLine("Failed to load the advanced rendering context.");

            ShowWindow(Internals->ID, SW_SHOW);
        }

        Window3D::~Window3D()
        {
            if (Internals->RenderContext)
                wglDeleteContext(Internals->RenderContext);
            if (Internals->DeviceContext)
                ReleaseDC(Internals->ID, Internals->DeviceContext);

            if (Internals->ID)  { DestroyWindow(Internals->ID); }
            UnregisterClass(TEXT("OpenGL"), GetModuleHandle(NULL));
            if (Internals)      { delete Internals; }
        }



        bool Window3D::ProcessEvents()
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


        void* Window3D::GetDeviceContext()  const { return Internals->DeviceContext; }
        void* Window3D::GetRenderContext()  const { return Internals->RenderContext; }
        void* Window3D::GetWindowHandle()   const { return Internals->ID; }


        void Window3D::Bind()               const { wglMakeCurrent(Internals->DeviceContext, Internals->RenderContext); }
        void Window3D::Present()            const { SwapBuffers(Internals->DeviceContext); }
        void Window3D::Unbind()             const { wglMakeCurrent(LoadingDeviceContext, LoadingRenderContext); }
    }
}