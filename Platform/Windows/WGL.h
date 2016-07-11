/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#ifndef LoadOpenGLWHeaderGuard
    #define LoadOpenGLWHeaderGuard

    #include "GL/OpenGL.h"
    #include "GL/wglext.h"
    #include "PlatformAPI.h"

    typedef HGLRC RenderContext;

    #ifdef __cplusplus
        extern "C"
        {
    #endif

            /** WGL FUNCTION POINTERS **/
            PlatformAPI extern PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs;
            PlatformAPI extern PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString;
            PlatformAPI extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv;
            PlatformAPI extern PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval;


            PlatformAPI extern HDC  LoadingContext;
            PlatformAPI extern HWND LoadingWindow;



            /** PUBLIC API FUNCTIONS **/
            int wglLoadFunctions();

            void wglDestroyResources();

            
    #ifdef __cplusplus
        }
    #endif


#endif