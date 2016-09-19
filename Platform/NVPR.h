/* CHANGELOG
 * Written by Josh Grooms on 20160915
 */

#ifndef LoadNVPRHeaderGuard
    #define LoadNVPRHeaderGuard

    #include "GL/OpenGL.h"
    #include "GL/glext.h"
    #include "PlatformAPI.h"

    #ifdef __cplusplus
        extern "C"
        {
    #endif


            PlatformAPI extern PFNGLCOVERFILLPATHINSTANCEDNVPROC            nvCoverFillPathInstanced;
            PlatformAPI extern PFNGLCOVERSTROKEPATHINSTANCEDNVPROC          nvCoverStrokePathInstanced;
            PlatformAPI extern PFNGLCOPYPATHNVPROC                          nvCopyPath;
            PlatformAPI extern PFNGLDELETEPATHSNVPROC                       nvDeletePaths;
            PlatformAPI extern PFNGLGENPATHSNVPROC                          nvGenPaths;
            PlatformAPI extern PFNGLGETPATHCOLORGENIVNVPROC                 nvGetPathColorGeniv;
            PlatformAPI extern PFNGLGETPATHCOLORGENFVNVPROC                 nvGetPathColorGenfv;
            PlatformAPI extern PFNGLGETPATHCOMMANDSNVPROC                   nvGetPathCommands;
            PlatformAPI extern PFNGLGETPATHCOORDSNVPROC                     nvGetPathCoords;
            PlatformAPI extern PFNGLGETPATHDASHARRAYNVPROC                  nvGetPathDashArray;
            PlatformAPI extern PFNGLGETPATHLENGTHNVPROC                     nvGetPathLength;
            PlatformAPI extern PFNGLGETPATHMETRICRANGENVPROC                nvGetPathMetricRange;
            PlatformAPI extern PFNGLGETPATHMETRICSNVPROC                    nvGetPathMetrics;
            PlatformAPI extern PFNGLGETPATHPARAMETERIVNVPROC                nvGetPathParameteriv;
            PlatformAPI extern PFNGLGETPATHPARAMETERFVNVPROC                nvGetPathParameterfv;
            PlatformAPI extern PFNGLGETPATHSPACINGNVPROC                    nvGetPathSpacing;
            PlatformAPI extern PFNGLGETPATHTEXGENIVNVPROC                   nvGetPathTexGeniv;
            PlatformAPI extern PFNGLGETPATHTEXGENFVNVPROC                   nvGetPathTexGenfv;
            PlatformAPI extern PFNGLINTERPOLATEPATHSNVPROC                  nvInterpolatePaths;
            PlatformAPI extern PFNGLISPATHNVPROC                            nvIsPath;
            PlatformAPI extern PFNGLISPOINTINFILLPATHNVPROC                 nvIsPointInFillPath;
            PlatformAPI extern PFNGLISPOINTINSTROKEPATHNVPROC               nvIsPointInStrokePath;
            PlatformAPI extern PFNGLPATHCOLORGENNVPROC                      nvPathColorGen;
            PlatformAPI extern PFNGLPATHCOMMANDSNVPROC                      nvPathCommands;
            PlatformAPI extern PFNGLPATHCOORDSNVPROC                        nvPathCoords;
            PlatformAPI extern PFNGLPATHCOVERDEPTHFUNCNVPROC                nvPathCoverDepthFunc;
            PlatformAPI extern PFNGLPATHDASHARRAYNVPROC                     nvPathDashArray;
            PlatformAPI extern PFNGLPATHFOGGENNVPROC                        nvPathFogGen;
            PlatformAPI extern PFNGLPATHGLYPHRANGENVPROC                    nvPathGlyphRange;
            PlatformAPI extern PFNGLPATHGLYPHSNVPROC                        nvPathGlyphs;
            PlatformAPI extern PFNGLPATHPARAMETERFNVPROC                    nvPathParameterf;
            PlatformAPI extern PFNGLPATHPARAMETERFVNVPROC                   nvPathParameterfv;
            PlatformAPI extern PFNGLPATHPARAMETERINVPROC                    nvPathParameteri;
            PlatformAPI extern PFNGLPATHPARAMETERIVNVPROC                   nvPathParameteriv;
            PlatformAPI extern PFNGLPATHSTENCILDEPTHOFFSETNVPROC            nvPathStencilDepthOffset;
            PlatformAPI extern PFNGLPATHSTENCILFUNCNVPROC                   nvPathStencilFunc;
            PlatformAPI extern PFNGLPATHSTRINGNVPROC                        nvPathString;
            PlatformAPI extern PFNGLPATHSUBCOMMANDSNVPROC                   nvPathSubCommands;
            PlatformAPI extern PFNGLPATHSUBCOORDSNVPROC                     nvPathSubCoords;
            PlatformAPI extern PFNGLPATHTEXGENNVPROC                        nvPathTexGen;
            PlatformAPI extern PFNGLPOINTALONGPATHNVPROC                    nvPointAlongPath;
            PlatformAPI extern PFNGLCOVERFILLPATHNVPROC                     nvCoverFillPath;
            PlatformAPI extern PFNGLCOVERSTROKEPATHNVPROC                   nvCoverStrokePath;
            PlatformAPI extern PFNGLSTENCILFILLPATHNVPROC                   nvStencilFillPath;
            PlatformAPI extern PFNGLSTENCILFILLPATHINSTANCEDNVPROC          nvStencilFillPathInstanced;
            PlatformAPI extern PFNGLSTENCILSTROKEPATHNVPROC                 nvStencilStrokePath;
            PlatformAPI extern PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC        nvStencilStrokePathInstanced;
            PlatformAPI extern PFNGLTRANSFORMPATHNVPROC                     nvTransformPath;
            PlatformAPI extern PFNGLWEIGHTPATHSNVPROC                       nvWeightPaths;
            PlatformAPI extern PFNGLMATRIXLOADIDENTITYEXTPROC               nvIdentityMatrix;
            PlatformAPI extern PFNGLMATRIXORTHOEXTPROC                      nvOrthoMatrix;



            PlatformAPI int nvLoadFunctions();


    #ifdef __cplusplus
        }
    #endif
#endif
