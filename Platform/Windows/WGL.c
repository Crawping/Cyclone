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
/// <summary> A handle for the GDI device context bound to the loading window. </summary>
HDC LoadingDeviceContext                = NULL;
/// <summary> A handle for the OpenGL rendering context bound to the loading window and device context. </summary>
HGLRC LoadingRenderContext              = NULL;
/// <summary> A handle for the Windows Forms window that is created in order to load OpenGL function pointers. </summary>
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
	if (LoadingDeviceContext)	{ ReleaseDC(LoadingWindow, LoadingDeviceContext); }
	if (LoadingWindow)			{ DestroyWindow(LoadingWindow); }

	LoadingDeviceContext	= NULL;
	LoadingRenderContext	= NULL;
	LoadingWindow			= NULL;

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

	if (!LoadFunctionPointers())
	{
		DestroyLoadingWindow();
		return 0;
	}

    return 1;
}

static int LoadFunctionPointers()
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
    wglSwapInterval             = (PFNWGLSWAPINTERVALEXTPROC)glGetFunctionPointer("wglSwapIntervalEXT");
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



/** API FUNCTIONS **/
_window3D* wglCreateWindow(const WindowSettings* settings)
{
    /* NOTES ON THE CODE BELOW
     *
     * On the Windows platform, getting an advanced OpenGL rendering context is a really weird procedure. It's basically a very hacky
     * workaround/fix for what amounts to a chicken-and-egg problem, but it's well known that what follows is the only way to do it.
     * The problem is this: an active OpenGL context MUST exist before you can load WGL functions, but WGL functions MUST be used to
     * create advanced OpenGL contexts. The solution arises because of the word 'advanced' in that last part. We can create a basic
     * context that supports the loading of WGL functions and then create a more advanced context to replace it.
     *
     * Except that alone doesn't work because the advanced rendering context requires different pixel format settings that can only be
     * set on any given desktop window ONCE. After these settings are applied to a window, which is a necessary step in the creation
     * of the basic context, they can never ever change again for the entire life of the window. That means we have to destroy the
     * entire window and recreate it from scratch just so we have the WGL functions available to create the rendering context we want
     * (e.g. for multisample antialiasing).
     */

	if (settings->PixelAttributes)
	{
		if (!CreateLoadingWindow())
			return NULL;
		DestroyLoadingWindow();
	}

	WNDCLASS winClass;
	ZeroMemory(&winClass, sizeof(winClass));

    winClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    winClass.hInstance      = GetModuleHandle(NULL);
    winClass.lpfnWndProc    = settings->MessageHandler;
    winClass.lpszClassName  = settings->ClassName;
    winClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClass(&winClass))
	{
		fprintf(stderr, "Failed to register the 3D loading window class.\n");
		return NULL;
	}

    _window3D* win = calloc(1, sizeof(_window3D));
	win->ClassName = settings->ClassName;
	win->ID = CreateWindowEx
	(
        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		settings->ClassName,
		settings->Title,
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		settings->DisplayArea.left,
		settings->DisplayArea.top,
		settings->DisplayArea.right - settings->DisplayArea.left,
		settings->DisplayArea.bottom - settings->DisplayArea.top,
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

	int idxPixelFormat = 0;
	if (settings->PixelAttributes)
	{
		float fAttribs[] = { 0.0f, 0.0f };
		UINT nformats = 0;
		if (!wglChoosePixelFormat(win->DeviceContext, settings->PixelAttributes, fAttribs, 1, &idxPixelFormat, &nformats))
		{
			fprintf(stderr, "Failed to find an advanced pixel format. Falling back to the legacy format.\n");
			idxPixelFormat = ChoosePixelFormat(win->DeviceContext, &DefaultPixelFormat);
		}
	}
	else
		idxPixelFormat = ChoosePixelFormat(win->DeviceContext, &DefaultPixelFormat);

    if (!SetPixelFormat(win->DeviceContext, idxPixelFormat, &DefaultPixelFormat))
    {
        wglDestroyWindow(win);
        fprintf(stderr, "Failed to set the pixel format for the 3D rendering window.\n");
        return NULL;
    }
    
    if (settings->PixelAttributes)
        win->RenderContext = wglCreateContextAttribs(win->DeviceContext, NULL, DefaultContextSettings);
    else
        win->RenderContext = wglCreateContext(win->DeviceContext);

    if (!wglMakeCurrent(win->DeviceContext, win->RenderContext))
    {
        wglDestroyWindow(win);
        fprintf(stderr, "Failed to initialize the temporary rendering context.\n");
        return NULL;
    }

    if (!LoadFunctionPointers())
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

    UnregisterClass(window->ClassName, GetModuleHandle(NULL));
    free(window);
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
