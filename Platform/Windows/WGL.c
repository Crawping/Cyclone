#include "WGL.h"
#include <stdio.h>
#include <Windows.h>



/** WGL FUNCTION POINTERS **/
PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString     = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs    = NULL;
PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval            = NULL;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv  = NULL;



/** WGL RESOURCES **/
HDC LoadingContext                      = NULL;
HWND LoadingWindow                      = NULL;
static HINSTANCE LibraryHandle          = NULL;
static RenderContext TemporaryContext   = NULL;



/** INTERNAL UTILITIES **/
static LRESULT CALLBACK WindowMessageHandler(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_SIZE:       break;
        case WM_CLOSE:      PostQuitMessage(0); return 0;
        default:            break;
    }

    return DefWindowProc(win, msg, wparam, lparam);
}

static int InitializeLoadingContext()
{
    LoadingContext = GetDC(LoadingWindow);

    PIXELFORMATDESCRIPTOR pixelFormat;
    ZeroMemory(&pixelFormat, sizeof(pixelFormat));

    pixelFormat.nSize           = sizeof(pixelFormat);
    pixelFormat.nVersion        = 1;
    pixelFormat.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormat.iPixelType      = PFD_TYPE_RGBA;
    pixelFormat.cColorBits      = 24;

    if (!SetPixelFormat(LoadingContext, ChoosePixelFormat(LoadingContext, &pixelFormat), &pixelFormat))
    {
        fprintf(stderr, "Failed to set the pixel format for the loading context.\n");
        return 0;
    }

    TemporaryContext = wglCreateContext(LoadingContext);
    if (!wglMakeCurrent(LoadingContext, TemporaryContext))
    {
        fprintf(stderr, "Failed to initialize the temporary rendering context.\n");
        return 0;
    }

    return 1;
}
static int InitializeLoadingWindow()
{
    WNDCLASS winClass;
    ZeroMemory(&winClass, sizeof(winClass));
    
    winClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    winClass.hInstance      = GetModuleHandle(NULL);
    winClass.lpfnWndProc    = WindowMessageHandler;
    winClass.lpszClassName  = TEXT("LoadingWindowWGL");
    winClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    
    if (!RegisterClass(&winClass))
    {
        fprintf(stderr, "Failed to register the API loading window class.\n");
        return 0;
    }

    LoadingWindow = CreateWindowEx
    (
        WS_EX_OVERLAPPEDWINDOW,
        TEXT("LoadingWindowWGL"),
        TEXT("WGL API Loading Window"),
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        0, 0, 1, 1,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (!LoadingWindow)
    {
        fprintf(stderr, "Failed to create the API loading window.\n");
        return 0;
    }

    return 1;
}





int wglLoadFunctions()
{
    if (!InitializeLoadingWindow() || !InitializeLoadingContext())
        return 0;

    LibraryHandle = LoadLibrary(L"opengl32.dll");
    if (!LibraryHandle)
    {
        fprintf(stderr, "Failed to load the OpenGL library 'opengl32.dll'.\n");
        return 0;
    }

    wglCreateContextAttribs     = (PFNWGLCREATECONTEXTATTRIBSARBPROC)glGetFunctionPointer("wglCreateContextAttribsARB");
    wglGetExtensionsString      = (PFNWGLGETEXTENSIONSSTRINGARBPROC)glGetFunctionPointer("wglGetExtensionsStringARB");
    wglGetPixelFormatAttribiv   = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)glGetFunctionPointer("wglGetPixelFormatAttribivARB");
    wglSwapInterval             = (PFNWGLSWAPINTERVALEXTPROC)glGetFunctionPointer("wglSwapInterval");

    FreeLibrary(LibraryHandle);
    LibraryHandle = NULL;
    wglDeleteContext(TemporaryContext);
    TemporaryContext = NULL;

    return 1;
}


void wglDestroyResources()
{
    if (LoadingContext) { ReleaseDC(LoadingWindow, LoadingContext); }
    if (LoadingWindow)  { DestroyWindow(LoadingWindow); }

    LoadingContext = NULL;
    LoadingWindow = NULL;

    UnregisterClass(TEXT("LoadingWindowWGL"), GetModuleHandle(NULL));
}