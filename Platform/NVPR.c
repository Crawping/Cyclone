#include "NVPR.h"
#include <stdio.h>

#ifdef __linux__
    #include "Linux/GLX.h"
#else
    #include "Windows/WGL.h"
#endif



/** PATH RENDERING FUNCTION POINTERS **/
PFNGLPATHCOMMANDSNVPROC              nvPathCommands         = NULL;
PFNGLPATHSTRINGNVPROC                nvPathString           = NULL;
PFNGLPATHPARAMETERINVPROC            nvPathParameteri       = NULL;
PFNGLPATHPARAMETERFNVPROC            nvPathParameterf       = NULL;
PFNGLCOVERFILLPATHNVPROC             nvCoverFillPath        = NULL;
PFNGLCOVERSTROKEPATHNVPROC           nvCoverStrokePath      = NULL;
PFNGLSTENCILFILLPATHNVPROC           nvStencilFillPath      = NULL;
PFNGLSTENCILSTROKEPATHNVPROC         nvStencilStrokePath    = NULL;

PFNGLMATRIXLOADIDENTITYEXTPROC       nvIdentityMatrix       = NULL;
PFNGLMATRIXORTHOEXTPROC              nvOrthoMatrix          = NULL;



int nvLoadFunctions()
{
    HINSTANCE libHandle = LoadLibrary(L"opengl32.dll");
    if (!libHandle)
    {
        fprintf(stderr, "The OpenGL library opengl32.dll could not be opened.\n");
        return 0;
    }

    nvPathCommands      = (PFNGLPATHCOMMANDSNVPROC)      glGetFunctionPointer("glPathCommandsNV");
    nvPathString        = (PFNGLPATHSTRINGNVPROC)        glGetFunctionPointer("glPathStringNV");
    nvPathParameteri    = (PFNGLPATHPARAMETERINVPROC)    glGetFunctionPointer("glPathParameteriNV");
    nvPathParameterf    = (PFNGLPATHPARAMETERFNVPROC)    glGetFunctionPointer("glPathParameterfNV");
    nvCoverFillPath     = (PFNGLCOVERFILLPATHNVPROC)     glGetFunctionPointer("glCoverFillPathNV");
    nvCoverStrokePath   = (PFNGLCOVERSTROKEPATHNVPROC)   glGetFunctionPointer("glCoverStrokePathNV");
    nvStencilFillPath   = (PFNGLSTENCILFILLPATHNVPROC)   glGetFunctionPointer("glStencilFillPathNV");
    nvStencilStrokePath = (PFNGLSTENCILSTROKEPATHNVPROC) glGetFunctionPointer("glStencilStrokePathNV");

    FreeLibrary(libHandle);
    
    if (!nvPathCommands || !nvPathString || !nvPathParameteri)
        return 0;
    else
        return 1;
}