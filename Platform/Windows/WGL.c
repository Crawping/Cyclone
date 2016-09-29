#include "Windows/WGL.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>



/** WGL FUNCTION POINTERS **/
PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString     = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs    = NULL;
PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval            = NULL;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv  = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC       wglChoosePixelFormat       = NULL;




/** WGL RESOURCES **/
HDC LoadingDeviceContext                = NULL;
HGLRC LoadingRenderContext              = NULL;
HGLRC TemporaryRenderContext            = NULL;
HWND LoadingWindow                      = NULL;

const PIXELFORMATDESCRIPTOR DefaultPixelFormat =
{
    sizeof(PIXELFORMATDESCRIPTOR),                                  // nSize
    1,                                                              // nVersion
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,     // dwFlags
    PFD_TYPE_RGBA,                                                  // iPixelType
    32,                                                             // cColorBits
    8,                                                              // cRedBits
    0,                                                              // cRedShift
    8,                                                              // cGreenBits
    0,                                                              // cGreenShift
    8,                                                              // cBlueBits
    0,                                                              // cBlueShift
    8,                                                              // cAlphaBits
    0,                                                              // cAlphaShift
    0,                                                              // cAccumBits
    0,                                                              // cAccumRedBits
    0,                                                              // cAccumGreenBits
    0,                                                              // cAccumBlueBits
    0,                                                              // cAccumAlphaBits
    24,                                                             // cDepthBits
    8,                                                              // cStencilBits
    0,                                                              // cAuxBuffers
    PFD_MAIN_PLANE,                                                 // iLayerType       (deprecated & ignored)
    0,                                                              // bReserved
    0,                                                              // dwLayerMask      (deprecated & ignored)
    0,                                                              // dwVisibleMask
    0,                                                              // dwDamageMask     (deprecated & ignored)
};

const int DefaultContextSettings[] =
{
    WGL_CONTEXT_FLAGS_ARB,          WGL_CONTEXT_DEBUG_BIT_ARB,
    WGL_CONTEXT_MAJOR_VERSION_ARB,  4,
    WGL_CONTEXT_MINOR_VERSION_ARB,  4,
    WGL_CONTEXT_PROFILE_MASK_ARB,   WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    NULL,
};

const int DefaultPixelAttributes[] =
{
    WGL_SUPPORT_OPENGL_ARB,         GL_TRUE,
    WGL_PIXEL_TYPE_ARB,             WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB,           WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB,             32,
    WGL_ALPHA_BITS_ARB,             8,
    WGL_DEPTH_BITS_ARB,             24,
    WGL_STENCIL_BITS_ARB,           8,
    WGL_DOUBLE_BUFFER_ARB,          GL_TRUE,
    WGL_SAMPLE_BUFFERS_ARB,         GL_TRUE,
    WGL_SAMPLES_ARB,                4,
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

static void DestroyLoadingWindow()
{
	if (LoadingRenderContext)
		wglMakeCurrent(LoadingDeviceContext, NULL);

	if (LoadingRenderContext)	{ wglDeleteContext(LoadingRenderContext); }
	if (TemporaryRenderContext) { wglDeleteContext(TemporaryRenderContext); }
	if (LoadingDeviceContext)	{ ReleaseDC(LoadingWindow, LoadingDeviceContext); }
	if (LoadingWindow)			{ DestroyWindow(LoadingWindow); }

	LoadingDeviceContext	= NULL;
	LoadingRenderContext	= NULL;
	LoadingWindow			= NULL;
	TemporaryRenderContext	= NULL;

	UnregisterClass(TEXT("LoadingWindowWGL"), GetModuleHandle(NULL));
}

/// <summary> Creates and initializes the Windows Forms window used to load OpenGL function pointers and rendering contexts. </summary>
/// <returns> An integer Boolean whose value is logically false if any errors were encountered. </returns>
static int CreateLoadingWindow()
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

    LoadingDeviceContext = GetDC(LoadingWindow);
    if (!SetPixelFormat(LoadingDeviceContext, ChoosePixelFormat(LoadingDeviceContext, &DefaultPixelFormat), &DefaultPixelFormat))
    {
        DestroyLoadingWindow();
        fprintf(stderr, "Failed to set the pixel format for the loading context.\n");
        return 0;
    }

    LoadingRenderContext = wglCreateContext(LoadingDeviceContext);
    if (!wglMakeCurrent(LoadingDeviceContext, LoadingRenderContext))
    {
        DestroyLoadingWindow();
        fprintf(stderr, "Failed to initialize the temporary rendering context.\n");
        return 0;
    }

    wglLoadFunctions();
    return 1;
}



/** API FUNCTIONS **/
_window3D* wglCreateWindow(const int* pixelAttributes, WNDPROC msgLoop)
{
    if (!CreateLoadingWindow())
        return NULL;

    DestroyLoadingWindow();

	WNDCLASS winClass;
	ZeroMemory(&winClass, sizeof(winClass));

    winClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    winClass.hInstance      = GetModuleHandle(NULL);
    winClass.lpfnWndProc    = msgLoop;
    winClass.lpszClassName  = TEXT("WindowWGL");
    winClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClass(&winClass))
	{
		fprintf(stderr, "Failed to register the 3D loading window class.\n");
		return NULL;
	}

    _window3D* win = calloc(1, sizeof(_window3D));

	win->ID = CreateWindowEx
	(
		WS_EX_OVERLAPPEDWINDOW,
		TEXT("WindowWGL"),
		TEXT("WGL API Loading Window"),
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 1024, 960,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (!win->ID)
	{
        wglDestroyWindow(win);
		fprintf(stderr, "Failed to create the 3D window.\n");
		return NULL;
	}

    win->DeviceContext = GetDC(win->ID);

    float fAttribs[] = { 0.0f, 0.0f };
    int idxPixelFormat = 0;
    UINT nformats = 0;

    if (!wglChoosePixelFormat(win->DeviceContext, pixelAttributes, fAttribs, 1, &idxPixelFormat, &nformats))
        fprintf(stderr, "Failed to find an advanced pixel format.");
    else if (!SetPixelFormat(win->DeviceContext, idxPixelFormat, &DefaultPixelFormat))
    {
        fprintf(stderr, "Failed to set the advanced pixel format.");
        idxPixelFormat = ChoosePixelFormat(win->DeviceContext, &DefaultPixelFormat);
    }

    if (!SetPixelFormat(win->DeviceContext, idxPixelFormat, &DefaultPixelFormat))
    {
        wglDestroyWindow(win);
        fprintf(stderr, "Failed to set the pixel format for the 3D rendering window.");
        return NULL;
    }

    win->RenderContext = wglCreateContext(win->DeviceContext);
    if (!wglMakeCurrent(win->DeviceContext, win->RenderContext))
    {
        wglDestroyWindow(win);
        fprintf(stderr, "Failed to initialize the temporary rendering context.\n");
        return NULL;
    }

    if (!wglLoadFunctions())
    {
        wglDestroyWindow(win);
        return NULL;
    }    

	return win;
}

void wglDestroyWindow(_window3D* window)
{
    if (!window) { return; }

    if (window->RenderContext)  { wglDeleteContext(LoadingRenderContext); }
    if (window->DeviceContext)  { ReleaseDC(LoadingWindow, LoadingDeviceContext); }
    if (window->ID)             { DestroyWindow(LoadingWindow); }

    UnregisterClass(TEXT("WindowWGL"), GetModuleHandle(NULL));
    free(window);
}

//int wglLoadAPI()
//{
//    if (!CreateLoadingWindow() || !InitializeLoadingContext())
//        return 0;
//
//    if (!wglLoadAPI())
//        return 0;
//
//    DestroyLoadingWindow();
//
//    if (!CreateLoadingWindow() || !FinalizeLoadingContext())
//        return 0;
//
//    if (!wglLoadAPI())
//        return 0;
//
//    return 1;
//}

int wglLoadFunctions()
{
   	HINSTANCE libHandle = LoadLibrary(L"opengl32.dll");
	if (!libHandle)
	{
		fprintf(stderr, "Failed to load the OpenGL library 'opengl32.dll'.\n");
		return 0;
	}

	wglCreateContextAttribs		= (PFNWGLCREATECONTEXTATTRIBSARBPROC)glGetFunctionPointer("wglCreateContextAttribsARB");
	wglGetExtensionsString      = (PFNWGLGETEXTENSIONSSTRINGARBPROC)glGetFunctionPointer("wglGetExtensionsStringARB");
    wglGetPixelFormatAttribiv   = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)glGetFunctionPointer("wglGetPixelFormatAttribivARB");
    wglSwapInterval             = (PFNWGLSWAPINTERVALEXTPROC)glGetFunctionPointer("wglSwapInterval");
    wglChoosePixelFormat        = (PFNWGLCHOOSEPIXELFORMATARBPROC)glGetFunctionPointer("wglChoosePixelFormatARB");

    if (!wglCreateContextAttribs)
    {
		FreeLibrary(libHandle);
        fprintf(stderr, "Failed to load the WGL function pointers.\n");
        return 0;
    }

	FreeLibrary(libHandle);
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



/** FIRST PASS **/
// Create loading window
// Get device context
// Choose simple pixel format
// Describe pixel format?
// Set simple pixel format
// Create advanced render context
// Make context current
// Load WGL extensions


/** SECOND PASS **/
// Make NULL the current context
// Destroy the rendering context
// Destroy the device context
// Destroy the loading window
// Create a new window
// Get the device context
// Choose advanced pixel format
// Describe pixel format?
// Set advanced pixel format
// Create advanced render context
// Make advanced context current
// Load WGL extensions