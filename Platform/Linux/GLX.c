#include "GLX.h"
#include <stdio.h>



/** GLX FUNCTION POINTERS **/
PFNGLXCREATECONTEXTATTRIBSARBPROC   glXCreateContextAttribs = NULL;
PFNGLXBINDTEXIMAGEEXTPROC           glXBindTexImage = NULL;
PFNGLXRELEASETEXIMAGEEXTPROC        glXReleaseTexImage = NULL;
PFNGLXSWAPINTERVALEXTPROC           glXSwapInterval = NULL;



/** FUNCTION LOADER **/
int glXLoadFunctions()
{
    glXCreateContextAttribs     = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glGetFunctionPointer("glXCreateContextAttribsARB");
    glXBindTexImage             = (PFNGLXBINDTEXIMAGEEXTPROC)glGetFunctionPointer("glXBindTexImageEXT");
    glXReleaseTexImage          = (PFNGLXRELEASETEXIMAGEEXTPROC)glGetFunctionPointer("glXReleaseTexImageEXT");
    glXSwapInterval             = (PFNGLXSWAPINTERVALEXTPROC)glGetFunctionPointer("glXSwapIntervalEXT");
    
    if (!glXCreateContextAttribs)
    {
        fprintf(stderr, "Failed to load the GLX render context creation function.\n");
        return 0;
    }

    if (!glXBindTexImage)
    {
        fprintf(stderr, "Failed to load the GLX pixmap binding function.\n");
        return 0;
    }

    if (!glXReleaseTexImage)
    {
        fprintf(stderr, "Failed to load the GLX pixmap release function.\n");
        return 0;
    }
    
    if (!glXSwapInterval)
    {
        fprintf(stderr, "Failed to load the GLX swap interval setting function.\n");
        return 0;
    }

    return 1;
}
