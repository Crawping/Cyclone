#include "NVPR.h"
#include <stdio.h>

#ifdef __linux__
    #include "Linux/GLX.h"
#else
    #include "Windows/WGL.h"
#endif



/** PATH RENDERING FUNCTION POINTERS **/
PFNGLCOVERFILLPATHINSTANCEDNVPROC            nvCoverFillPathInstanced                   = NULL;
PFNGLCOVERSTROKEPATHINSTANCEDNVPROC          nvCoverStrokePathInstanced                 = NULL;
PFNGLCOPYPATHNVPROC                          nvCopyPath                                 = NULL;
PFNGLDELETEPATHSNVPROC                       nvDeletePaths                              = NULL;
PFNGLGENPATHSNVPROC                          nvGenPaths                                 = NULL;
PFNGLGETPATHCOLORGENIVNVPROC                 nvGetPathColorGeniv                        = NULL;
PFNGLGETPATHCOLORGENFVNVPROC                 nvGetPathColorGenfv                        = NULL;
PFNGLGETPATHCOMMANDSNVPROC                   nvGetPathCommands                          = NULL;
PFNGLGETPATHCOORDSNVPROC                     nvGetPathCoords                            = NULL;
PFNGLGETPATHDASHARRAYNVPROC                  nvGetPathDashArray                         = NULL;
PFNGLGETPATHLENGTHNVPROC                     nvGetPathLength                            = NULL;
PFNGLGETPATHMETRICRANGENVPROC                nvGetPathMetricRange                       = NULL;
PFNGLGETPATHMETRICSNVPROC                    nvGetPathMetrics                           = NULL;
PFNGLGETPATHPARAMETERIVNVPROC                nvGetPathParameteriv                       = NULL;
PFNGLGETPATHPARAMETERFVNVPROC                nvGetPathParameterfv                       = NULL;
PFNGLGETPATHSPACINGNVPROC                    nvGetPathSpacing                           = NULL;
PFNGLGETPATHTEXGENIVNVPROC                   nvGetPathTexGeniv                          = NULL;
PFNGLGETPATHTEXGENFVNVPROC                   nvGetPathTexGenfv                          = NULL;
PFNGLMATRIXLOADIDENTITYEXTPROC               nvIdentityMatrix                           = NULL;
PFNGLINTERPOLATEPATHSNVPROC                  nvInterpolatePaths                         = NULL;
PFNGLISPATHNVPROC                            nvIsPath                                   = NULL;
PFNGLISPOINTINFILLPATHNVPROC                 nvIsPointInFillPath                        = NULL;
PFNGLISPOINTINSTROKEPATHNVPROC               nvIsPointInStrokePath                      = NULL;
PFNGLMATRIXORTHOEXTPROC                      nvOrthoMatrix                              = NULL;
PFNGLPATHCOLORGENNVPROC                      nvPathColorGen                             = NULL;
PFNGLPATHCOMMANDSNVPROC                      nvPathCommands                             = NULL;
PFNGLPATHCOORDSNVPROC                        nvPathCoords                               = NULL;
PFNGLPATHCOVERDEPTHFUNCNVPROC                nvPathCoverDepthFunc                       = NULL;
PFNGLPATHDASHARRAYNVPROC                     nvPathDashArray                            = NULL;
PFNGLPATHFOGGENNVPROC                        nvPathFogGen                               = NULL;
PFNGLPATHGLYPHRANGENVPROC                    nvPathGlyphRange                           = NULL;
PFNGLPATHGLYPHSNVPROC                        nvPathGlyphs                               = NULL;
PFNGLPATHPARAMETERFNVPROC                    nvPathParameterf                           = NULL;
PFNGLPATHPARAMETERFVNVPROC                   nvPathParameterfv                          = NULL;
PFNGLPATHPARAMETERINVPROC                    nvPathParameteri                           = NULL;
PFNGLPATHPARAMETERIVNVPROC                   nvPathParameteriv                          = NULL;
PFNGLPATHSTENCILDEPTHOFFSETNVPROC            nvPathStencilDepthOffset                   = NULL;
PFNGLPATHSTENCILFUNCNVPROC                   nvPathStencilFunc                          = NULL;
PFNGLPATHSTRINGNVPROC                        nvPathString                               = NULL;
PFNGLPATHSUBCOMMANDSNVPROC                   nvPathSubCommands                          = NULL;
PFNGLPATHSUBCOORDSNVPROC                     nvPathSubCoords                            = NULL;
PFNGLPATHTEXGENNVPROC                        nvPathTexGen                               = NULL;
PFNGLPOINTALONGPATHNVPROC                    nvPointAlongPath                           = NULL;
PFNGLCOVERFILLPATHNVPROC                     nvCoverFillPath                            = NULL;
PFNGLCOVERSTROKEPATHNVPROC                   nvCoverStrokePath                          = NULL;
PFNGLSTENCILFILLPATHNVPROC                   nvStencilFillPath                          = NULL;
PFNGLSTENCILFILLPATHINSTANCEDNVPROC          nvStencilFillPathInstanced                 = NULL;
PFNGLSTENCILSTROKEPATHNVPROC                 nvStencilStrokePath                        = NULL;
PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC        nvStencilStrokePathInstanced               = NULL;
PFNGLTRANSFORMPATHNVPROC                     nvTransformPath                            = NULL;
PFNGLWEIGHTPATHSNVPROC                       nvWeightPaths                              = NULL;




int nvLoadFunctions()
{
    HINSTANCE libHandle = LoadLibrary(L"opengl32.dll");
    if (!libHandle)
    {
        fprintf(stderr, "The OpenGL library opengl32.dll could not be opened.\n");
        return 0;
    }

    nvDeletePaths                       = (PFNGLDELETEPATHSNVPROC)                      glGetFunctionPointer("glDeletePathsNV");
    nvCopyPath                          = (PFNGLCOPYPATHNVPROC)                         glGetFunctionPointer("glCopyPathNV");
    nvCoverFillPath                     = (PFNGLCOVERFILLPATHNVPROC)                    glGetFunctionPointer("glCoverFillPathNV");
    nvCoverFillPathInstanced            = (PFNGLCOVERFILLPATHINSTANCEDNVPROC)           glGetFunctionPointer("glCoverFillPathInstancedNV");
    nvCoverStrokePath                   = (PFNGLCOVERSTROKEPATHNVPROC)                  glGetFunctionPointer("glCoverStrokePathNV");
    nvCoverStrokePathInstanced          = (PFNGLCOVERSTROKEPATHINSTANCEDNVPROC)         glGetFunctionPointer("glCoverStrokePathInstancedNV");
    nvGenPaths                          = (PFNGLGENPATHSNVPROC)                         glGetFunctionPointer("glGenPathsNV");
    nvGetPathColorGeniv                 = (PFNGLGETPATHCOLORGENIVNVPROC)                glGetFunctionPointer("glGetPathColorGenivNV");
    nvGetPathColorGenfv                 = (PFNGLGETPATHCOLORGENFVNVPROC)                glGetFunctionPointer("glGetPathColorGenfvNV");
    nvGetPathCommands                   = (PFNGLGETPATHCOMMANDSNVPROC)                  glGetFunctionPointer("glGetPathCommandsNV");
    nvGetPathCoords                     = (PFNGLGETPATHCOORDSNVPROC)                    glGetFunctionPointer("glGetPathCoordsNV");
    nvGetPathDashArray                  = (PFNGLGETPATHDASHARRAYNVPROC)                 glGetFunctionPointer("glGetPathDashArrayNV");
    nvGetPathLength                     = (PFNGLGETPATHLENGTHNVPROC)                    glGetFunctionPointer("glGetPathLengthNV");
    nvGetPathMetricRange                = (PFNGLGETPATHMETRICRANGENVPROC)               glGetFunctionPointer("glGetPathMetricRangeNV");
    nvGetPathMetrics                    = (PFNGLGETPATHMETRICSNVPROC)                   glGetFunctionPointer("glGetPathMetricsNV");
    nvGetPathParameterfv                = (PFNGLGETPATHPARAMETERFVNVPROC)               glGetFunctionPointer("glGetPathParameterfvNV");
    nvGetPathParameteriv                = (PFNGLGETPATHPARAMETERIVNVPROC)               glGetFunctionPointer("glGetPathParameterivNV");
    nvGetPathSpacing                    = (PFNGLGETPATHSPACINGNVPROC)                   glGetFunctionPointer("glGetPathSpacingNV");
    nvGetPathTexGeniv                   = (PFNGLGETPATHTEXGENIVNVPROC)                  glGetFunctionPointer("glGetPathTexGenivNV");
    nvGetPathTexGenfv                   = (PFNGLGETPATHTEXGENFVNVPROC)                  glGetFunctionPointer("glGetPathTexGenfvNV");
    nvInterpolatePaths                  = (PFNGLINTERPOLATEPATHSNVPROC)                 glGetFunctionPointer("glInterpolatePathsNV");
    nvIsPath                            = (PFNGLISPATHNVPROC)                           glGetFunctionPointer("glIsPathNV");
    nvIsPointInFillPath                 = (PFNGLISPOINTINFILLPATHNVPROC)                glGetFunctionPointer("glIsPointInFillPathNV");
    nvIsPointInStrokePath               = (PFNGLISPOINTINSTROKEPATHNVPROC)              glGetFunctionPointer("glIsPointInStrokePathNV");
    nvPathColorGen                      = (PFNGLPATHCOLORGENNVPROC)                     glGetFunctionPointer("glPathColorGenNV");
    nvPathCommands                      = (PFNGLPATHCOMMANDSNVPROC)                     glGetFunctionPointer("glPathCommandsNV");
    nvPathCoords                        = (PFNGLPATHCOORDSNVPROC)                       glGetFunctionPointer("glPathCoordsNV");
    nvPathCoverDepthFunc                = (PFNGLPATHCOVERDEPTHFUNCNVPROC)               glGetFunctionPointer("glPathCoverDepthFuncNV");
    nvPathDashArray                     = (PFNGLPATHDASHARRAYNVPROC)                    glGetFunctionPointer("glPathDashArrayNV");
    nvPathFogGen                        = (PFNGLPATHFOGGENNVPROC)                       glGetFunctionPointer("glPathFogGenNV");
    nvPathGlyphs                        = (PFNGLPATHGLYPHSNVPROC)                       glGetFunctionPointer("glPathGlyphsNV");
    nvPathGlyphRange                    = (PFNGLPATHGLYPHRANGENVPROC)                   glGetFunctionPointer("glPathGlyphRangeNV");
    nvPathParameterf                    = (PFNGLPATHPARAMETERFNVPROC)                   glGetFunctionPointer("glPathParameterfNV");
    nvPathParameterfv                   = (PFNGLPATHPARAMETERFVNVPROC)                  glGetFunctionPointer("glPathParameterfvNV");
    nvPathParameteri                    = (PFNGLPATHPARAMETERINVPROC)                   glGetFunctionPointer("glPathParameteriNV");
    nvPathParameteriv                   = (PFNGLPATHPARAMETERIVNVPROC)                  glGetFunctionPointer("glPathParameterivNV");
    nvPathStencilDepthOffset            = (PFNGLPATHSTENCILDEPTHOFFSETNVPROC)           glGetFunctionPointer("glPathStencilDepthOffsetNV");
    nvPathStencilFunc                   = (PFNGLPATHSTENCILFUNCNVPROC)                  glGetFunctionPointer("glPathStencilFuncNV");
    nvPathString                        = (PFNGLPATHSTRINGNVPROC)                       glGetFunctionPointer("glPathStringNV");
    nvPathSubCommands                   = (PFNGLPATHSUBCOMMANDSNVPROC)                  glGetFunctionPointer("glPathSubCommandsNV");
    nvPathSubCoords                     = (PFNGLPATHSUBCOORDSNVPROC)                    glGetFunctionPointer("glPathSubCoordsNV");
    nvPathTexGen                        = (PFNGLPATHTEXGENNVPROC)                       glGetFunctionPointer("glPathTexGenNV");
    nvPointAlongPath                    = (PFNGLPOINTALONGPATHNVPROC)                   glGetFunctionPointer("glPointAlongPathNV");
    nvStencilFillPath                   = (PFNGLSTENCILFILLPATHNVPROC)                  glGetFunctionPointer("glStencilFillPathNV");
    nvStencilFillPathInstanced          = (PFNGLSTENCILFILLPATHINSTANCEDNVPROC)         glGetFunctionPointer("glStencilFillPathInstancedNV");
    nvStencilStrokePath                 = (PFNGLSTENCILSTROKEPATHNVPROC)                glGetFunctionPointer("glStencilStrokePathNV");
    nvStencilStrokePathInstanced        = (PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC)       glGetFunctionPointer("glStencilStrokePathInstancedNV");
    nvTransformPath                     = (PFNGLTRANSFORMPATHNVPROC)                    glGetFunctionPointer("glTransformPathNV");
    nvWeightPaths                       = (PFNGLWEIGHTPATHSNVPROC)                      glGetFunctionPointer("glWeightPathsNV");

    nvIdentityMatrix                    = (PFNGLMATRIXLOADIDENTITYEXTPROC)              glGetFunctionPointer("glMatrixLoadIdentityEXT");
    nvOrthoMatrix                       = (PFNGLMATRIXORTHOEXTPROC)                     glGetFunctionPointer("glMatrixOrthoEXT");

    FreeLibrary(libHandle);

    if (!nvPathCommands || !nvPathString || !nvPathParameteri || !nvIdentityMatrix || !nvOrthoMatrix)
        return 0;
    else
        return 1;
}
