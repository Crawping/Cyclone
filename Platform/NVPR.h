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

            PlatformAPI extern PFNGLCOVERFILLPATHNVPROC                     nvCoverFillPath;
            PlatformAPI extern PFNGLCOVERFILLPATHINSTANCEDNVPROC            nvCoverFillPathInstanced;
            PlatformAPI extern PFNGLCOVERSTROKEPATHNVPROC                   nvCoverStrokePath;
            PlatformAPI extern PFNGLCOVERSTROKEPATHINSTANCEDNVPROC          nvCoverStrokePathInstanced;

            PlatformAPI extern PFNGLCOPYPATHNVPROC                          nvCopyPath;
            PlatformAPI extern PFNGLDELETEPATHSNVPROC                       nvDeletePaths;
            PlatformAPI extern PFNGLGENPATHSNVPROC                          nvGenPaths;

            PlatformAPI extern PFNGLGETPATHCOMMANDSNVPROC                   nvGetPathCommands;
            PlatformAPI extern PFNGLGETPATHCOORDSNVPROC                     nvGetPathCoords;
            PlatformAPI extern PFNGLGETPATHDASHARRAYNVPROC                  nvGetPathDashArray;
            PlatformAPI extern PFNGLGETPATHLENGTHNVPROC                     nvGetPathLength;
            PlatformAPI extern PFNGLGETPATHMETRICRANGENVPROC                nvGetPathMetricRange;
            PlatformAPI extern PFNGLGETPATHMETRICSNVPROC                    nvGetPathMetrics;
            PlatformAPI extern PFNGLGETPATHPARAMETERIVNVPROC                nvGetPathParameteriv;
            PlatformAPI extern PFNGLGETPATHPARAMETERFVNVPROC                nvGetPathParameterfv;
            PlatformAPI extern PFNGLGETPATHSPACINGNVPROC                    nvGetPathSpacing;

            PlatformAPI extern PFNGLINTERPOLATEPATHSNVPROC                  nvInterpolatePaths;
            PlatformAPI extern PFNGLISPATHNVPROC                            nvIsPath;
            PlatformAPI extern PFNGLISPOINTINFILLPATHNVPROC                 nvIsPointInFillPath;
            PlatformAPI extern PFNGLISPOINTINSTROKEPATHNVPROC               nvIsPointInStrokePath;

            PlatformAPI extern PFNGLMATRIXFRUSTUMEXTPROC                    nvMatrixFrustum;
            PlatformAPI extern PFNGLMATRIXLOADDEXTPROC                      nvMatrixLoadd;
            PlatformAPI extern PFNGLMATRIXLOADFEXTPROC                      nvMatrixLoadf;
            PlatformAPI extern PFNGLMATRIXLOADIDENTITYEXTPROC               nvMatrixLoadIdentity;
            PlatformAPI extern PFNGLMATRIXLOADTRANSPOSEDEXTPROC             nvMatrixLoadTransposed;
            PlatformAPI extern PFNGLMATRIXLOADTRANSPOSEFEXTPROC             nvMatrixLoadTransposef;
            PlatformAPI extern PFNGLMATRIXMULTDEXTPROC                      nvMatrixMultd;
            PlatformAPI extern PFNGLMATRIXMULTFEXTPROC                      nvMatrixMultf;
            PlatformAPI extern PFNGLMATRIXMULTTRANSPOSEDEXTPROC             nvMatrixMultTransposed;
            PlatformAPI extern PFNGLMATRIXMULTTRANSPOSEFEXTPROC             nvMatrixMultTransposef;
            PlatformAPI extern PFNGLMATRIXORTHOEXTPROC                      nvMatrixOrtho;
            PlatformAPI extern PFNGLMATRIXPOPEXTPROC                        nvMatrixPop;
            PlatformAPI extern PFNGLMATRIXPUSHEXTPROC                       nvMatrixPush;
            PlatformAPI extern PFNGLMATRIXROTATEDEXTPROC                    nvMatrixRotated;
            PlatformAPI extern PFNGLMATRIXROTATEFEXTPROC                    nvMatrixRotatef;
            PlatformAPI extern PFNGLMATRIXSCALEDEXTPROC                     nvMatrixScaled;
            PlatformAPI extern PFNGLMATRIXSCALEFEXTPROC                     nvMatrixScalef;
            PlatformAPI extern PFNGLMATRIXTRANSLATEDEXTPROC                 nvMatrixTranslated;
            PlatformAPI extern PFNGLMATRIXTRANSLATEFEXTPROC                 nvMatrixTranslatef;

            PlatformAPI extern PFNGLPATHCOMMANDSNVPROC                      nvPathCommands;
            PlatformAPI extern PFNGLPATHCOORDSNVPROC                        nvPathCoords;
            PlatformAPI extern PFNGLPATHCOVERDEPTHFUNCNVPROC                nvPathCoverDepthFunc;
            PlatformAPI extern PFNGLPATHDASHARRAYNVPROC                     nvPathDashArray;
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

            PlatformAPI extern PFNGLPOINTALONGPATHNVPROC                    nvPointAlongPath;
            PlatformAPI extern PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC       nvProgramPathFragmentInputGen;
            PlatformAPI extern PFNGLSTENCILFILLPATHNVPROC                   nvStencilFillPath;
            PlatformAPI extern PFNGLSTENCILFILLPATHINSTANCEDNVPROC          nvStencilFillPathInstanced;
            PlatformAPI extern PFNGLSTENCILSTROKEPATHNVPROC                 nvStencilStrokePath;
            PlatformAPI extern PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC        nvStencilStrokePathInstanced;
            PlatformAPI extern PFNGLTRANSFORMPATHNVPROC                     nvTransformPath;
            PlatformAPI extern PFNGLWEIGHTPATHSNVPROC                       nvWeightPaths;



            PlatformAPI int nvLoadFunctions();


    #ifdef __cplusplus
        }
    #endif
#endif
