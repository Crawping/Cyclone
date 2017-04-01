#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/Model3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;



class Program : public BasicRenderer
{
    public:
        Program() :
            BasicRenderer(Area(0, 0, 1024, 960), "Rotating Cube"),
            Icosahedron(Geometry3D::Icosahedron())
        {
            Initialize();
        }

    protected:
        Model3D Icosahedron;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Icosahedron
                .PrimaryColor(Color4::Cyan)
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .Pitch(90)
                .Roll(90)
                .Scale(100, 100, 100);

            RenderScene->Insert(Icosahedron);
            RenderScene->CullingMode(CullingModes::Back);
        }

        void CreateSizedResources() override
        {
            BasicRenderer::CreateSizedResources();
            Icosahedron.Position(Vector3(RenderWindow->ClientArea().Center(), 50));
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Depth.psl");
        }

        void UpdateScene() override
        {
            Icosahedron.Rotate(0.01f);
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