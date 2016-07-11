#include "Console.h"
#include "CGL.h"

#ifdef __linux__
    #include "Linux/GLX.h"
#else
    #include "Windows/WGL.h"
#endif

using namespace Cyclone::Utilities;



namespace Cyclone
{
    namespace Platform
    {
        
        int cglLoadAPI()
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

        void cglClearAPI()
        {
            wglDestroyResources();
        }
    }
}