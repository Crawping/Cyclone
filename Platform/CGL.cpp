#include "Console.h"
#include "CGL.h"

#ifdef __linux__
    #include "Linux/GLX.h"
#else
    #include "Windows/WGL.h"
#endif

using namespace Cyclone::Utilities;



#ifdef __linux__

    int Cyclone::Platform::cglLoadAPI()
    {        
        return 1;
    }
    void Cyclone::Platform::cglClearAPI()
    {

    }

#else

    int Cyclone::Platform::cglLoadAPI()
    {
        if (!wglLoadFunctions())
        {
            Console::WriteLine("Failed to load the WGL library functions.");
            return 0;
        }

        if (!glLoadFunctions())
        {
            Console::WriteLine("Failed to load the OpenGL library functions.");
            return 0;
        }

        return 1;
    }
    void Cyclone::Platform::cglClearAPI()
    {
        wglDestroyResources();
    }

#endif
