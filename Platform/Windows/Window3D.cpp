#include "Console.h"
#include "Math/Vector2.h"
#include "Window3D.h"
#include <Windows.h>



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
            MSG message;
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
        }

        Window3D::~Window3D()
        {
            if (Internals->ID)  { DestroyWindow(Internals->ID); }
            UnregisterClass(TEXT("OpenGL"), GetModuleHandle(NULL));
            if (Internals)      { delete Internals; }
        }

    }
}