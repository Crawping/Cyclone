#include "NVPR.h"
#include <stdio.h>

#ifdef __linux__
    #include "Linux/GLX.h"
#else
    #include "Windows/WGL.h"
#endif



/** PATH RENDERING FUNCTION POINTERS **/
PFNGLCOVERFILLPATHNVPROC                     nvCoverFillPath                            = NULL;
PFNGLCOVERFILLPATHINSTANCEDNVPROC            nvCoverFillPathInstanced                   = NULL;
PFNGLCOVERSTROKEPATHNVPROC                   nvCoverStrokePath                          = NULL;
PFNGLCOVERSTROKEPATHINSTANCEDNVPROC          nvCoverStrokePathInstanced                 = NULL;

PFNGLCOPYPATHNVPROC                          nvCopyPath                                 = NULL;
PFNGLDELETEPATHSNVPROC                       nvDeletePaths                              = NULL;
PFNGLGENPATHSNVPROC                          nvGenPaths                                 = NULL;

PFNGLGETPATHCOMMANDSNVPROC                   nvGetPathCommands                          = NULL;
PFNGLGETPATHCOORDSNVPROC                     nvGetPathCoords                            = NULL;
PFNGLGETPATHDASHARRAYNVPROC                  nvGetPathDashArray                         = NULL;
PFNGLGETPATHLENGTHNVPROC                     nvGetPathLength                            = NULL;
PFNGLGETPATHMETRICRANGENVPROC                nvGetPathMetricRange                       = NULL;
PFNGLGETPATHMETRICSNVPROC                    nvGetPathMetrics                           = NULL;
PFNGLGETPATHPARAMETERIVNVPROC                nvGetPathParameteriv                       = NULL;
PFNGLGETPATHPARAMETERFVNVPROC                nvGetPathParameterfv                       = NULL;
PFNGLGETPATHSPACINGNVPROC                    nvGetPathSpacing                           = NULL;

PFNGLINTERPOLATEPATHSNVPROC                  nvInterpolatePaths                         = NULL;
PFNGLISPATHNVPROC                            nvIsPath                                   = NULL;
PFNGLISPOINTINFILLPATHNVPROC                 nvIsPointInFillPath                        = NULL;
PFNGLISPOINTINSTROKEPATHNVPROC               nvIsPointInStrokePath                      = NULL;

PFNGLMATRIXFRUSTUMEXTPROC                    nvMatrixFrustum                            = NULL;
PFNGLMATRIXLOADDEXTPROC                      nvMatrixLoadd                              = NULL;
PFNGLMATRIXLOADFEXTPROC                      nvMatrixLoadf                              = NULL;
PFNGLMATRIXLOADIDENTITYEXTPROC               nvMatrixLoadIdentity                       = NULL;
PFNGLMATRIXLOADTRANSPOSEDEXTPROC             nvMatrixLoadTransposed                     = NULL;
PFNGLMATRIXLOADTRANSPOSEFEXTPROC             nvMatrixLoadTransposef                     = NULL;
PFNGLMATRIXMULTDEXTPROC                      nvMatrixMultd                              = NULL;
PFNGLMATRIXMULTFEXTPROC                      nvMatrixMultf                              = NULL;
PFNGLMATRIXMULTTRANSPOSEDEXTPROC             nvMatrixMultTransposed                     = NULL;
PFNGLMATRIXMULTTRANSPOSEFEXTPROC             nvMatrixMultTransposef                     = NULL;
PFNGLMATRIXORTHOEXTPROC                      nvMatrixOrtho                              = NULL;
PFNGLMATRIXPOPEXTPROC                        nvMatrixPop                                = NULL;
PFNGLMATRIXPUSHEXTPROC                       nvMatrixPush                               = NULL;
PFNGLMATRIXROTATEDEXTPROC                    nvMatrixRotated                            = NULL;
PFNGLMATRIXROTATEFEXTPROC                    nvMatrixRotatef                            = NULL;
PFNGLMATRIXSCALEDEXTPROC                     nvMatrixScaled                             = NULL;
PFNGLMATRIXSCALEFEXTPROC                     nvMatrixScalef                             = NULL;
PFNGLMATRIXTRANSLATEDEXTPROC                 nvMatrixTranslated                         = NULL;
PFNGLMATRIXTRANSLATEFEXTPROC                 nvMatrixTranslatef                         = NULL;

PFNGLPATHCOMMANDSNVPROC                      nvPathCommands                             = NULL;
PFNGLPATHCOORDSNVPROC                        nvPathCoords                               = NULL;
PFNGLPATHCOVERDEPTHFUNCNVPROC                nvPathCoverDepthFunc                       = NULL;
PFNGLPATHDASHARRAYNVPROC                     nvPathDashArray                            = NULL;
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

PFNGLPOINTALONGPATHNVPROC                    nvPointAlongPath                           = NULL;
PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC       nvProgramPathFragmentInputGen              = NULL;
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

    nvCoverFillPath                     = (PFNGLCOVERFILLPATHNVPROC)                    glGetFunctionPointer("glCoverFillPathNV");
    nvCoverFillPathInstanced            = (PFNGLCOVERFILLPATHINSTANCEDNVPROC)           glGetFunctionPointer("glCoverFillPathInstancedNV");
    nvCoverStrokePath                   = (PFNGLCOVERSTROKEPATHNVPROC)                  glGetFunctionPointer("glCoverStrokePathNV");
    nvCoverStrokePathInstanced          = (PFNGLCOVERSTROKEPATHINSTANCEDNVPROC)         glGetFunctionPointer("glCoverStrokePathInstancedNV");

    nvCopyPath                          = (PFNGLCOPYPATHNVPROC)                         glGetFunctionPointer("glCopyPathNV");
    nvDeletePaths                       = (PFNGLDELETEPATHSNVPROC)                      glGetFunctionPointer("glDeletePathsNV");
    nvGenPaths                          = (PFNGLGENPATHSNVPROC)                         glGetFunctionPointer("glGenPathsNV");
    nvGetPathCommands                   = (PFNGLGETPATHCOMMANDSNVPROC)                  glGetFunctionPointer("glGetPathCommandsNV");
    nvGetPathCoords                     = (PFNGLGETPATHCOORDSNVPROC)                    glGetFunctionPointer("glGetPathCoordsNV");
    nvGetPathDashArray                  = (PFNGLGETPATHDASHARRAYNVPROC)                 glGetFunctionPointer("glGetPathDashArrayNV");
    nvGetPathLength                     = (PFNGLGETPATHLENGTHNVPROC)                    glGetFunctionPointer("glGetPathLengthNV");
    nvGetPathMetricRange                = (PFNGLGETPATHMETRICRANGENVPROC)               glGetFunctionPointer("glGetPathMetricRangeNV");
    nvGetPathMetrics                    = (PFNGLGETPATHMETRICSNVPROC)                   glGetFunctionPointer("glGetPathMetricsNV");
    nvGetPathParameterfv                = (PFNGLGETPATHPARAMETERFVNVPROC)               glGetFunctionPointer("glGetPathParameterfvNV");
    nvGetPathParameteriv                = (PFNGLGETPATHPARAMETERIVNVPROC)               glGetFunctionPointer("glGetPathParameterivNV");
    nvGetPathSpacing                    = (PFNGLGETPATHSPACINGNVPROC)                   glGetFunctionPointer("glGetPathSpacingNV");
    nvInterpolatePaths                  = (PFNGLINTERPOLATEPATHSNVPROC)                 glGetFunctionPointer("glInterpolatePathsNV");
    nvIsPath                            = (PFNGLISPATHNVPROC)                           glGetFunctionPointer("glIsPathNV");
    nvIsPointInFillPath                 = (PFNGLISPOINTINFILLPATHNVPROC)                glGetFunctionPointer("glIsPointInFillPathNV");
    nvIsPointInStrokePath               = (PFNGLISPOINTINSTROKEPATHNVPROC)              glGetFunctionPointer("glIsPointInStrokePathNV");

    nvMatrixOrtho                       = (PFNGLMATRIXORTHOEXTPROC)                     glGetFunctionPointer("glMatrixOrthoEXT");
    nvMatrixLoadIdentity                = (PFNGLMATRIXLOADIDENTITYEXTPROC)              glGetFunctionPointer("glMatrixLoadIdentityEXT");
    nvMatrixFrustum                     = (PFNGLMATRIXFRUSTUMEXTPROC)                   glGetFunctionPointer("glMatrixFrustumEXT");
    nvMatrixLoadd                       = (PFNGLMATRIXLOADDEXTPROC)                     glGetFunctionPointer("glMatrixLoaddEXT");
    nvMatrixLoadf                       = (PFNGLMATRIXLOADFEXTPROC)                     glGetFunctionPointer("glMatrixLoadfEXT");
    nvMatrixLoadIdentity                = (PFNGLMATRIXLOADIDENTITYEXTPROC)              glGetFunctionPointer("glMatrixLoadIdentityEXT");
    nvMatrixLoadTransposed              = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC)            glGetFunctionPointer("glMatrixLoadTransposedEXT");
    nvMatrixLoadTransposef              = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC)            glGetFunctionPointer("glMatrixLoadTransposefEXT");
    nvMatrixMultd                       = (PFNGLMATRIXMULTDEXTPROC)                     glGetFunctionPointer("glMatrixMultdEXT");
    nvMatrixMultf                       = (PFNGLMATRIXMULTFEXTPROC)                     glGetFunctionPointer("glMatrixMultfEXT");
    nvMatrixMultTransposed              = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC)            glGetFunctionPointer("glMatrixMultTransposedEXT");
    nvMatrixMultTransposef              = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC)            glGetFunctionPointer("glMatrixMultTransposefEXT");
    nvMatrixOrtho                       = (PFNGLMATRIXORTHOEXTPROC)                     glGetFunctionPointer("glMatrixOrthoEXT");
    nvMatrixPop                         = (PFNGLMATRIXPOPEXTPROC)                       glGetFunctionPointer("glMatrixPopEXT");
    nvMatrixPush                        = (PFNGLMATRIXPUSHEXTPROC)                      glGetFunctionPointer("glMatrixPushEXT");
    nvMatrixRotated                     = (PFNGLMATRIXROTATEDEXTPROC)                   glGetFunctionPointer("glMatrixRotatedEXT");
    nvMatrixRotatef                     = (PFNGLMATRIXROTATEFEXTPROC)                   glGetFunctionPointer("glMatrixRotatefEXT");
    nvMatrixScaled                      = (PFNGLMATRIXSCALEDEXTPROC)                    glGetFunctionPointer("glMatrixScaledEXT");
    nvMatrixScalef                      = (PFNGLMATRIXSCALEFEXTPROC)                    glGetFunctionPointer("glMatrixScalefEXT");
    nvMatrixTranslated                  = (PFNGLMATRIXTRANSLATEDEXTPROC)                glGetFunctionPointer("glMatrixTranslatedEXT");
    nvMatrixTranslatef                  = (PFNGLMATRIXTRANSLATEFEXTPROC)                glGetFunctionPointer("glMatrixTranslatefEXT");

    nvPathCommands                      = (PFNGLPATHCOMMANDSNVPROC)                     glGetFunctionPointer("glPathCommandsNV");
    nvPathCoords                        = (PFNGLPATHCOORDSNVPROC)                       glGetFunctionPointer("glPathCoordsNV");
    nvPathCoverDepthFunc                = (PFNGLPATHCOVERDEPTHFUNCNVPROC)               glGetFunctionPointer("glPathCoverDepthFuncNV");
    nvPathDashArray                     = (PFNGLPATHDASHARRAYNVPROC)                    glGetFunctionPointer("glPathDashArrayNV");
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

    nvPointAlongPath                    = (PFNGLPOINTALONGPATHNVPROC)                   glGetFunctionPointer("glPointAlongPathNV");
    nvProgramPathFragmentInputGen       = (PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC)      glGetFunctionPointer("glProgramPathFragmentInputGenNV");
    nvStencilFillPath                   = (PFNGLSTENCILFILLPATHNVPROC)                  glGetFunctionPointer("glStencilFillPathNV");
    nvStencilFillPathInstanced          = (PFNGLSTENCILFILLPATHINSTANCEDNVPROC)         glGetFunctionPointer("glStencilFillPathInstancedNV");
    nvStencilStrokePath                 = (PFNGLSTENCILSTROKEPATHNVPROC)                glGetFunctionPointer("glStencilStrokePathNV");
    nvStencilStrokePathInstanced        = (PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC)       glGetFunctionPointer("glStencilStrokePathInstancedNV");
    nvTransformPath                     = (PFNGLTRANSFORMPATHNVPROC)                    glGetFunctionPointer("glTransformPathNV");
    nvWeightPaths                       = (PFNGLWEIGHTPATHSNVPROC)                      glGetFunctionPointer("glWeightPathsNV");


    FreeLibrary(libHandle);

    if (!nvPathCommands || !nvPathString || !nvPathParameteri || !nvMatrixLoadIdentity || !nvMatrixOrtho)
        return 0;
    else
        return 1;
}
