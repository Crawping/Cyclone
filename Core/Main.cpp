#include "GL/OpenGL.h"

#include "Area.h"
#include "Array.h"
#include "CGL.h"
#include "Console.h"
#include "Program.h"
#include "Utilities.h"
#include "Window3D.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace Cyclone::Utilities;
using namespace Cyclone::Platform;
using namespace Cyclone;


int main(int nargs, char** args)
{    
    Program app(nargs, args);
    app.Execute();

    return 0;
}