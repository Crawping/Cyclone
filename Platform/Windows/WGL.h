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

            /** WGL FUNCTION POINTERS **/
            PlatformAPI extern PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs;
            PlatformAPI extern PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString;
            PlatformAPI extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv;
            PlatformAPI extern PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval;



            /// <summary> A handle for the GDI device context bound to the loading window. </summary>
            InternalAPI extern HDC      LoadingDeviceContext;
            /// <summary> A handle for the OpenGL rendering context bound to the loading window and device context. </summary>
            InternalAPI extern HGLRC    LoadingRenderContext;
            /// <summary> A handle for the Windows Forms window that is created in order to load OpenGL function pointers. </summary>
            /// <remarks>
            ///     Loading the OpenGL API on the Windows platform is a complicated procedure.
            /// </remarks>
            InternalAPI extern HWND     LoadingWindow;



            /** PUBLIC API FUNCTIONS **/
            InternalAPI int wglLoadFunctions();

            InternalAPI void wglDestroyResources();
            
    #ifdef __cplusplus
        }
    #endif


#endif