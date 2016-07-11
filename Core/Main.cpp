#include "GL/OpenGL.h"

#include "Area.h"
#include "Array.h"
#include "CGL.h"
#include "Console.h"
#include "Utilities.h"
#include "Window3D.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace Cyclone::Utilities;
using namespace Cyclone::Platform;



int main(int nargs, char** args)
{
    Console::WriteLine("Testing this out.");
    
    if (cglLoadAPI())
    {
        Window3D t(Area(0, 0, 1024, 512), "Test Window");
        char temp; std::cin >> temp;
    }

    cglClearAPI();
    return 0;
}