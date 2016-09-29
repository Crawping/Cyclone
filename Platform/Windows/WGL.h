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

			typedef struct _window3D
			{
				HDC     DeviceContext;
				HWND    ID;
				HGLRC   RenderContext;


				PFNWGLCREATECONTEXTATTRIBSARBPROC    CreateContextAttribs;
				PFNWGLGETEXTENSIONSSTRINGARBPROC     GetExtensionsString;
				PFNWGLGETPIXELFORMATATTRIBIVARBPROC  GetPixelFormatAttribiv;
				PFNWGLSWAPINTERVALEXTPROC            SwapInterval;
				PFNWGLCHOOSEPIXELFORMATARBPROC       ChoosePixelFormat;

			} _window3D;



            /** WGL FUNCTION POINTERS **/
            PlatformAPI extern PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs;
            PlatformAPI extern PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString;
            PlatformAPI extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv;
            PlatformAPI extern PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval;
            PlatformAPI extern PFNWGLCHOOSEPIXELFORMATARBPROC       wglChoosePixelFormat;


			InternalAPI extern const int						DefaultContextSettings[];
            InternalAPI extern const int                        DefaultPixelAttributes[];
            InternalAPI extern const PIXELFORMATDESCRIPTOR      DefaultPixelFormat;

            /// <summary> A handle for the GDI device context bound to the loading window. </summary>
            InternalAPI extern HDC                              LoadingDeviceContext;
            /// <summary> A handle for the OpenGL rendering context bound to the loading window and device context. </summary>
            InternalAPI extern HGLRC                            LoadingRenderContext;
            /// <summary> A handle for the Windows Forms window that is created in order to load OpenGL function pointers. </summary>
            /// <remarks>
            ///     Loading the OpenGL API on the Windows platform is a complicated procedure.
            /// </remarks>
            InternalAPI extern HWND                             LoadingWindow;



            /** INTERNAL API FUNCTIONS **/
			InternalAPI _window3D* wglCreateWindow(const int* pixelAttributes, WNDPROC msgLoop);

            InternalAPI void wglDestroyWindow(_window3D* window);

			//InternalAPI int wglLoadAPI();

            InternalAPI int wglLoadFunctions();


            InternalAPI void wglDestroyResources();
            
    #ifdef __cplusplus
        }
    #endif

#endif