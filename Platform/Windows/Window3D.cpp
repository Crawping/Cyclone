#include "Console.h"
#include "Math/Vector2.h"
#include "Windows/Window3D.h"
#include <Windows.h>



namespace Cyclone
{
    namespace Platform
    {

        struct Window3D::_window3D
        {
            HWND    ID;
            Area    DisplayArea;
            string  Title;
        };



        static LRESULT CALLBACK WindowMessageLoop(HWND win, uint msg, WPARAM wparam, LPARAM lparam)
        {
            switch (msg)
            {
                case WM_SIZE:       break;
                case WM_CLOSE:      PostQuitMessage(0); return 0;
                default:            break;
            }

            return DefWindowProc(win, msg, wparam, lparam);
        }



        Window3D::Window3D(const Area& displayArea, const string& title) : 
            _internal(new _window3D{ NULL, displayArea, title })
        {
            MSG message;
            WNDCLASS winClass;

            ZeroMemory(&winClass, sizeof(winClass));

            winClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            winClass.lpfnWndProc    = WindowMessageLoop;
            winClass.hInstance      = GetModuleHandle(NULL);
            winClass.lpszClassName  = TEXT("OpenGL");

            RegisterClass(&winClass);

            _internal->ID = CreateWindowEx
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
            if (_internal->ID) { DestroyWindow(_internal->ID); }
            UnregisterClass(TEXT("OpenGL"), GetModuleHandle(NULL));
            if (_internal)
                delete _internal;
        }

    }
}