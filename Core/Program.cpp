#include "CGL.h"
#include "Console.h"
#include "Program.h"
#include "GPU.h"
#include "Utilities.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Quad3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Geometry/Geometry.h"



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
        PlaneXZ(nullptr),
        Renderer(nullptr),
        RenderScene(nullptr),
        RenderTarget(nullptr),
        RenderWindow(nullptr),
        RenderPipeline(nullptr),
        TestShape(nullptr)
    {
        ParseInputArguments(nargs, args);

        if (!cglLoadAPI())
        {
            PostInfo("Failed to initialize the OpenGL library.");
            return;
        }

        Renderer        = new GPU();
        RenderWindow    = new Window3D(Area(0, 0, 960, 540), "OpenGL Test Window");
        RenderPipeline  = new ShaderPipeline("../OpenGL/Shaders/Default.vsl", "../OpenGL/Shaders/Default.psl");
        RenderScene     = new Scene3D();

        Renderer->RenderWindow(RenderWindow);
        Renderer->RenderPipeline(RenderPipeline);

        CreateSizedResources();

        PlaneXZ = new Quad3D();
        PlaneXZ->Pitch(-90).Scale(5000, 5000).Translate(0, 50);

        Vector<uint> indices;
        Vector<Vertex::Standard> vertices = Geometry::Cube(indices);
        TestShape = new Mesh3D(vertices, indices);
        TestShape->Scale(Vector3(50, 50, 50)).Translate(250, 250, -10);

        RenderScene->Add(*TestShape);
        RenderScene->Add(*PlaneXZ);

        Renderer->Scene(RenderScene);

        RenderWindow->OnClose.Register(this, &Program::BreakEventLoop);
        RenderWindow->OnResize.Register(this, &Program::CreateSizedResources);
    }
    Program::~Program()
    {
        if (TestShape)          { delete TestShape; }
        if (PlaneXZ)            { delete PlaneXZ; }
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
            RenderScene->Update(*TestShape);

            Console::WriteLine("1. " + Renderer->Report());
            Renderer->Clear(Color4(0.5f));
            Console::WriteLine("2. " + Renderer->Report());
            Renderer->Update();
            Console::WriteLine("3. " + Renderer->Report());
            Renderer->Execute();
            Console::WriteLine("4. " + Renderer->Report());
            Renderer->Present();           
            Console::WriteLine("5. " + Renderer->Report());
        }
    }



    /** PRIVATE UTILITIES **/
    void Program::BreakEventLoop()
    {
        _canContinue = false;
    }
    void Program::CreateSizedResources()
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
                    PostInfo("The display option was invoked at the command line, but no display index was provided.");
            }
            else
                PostInfo("Unrecognized command line input argument: " + ctArg);
        }
    }
}
