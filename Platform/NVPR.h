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

            typedef void (APIENTRYP PFNGLPATHCOMMANDSNVPROC)        (GLuint path, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const GLvoid *coords);
            typedef void (APIENTRYP PFNGLPATHSTRINGNVPROC)          (GLuint path, GLenum format, GLsizei length, const GLvoid *pathString);
            typedef void (APIENTRYP PFNGLPATHPARAMETERINVPROC)      (GLuint path, GLenum pname, GLint value);
            typedef void (APIENTRYP PFNGLPATHPARAMETERFNVPROC)      (GLuint path, GLenum pname, GLfloat value);
            typedef void (APIENTRYP PFNGLSTENCILFILLPATHNVPROC)     (GLuint path, GLenum fillMode, GLuint mask);
            typedef void (APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC)   (GLuint path, GLint reference, GLuint mask);
            typedef void (APIENTRYP PFNGLCOVERFILLPATHNVPROC)       (GLuint path, GLenum coverMode);
            typedef void (APIENTRYP PFNGLCOVERSTROKEPATHNVPROC)     (GLuint path, GLenum coverMode);

            typedef void (APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum mode);
            typedef void (APIENTRYP PFNGLMATRIXORTHOEXTPROC)        (GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble znear, GLdouble zfar);



            PlatformAPI extern PFNGLPATHCOMMANDSNVPROC              nvPathCommands;
            PlatformAPI extern PFNGLPATHSTRINGNVPROC                nvPathString;
            PlatformAPI extern PFNGLPATHPARAMETERINVPROC            nvPathParameteri;
            PlatformAPI extern PFNGLPATHPARAMETERFNVPROC            nvPathParameterf;
            PlatformAPI extern PFNGLCOVERFILLPATHNVPROC             nvCoverFillPath;
            PlatformAPI extern PFNGLCOVERSTROKEPATHNVPROC           nvCoverStrokePath;
            PlatformAPI extern PFNGLSTENCILFILLPATHNVPROC           nvStencilFillPath;
            PlatformAPI extern PFNGLSTENCILSTROKEPATHNVPROC         nvStencilStrokePath;

            PlatformAPI extern PFNGLMATRIXLOADIDENTITYEXTPROC       nvIdentityMatrix;
            PlatformAPI extern PFNGLMATRIXORTHOEXTPROC              nvOrthoMatrix;


            PlatformAPI int nvLoadFunctions();


    #ifdef __cplusplus
        }
    #endif
#endif
