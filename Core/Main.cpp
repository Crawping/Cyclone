#include "GL/OpenGL.h"
#include "Program.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace Cyclone;



int main(int nargs, char** args)
{    
    Program app(nargs, args);
    app.Execute();
    return 0;
}