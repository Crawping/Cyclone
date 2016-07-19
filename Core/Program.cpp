#include "CGL.h"
#include "Console.h"
#include "Program.h"
#include "GPU.h"
#include "Window3D.h"

#include "Pipelines/ShaderPipeline.h"

using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;

const static string Help = "            \n\
    CYCLONE - A cross-platform 3D rendering engine. \n\n";



namespace Cyclone
{
    using namespace OpenGL;


    /** CONSTRUCTOR & DESTRUCTOR **/
    Program::Program(int nargs, char** args) : 
        _debug(false),
        _display(0),
        _showHelp(false),
        Renderer(nullptr),
        RenderWindow(nullptr),
        RenderPipeline(nullptr)
    {
        ParseInputArguments(nargs, args);
    
        if (!cglLoadAPI())
            Console::WriteLine("Failed to load the OpenGL function pointers.");

        Renderer        = new GPU();
        RenderPipeline  = new ShaderPipeline("../OpenGL/Shaders/Default.vsl", "../OpenGL/Shaders/Default.psl");
        RenderWindow    = new Window3D(Area(0, 0, 1024, 512), "Test Window");

        Renderer->RenderWindow(RenderWindow);
        Renderer->RenderPipeline(RenderPipeline);
    }

    Program::~Program()
    {
        if (RenderWindow)       { delete RenderWindow; }
        if (RenderPipeline)     { delete RenderPipeline; }
        if (Renderer)           { delete Renderer; }

        cglClearAPI();
    }



    /** UTILITIES **/
    void Program::Execute()
    {        
        while (true)
        {
            if (!RenderWindow->ProcessEvents())
                break;

            Renderer->Clear();
            Renderer->Present();
        }

    }

    void Program::ParseInputArguments(int nargs, char** args)
    {
        if (nargs == 1)
            return;

        string ctArg, ntArg;
        for (int a = 1; a < nargs; a++)
        {
            ctArg = args[a];
            if (ctArg == "-h" || ctArg == "--help")
                _showHelp = true;
            else if (ctArg == "--debug")
                _debug = true;
            else if (ctArg == "--display")
            {
                if (a < nargs - 1)
                {
                    ntArg = args[++a];
                    if (ntArg[0] == ':')
                        ntArg.erase(ntArg.begin());
                    _display = std::stoi(ntArg);
                }
                else
                    Console::WriteLine("The display option was invoked at the command line, but no display index was provided.");
            }
            else
                Console::WriteLine("Unrecognized command line input argument: " + ctArg);
        }
    }
}