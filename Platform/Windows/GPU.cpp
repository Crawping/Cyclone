#include "Buffers/FrameBuffer.h"
#include "Console.h"
#include "GPU.h"

#ifdef __linux__
    #include "Linux/GLX.h"
#else
    #include "Windows/WGL.h"
#endif

using namespace Cyclone::Utilities;



/** INTERNAL DATA **/
const static PIXELFORMATDESCRIPTOR DefaultPixelFormat =
{
    sizeof(PIXELFORMATDESCRIPTOR),                                  // nSize
    1,                                                              // nVersion
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,     // dwFlags
    PFD_TYPE_RGBA,                                                  // iPixelType
    32,                                                             // cColorBits
    8,                                                              // cRedBits;
    0,                                                              // cRedShift;
    8,                                                              // cGreenBits;
    0,                                                              // cGreenShift;
    8,                                                              // cBlueBits;
    0,                                                              // cBlueShift;
    8,                                                              // cAlphaBits;
    0,                                                              // cAlphaShift;
    0,                                                              // cAccumBits;
    0,                                                              // cAccumRedBits
    0,                                                              // cAccumGreenBi
    0,                                                              // cAccumBlueBit
    0,                                                              // cAccumAlphaBi
    24,                                                             // cDepthBits;
    8,                                                              // cStencilBits;
    0,                                                              // cAuxBuffers;
    PFD_MAIN_PLANE,                                                 // iLayerType;
    0,                                                              // bReserved;
    0,                                                              // dwLayerMask;
    0,                                                              // dwVisibleMask
    0,                                                              // dwDamageMask;
};

const static int DefaultContextSettings[] = 
{
    WGL_CONTEXT_FLAGS_ARB,          WGL_CONTEXT_DEBUG_BIT_ARB,
    WGL_CONTEXT_MAJOR_VERSION_ARB,  3,
    WGL_CONTEXT_MINOR_VERSION_ARB,  2,
    WGL_CONTEXT_PROFILE_MASK_ARB,   WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    NULL,
};




namespace Cyclone
{
    struct GPU::_gpu
    {
        RenderContext Context;
    };



    /** CONSTRUCTOR & DESTRUCTOR **/
    GPU::GPU() : 
        Internals(new _gpu{ NULL }),
        _renderPipeline(nullptr),
        _renderTarget(nullptr)
    {
        CreateRenderContext();
    }

    GPU::~GPU()
    {
        if (Internals->Context)
            wglDeleteContext(Internals->Context);
        if (Internals) { delete Internals; }
    }



    /** RENDERING UTILITIES **/
    void GPU::Clear()
    {
        RestoreRenderingDefaults();
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GPU::Present()
    {
        
    }


    /** PRIVATE UTILITIES **/
    void GPU::CreateRenderContext()
    {
        int idxPixelFormat = ChoosePixelFormat(LoadingContext, &DefaultPixelFormat);
        SetPixelFormat(LoadingContext, idxPixelFormat, &DefaultPixelFormat);

        Internals->Context = wglCreateContextAttribs(LoadingContext, NULL, DefaultContextSettings);
        if (!Internals->Context)
            Console::WriteLine("Failed to load the advanced rendering context.");
    }

    void GPU::RestoreRenderingDefaults()
    {

    }
}
