#include "CGL.h"
#include "Console.h"
#include "Program.h"
#include "GPU.h"
#include "Utilities.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Pipelines/ShaderPipeline.h"
#include "Primitives/Mesh3D.h"
#include "Primitives/Scene3D.h"
#include "Spatial/Geometry.h"



const static string Help = "                        \n\
    CYCLONE - A cross-platform 3D rendering engine. \n\n";



namespace Cyclone
{
    using namespace OpenGL;
    using namespace Platform;
    using namespace Utilities;



    /** CONSTRUCTOR & DESTRUCTOR **/
    Program::Program(int nargs, char** args) : 
        _canContinue(true),
        _debug(false),
        _display(0),
        _showHelp(false),
        Renderer(nullptr),
        RenderScene(nullptr),
        RenderTarget(nullptr),
        RenderWindow(nullptr),
        RenderPipeline(nullptr),
        TestShape(nullptr)
    {
        ParseInputArguments(nargs, args);
    
        if (!cglLoadAPI())
            Console::WriteLine("Failed to initialize the OpenGL library.");

        Renderer        = new GPU();
        RenderWindow    = new Window3D(Area(0, 0, 960, 540), "OpenGL Test Window");
        RenderPipeline  = new ShaderPipeline("../OpenGL/Shaders/Default.vsl", "../OpenGL/Shaders/Default.psl");
        RenderScene     = new Scene3D();

        CreateRenderTarget();

        TestShape = new Mesh3D(Geometry::Cube());
        TestShape->Scale(Vector3(25, 25, 25)).Translate(250, 250, -10);
        RenderScene->Add(*TestShape);
        RenderScene->Update();

        Renderer->RenderWindow(RenderWindow);
        Renderer->RenderPipeline(RenderPipeline);
        Renderer->Scene(RenderScene);

        RenderWindow->OnResize.Register(this, &Program::CreateRenderTarget);
        RenderWindow->OnClose.Register(this, &Program::BreakEventLoop);
    }
    Program::~Program()
    {
        if (TestShape)          { delete TestShape; }
        if (RenderTarget)       { delete RenderTarget; }
        if (RenderScene)        { delete RenderScene; }
        if (RenderPipeline)     { delete RenderPipeline; }
        if (RenderWindow)       { delete RenderWindow; }
        if (Renderer)           { delete Renderer; }

        cglClearAPI();
    }



    /** UTILITIES **/
    void Program::Execute()
    {  
        while (_canContinue)
        {
            if (!RenderWindow->ProcessEvent())
                break;

            TestShape->Rotate(Vector3(0.01f, 0.01f, 0.01f));
            RenderScene->Add(*TestShape);

            Renderer->Clear(Color4(0.5f));
            Renderer->Update();
            Renderer->Render();
            Renderer->Present();
        }
    }



    /** PRIVATE UTILITIES **/
    void Program::BreakEventLoop()
    {
        _canContinue = false;
    }
    void Program::CreateRenderTarget()
    {
        if (RenderTarget)
            delete RenderTarget;

        Area clientArea = RenderWindow->ClientArea();
        View = Transform::Translation(Vector3(-clientArea.Scale() / 2.0f, -clientArea.Height / 2.0f));
        Projection = Transform::PerspectiveProjection
        (
            90,
            clientArea.Width / clientArea.Height,
            (clientArea.Height - 100.0f) / 2.0f,
            (clientArea.Height + 100.0f) / 2.0f
        );

        RenderTarget = new FrameBuffer(clientArea.Scale());

        Renderer->RenderTarget(RenderTarget);
        Renderer->Projection(Projection);
        Renderer->View(View);
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