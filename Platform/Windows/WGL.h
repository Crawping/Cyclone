/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#ifndef LoadOpenGLWHeaderGuard
    #define LoadOpenGLWHeaderGuard

    #include "GL/OpenGL.h"
    #include "GL/wglext.h"

    typedef HGLRC RenderContext;

    #ifdef __cplusplus
        extern "C"
        {
    #endif

            /** WGL FUNCTION POINTERS **/
            extern PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribs;
            extern PFNWGLGETEXTENSIONSSTRINGARBPROC     wglGetExtensionsString;
            extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribiv;
            extern PFNWGLSWAPINTERVALEXTPROC            wglSwapInterval;


            extern HDC  LoadingContext;
            extern HWND LoadingWindow;



            /** PUBLIC API FUNCTIONS **/
            int wglLoadFunctions();

            void wglDestroyResources();

            
    #ifdef __cplusplus
        }
    #endif


#endif