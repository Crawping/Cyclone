/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#ifndef LoadOpenGLWHeaderGuard
    #define LoadOpenGLWHeaderGuard

    #include "GL/OpenGL.h"
    #include "GL/wglext.h"
    #include "PlatformAPI.h"
	

    #ifdef __cplusplus
        extern "C"
        {
    #endif

			/** WGL DATA STRUCTURES **/
			typedef struct _window3D
			{
				HDC     DeviceContext;
				LPCWSTR ClassName;
				HWND    ID;
				HGLRC   RenderContext;


				PFNWGLCREATECONTEXTATTRIBSARBPROC    CreateContextAttribs;
				PFNWGLGETEXTENSIONSSTRINGARBPROC     GetExtensionsString;
				PFNWGLGETPIXELFORMATATTRIBIVARBPROC  GetPixelFormatAttribiv;
				PFNWGLSWAPINTERVALEXTPROC            SwapInterval;
				PFNWGLCHOOSEPIXELFORMATARBPROC       ChoosePixelFormat;

			} _window3D;

			typedef struct WindowSettings
			{
				LPCWSTR		ClassName;
				RECT		DisplayArea;
				WNDPROC		MessageHandler;
				const int*	PixelAttributes;
				LPCWSTR		Title;
			} WindowSettings;



            /** WGL FUNCTION POINTERS **/
            PlatformAPI extern PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs;
            PlatformAPI extern PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString;
            PlatformAPI extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv;
            PlatformAPI extern PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval;
            PlatformAPI extern PFNWGLCHOOSEPIXELFORMATARBPROC       wglChoosePixelFormat;



            /** INTERNAL API FUNCTIONS **/
			InternalAPI _window3D* wglCreateWindow(const WindowSettings* settings);

            InternalAPI void wglDestroyWindow(_window3D* window);
            
    #ifdef __cplusplus
        }
    #endif

#endif