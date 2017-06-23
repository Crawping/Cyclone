#include "Program.h"
#include "GPU.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "Geometry/Mesh3D.h"



namespace Cyclone
{

    /** CONSTRUCTOR & DESTRUCTOR **/
    Program::Program(int nargs, char** args) :
        BasicRenderer(Area(0, 0, 1280, 800), "Core Test", 4),
        _debug(false),
        _showHelp(false)
    {
        Initialize();
    }
    Program::~Program()
    {

    }



    /** UTILITIES **/
    void Program::Execute()
    {
        while (CanContinue())
        {
            RenderWindow->ProcessEvent();
            UpdateScene();
            Render();
            Renderer->Present();
            Console::WriteLine("1. " + Renderer->Report());
        }
    }



    /** PRIVATE UTILITIES **/
	void Program::CreateShaderPipeline()
	{
         _pipeline = Create<ShaderPipeline, string, string>
        (
            "BlinnPhong", Constructor<ShaderPipeline, string, string>(),
            "../Renderers/Shaders/BlinnPhong.vsl",
            "../Renderers/Shaders/BlinnPhong.psl"
        );
	}
	void Program::CreateSceneResources()
	{
        BasicRenderer::CreateSceneResources();

        auto gcube = Create("Cube", Function<Mesh3D, bool>(&Mesh3D::Cube), true);
        auto gplane = Create("Plane", Function<Mesh3D, bool>(&Mesh3D::Quad), true);
        auto gicos = Create("Icosahedron", Function<Mesh3D, bool>(&Mesh3D::Icosahedron), false);

        PlaneXZ = Create<Entity3D>("PlaneXZ");
        Cube = Create<Entity3D>("Cube");
        Icosahedron = Create<Entity3D>("Icosahedron");

		PlaneXZ->
             Material(Create<Material3D>("Plane"))
            .Model(Create<Model3D>("Plane"))
            .Geometry(gplane)
            .PrimaryColor(Color4::Blue)
            .Pitch(-90)
            .Scale(5000).Translate(0, 50, 0);

        Cube->
             Material(Create<Material3D>("Cube"))
            .Model(Create<Model3D>("Cube"))
            .Geometry(gcube)
            .PrimaryColor(Color4::Gray)
            .Scale(50)
            .Translate(250, 250, -10);

        Icosahedron->
             Material(Create<Material3D>("Icosahedron"))
            .Model(Create<Model3D>("Icosahedron"))
            .Geometry(gicos)
            .PrimaryColor(Color4::Red)
            .Scale(50)
            .Translate(750, 250, -10);

        auto cube2 = Create<Entity3D>("Cube2");
        cube2->
             Material(Icosahedron->Material())
            .Model(Cube->Model())
            .Scale(100)
            .Translate(500, 250, -150);

        RenderScene->Insert(Icosahedron);
        RenderScene->Insert(Cube);
        RenderScene->Insert(PlaneXZ);
        RenderScene->Insert(cube2);
	}

    void Program::UpdateScene()
    {
        Cube->Rotate(Vector3(0.01f, 0.05f, 0.01f));
        Icosahedron->Rotate(-0.025f);

        Color4 color
        (
            0.5f * sinf(Cube->Pitch()) + 0.5f,
            0.25f * cosf(Cube->Yaw()) + 0.75f,
            0.125f * sinf(Cube->Roll()) + 0.875f
        );

        auto cube2 = Get<Entity3D>("Cube2");
        cube2->PrimaryColor(color);

        RenderScene->Update(Cube);
        RenderScene->Update(Icosahedron);
        RenderScene->Update(cube2);
        BasicRenderer::UpdateScene();
    }

}
