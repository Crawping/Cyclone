#include "GLX.h"
#include <iostream>



/** GLX FUNCTION POINTERS **/
//PFNGLXCREATECONTEXTATTRIBSARBPROC   glXCreateContextAttribs = NULL;
//PFNGLXBINDTEXIMAGEEXTPROC           glXBindTexImage = NULL;
//PFNGLXRELEASETEXIMAGEEXTPROC        glXReleaseTexImage = NULL;
//PFNGLXSWAPINTERVALEXTPROC           glXSwapInterval = NULL;



/** FUNCTION LOADER **/
int glXLoadFunctions()
{
    //glXCreateContextAttribs     = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glGetFunctionPointer("glXCreateContextAttribsARB");
    //glXBindTexImage             = (PFNGLXBINDTEXIMAGEEXTPROC)glGetFunctionPointer("glXBindTexImageEXT");
    //glXReleaseTexImage          = (PFNGLXRELEASETEXIMAGEEXTPROC)glGetFunctionPointer("glXReleaseTexImageEXT");
    //glXSwapInterval             = (PFNGLXSWAPINTERVALEXTPROC)glGetFunctionPointer("glXSwapIntervalEXT");
    //
    //if (!glXCreateContextAttribs)
    //{
    //    std::cout << "Failed to load the GLX render context creation function.\n";
    //    return 0;
    //}

    //if (!glXBindTexImage)
    //{
    //    std::cout << "Failed to load the GLX pixmap binding function.\n";
    //    return 0;
    //}

    //if (!glXReleaseTexImage)
    //{
    //    std::cout << "Failed to load the GLX pixmap release function.\n";
    //    return 0;
    //}
    //
    //if (!glXSwapInterval)
    //{
    //    std::cout << "Failed to load the GLX swap interval setting function.\n";
    //    return 0;
    //}

    return 1;
}
