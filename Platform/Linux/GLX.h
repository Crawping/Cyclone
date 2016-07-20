/* CHANGELOG
 * Written by Josh Grooms on 20151104
 */

#ifndef LoadOpenGLXHeaderGuard
    #define LoadOpenGLXHeaderGuard

    #include "GL/OpenGL.h"
    #include <GL/glx.h>
    #include <GL/glxext.h>

    #ifdef __cplusplus
        extern "C"
        {
    #endif

            /** GLX FUNCTION POINTERS **/
            extern PFNGLXCREATECONTEXTATTRIBSARBPROC    glXCreateContextAttribs;
            extern PFNGLXBINDTEXIMAGEEXTPROC            glXBindTexImage;
            extern PFNGLXRELEASETEXIMAGEEXTPROC         glXReleaseTexImage;
            extern PFNGLXSWAPINTERVALEXTPROC            glXSwapInterval;



            /** PUBLIC API FUNCTIONS **/
            int glXLoadFunctions();

    #ifdef __cplusplus
        }
    #endif
#endif
