#include "Window3D.h"
#include "Math/Vector2.h"
#include <Windows.h>


namespace Cyclone::Platform
{
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
        _id(0),
        _title("Cyclone Window"),
        DeviceContext(nullptr)
    {
        MSG message;
        WNDCLASS winClass;

        ZeroMemory(&winClass, sizeof(winClass));

        winClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        winClass.lpfnWndProc    = WindowMessageLoop;
        winClass.hInstance      = GetModuleHandle(NULL);
        winClass.lpszClassName  = TEXT("OpenGL");

        RegisterClass(&winClass);

        _id = 0;
        //_id = CreateWindowEx
        //(
        //    WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
        //    TEXT("OpenGL"),
        //    TEXT("OpenGL Window"),
        //    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        //    0, 0,
        //    (int)size.X, (int)size.Y,
        //    NULL,
        //    NULL,

        //);

        DeviceContext = GetDC(_id);
  
        PIXELFORMATDESCRIPTOR pixelFormat;
        ZeroMemory(&pixelFormat, sizeof(pixelFormat));

        pixelFormat.nSize       = sizeof(pixelFormat);
        pixelFormat.nVersion    = 1;
        pixelFormat.dwFlags     = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;
        pixelFormat.iPixelType  = PFD_TYPE_RGBA;
        pixelFormat.cColorBits  = 24;
        pixelFormat.cRedBits    = 8;
        pixelFormat.cGreenBits  = 8;
        pixelFormat.cBlueBits   = 8;
        pixelFormat.cDepthBits  = 32;

        int idxPixelFormat = ChoosePixelFormat(DeviceContext, &pixelFormat);
        SetPixelFormat(DeviceContext, idxPixelFormat, &pixelFormat);


    }

    Window3D::~Window3D()
    {
        if (DeviceContext)  { ReleaseDC(_id, DeviceContext); }
        if (_id)            { DestroyWindow(_id); }
        UnregisterClass(TEXT("CycloneWindow"), GetModuleHandle(NULL));
    }

}