
#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"
#include "GL/OpenGL.h"
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
            glEnable(GL_CULL_FACE);
        }

    protected:

        Resource<Entity3D> Cube;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Cube = Create<Entity3D>("Cube");
            Cube->
                 Material(Create<Material3D>("Cube"))
                .Model(Create<Model3D>("Cube"))
                .Geometry(Create("Cube", Function<Mesh3D, bool>(&Mesh3D::Cube), false))
                .PrimaryColor(Color4::Green)
                .Position(RenderWindow->ClientArea().Center())
                .Pitch(90)
                .Roll(90)
                .Scale(200);

            RenderScene->Insert(Cube);
        }

        void UpdateScene() override
        {
            Cube->Rotate(Vector3(0.0f, 0.01f, 0.0f));
            RenderScene->Update(Cube);
            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}