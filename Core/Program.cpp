#include "CGL.h"
#include "Console.h"
#include "Program.h"

using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;



Program::Program(int nargs, char** args)
{
    ParseInputArguments(nargs, args);
    
    if (!cglLoadAPI())
        Console::WriteLine("Failed to load the OpenGL function pointers.");
}


Program::~Program()
{
    cglClearAPI();
}

void Program::InitializeOpenGL()
{
    
}

void Program::ParseInputArguments(int nargs, char** args)
{

}
