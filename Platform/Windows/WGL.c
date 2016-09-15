#include "Windows/WGL.h"
#include <stdio.h>
#include <Windows.h>



/** WGL FUNCTION POINTERS **/
PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString     = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs    = NULL;
PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval            = NULL;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv  = NULL;



/** WGL RESOURCES **/
HDC LoadingDeviceContext                = NULL;
HGLRC LoadingRenderContext              = NULL;
HGLRC TemporaryRenderContext            = NULL;
HWND LoadingWindow                      = NULL;
static HINSTANCE LibraryHandle          = NULL;

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

/// <summary> Destroys the temporary rendering context and replaces it with a more advanced one. </summary>
/// <returns> An integer Boolean whose value is logically false if any errors were encountered. </returns>
static int FinalizeLoadingContext()
{
    LoadingRenderContext = wglCreateContextAttribs(LoadingDeviceContext, NULL, DefaultContextSettings);
    if (!LoadingRenderContext)
    {
        fprintf(stderr, "Failed to create the advanced OpenGL rendering context.");
        return 0;
    }

    wglMakeCurrent(LoadingDeviceContext, NULL);
    wglDeleteContext(TemporaryRenderContext);
    TemporaryRenderContext = NULL;

    if (!wglMakeCurrent(LoadingDeviceContext, LoadingRenderContext))
    {
        fprintf(stderr, "Failed to bind the advanced OpenGL rendering context to the loading window.");
        return 0;
    }

    return 1;
}

/// <summary> Creates the temporary legacy rendering context required to load more advanced OpenGL functionality. </summary>
/// <returns> An integer Boolean whose value is logically false if any errors were encountered. </returns>
static int InitializeLoadingContext()
{
    LoadingDeviceContext = GetDC(LoadingWindow);

    if (!SetPixelFormat(LoadingDeviceContext, ChoosePixelFormat(LoadingDeviceContext, &DefaultPixelFormat), &DefaultPixelFormat))
    {
        fprintf(stderr, "Failed to set the pixel format for the loading context.\n");
        return 0;
    }

    TemporaryRenderContext = wglCreateContext(LoadingDeviceContext);
    if (!wglMakeCurrent(LoadingDeviceContext, TemporaryRenderContext))
    {
        fprintf(stderr, "Failed to initialize the temporary rendering context.\n");
        return 0;
    }

    return 1;
}

/// <summary> Creates and initializes the Windows Forms window used to load OpenGL function pointers and rendering contexts. </summary>
/// <returns> An integer Boolean whose value is logically false if any errors were encountered. </returns>
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
    
    if (!FinalizeLoadingContext())
        return 0;
    
    wglGetExtensionsString      = (PFNWGLGETEXTENSIONSSTRINGARBPROC)glGetFunctionPointer("wglGetExtensionsStringARB");
    wglGetPixelFormatAttribiv   = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)glGetFunctionPointer("wglGetPixelFormatAttribivARB");
    wglSwapInterval             = (PFNWGLSWAPINTERVALEXTPROC)glGetFunctionPointer("wglSwapInterval");

    FreeLibrary(LibraryHandle);
    LibraryHandle = NULL;    

    return 1;
}


void wglDestroyResources()
{
    if (LoadingRenderContext)   { wglDeleteContext(LoadingRenderContext); }
    if (TemporaryRenderContext) { wglDeleteContext(TemporaryRenderContext); }
    if (LoadingDeviceContext)   { ReleaseDC(LoadingWindow, LoadingDeviceContext); }
    if (LoadingWindow)          { DestroyWindow(LoadingWindow); }

    LoadingDeviceContext    = NULL;
    LoadingRenderContext    = NULL;
    LoadingWindow           = NULL;
    TemporaryRenderContext  = NULL;

    UnregisterClass(TEXT("LoadingWindowWGL"), GetModuleHandle(NULL));
}