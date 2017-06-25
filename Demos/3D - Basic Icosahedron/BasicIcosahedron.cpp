#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"

using namespace Cyclone::OpenGL;
using namespace Cyclone::Renderers;



class Program : public BasicRenderer
{
    public:
        Program() :
            BasicRenderer(Area(0, 0, 1024, 960), "Rotating Cube")
        {
            Initialize();
        }

    protected:

        Resource<Entity3D> Icosahedron;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Icosahedron = Create<Entity3D>("Icosahedron");

            Icosahedron->
                 Material(Create<Material3D>("Icosahedron"))
                .Model(Create<Model3D>("Icosahedron"))
                .Geometry(Create("Icosahedron", Function<Mesh3D, bool>(&Mesh3D::Icosahedron), false))
                .PrimaryColor(Color4::Cyan)
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .Pitch(90)
                .Roll(90)
                .Scale(100);

            RenderScene->Insert(Icosahedron);
            RenderScene->CullingMode(CullingModes::Back);
        }

        void UpdateScene() override
        {
            Icosahedron->Rotate(0.01f);
            RenderScene->Update(Icosahedron);
            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}