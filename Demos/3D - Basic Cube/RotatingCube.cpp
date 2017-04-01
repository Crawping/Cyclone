
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
            Cube(Geometry3D::Cube())
        {
            Initialize();
            glEnable(GL_CULL_FACE);
        }

    protected:
        Model3D Cube;
        Vector3 Rotation;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Cube
                .PrimaryColor(Color4::Green)
                .Position(RenderWindow->ClientArea().Center())
                .Pitch(90)
                .Roll(90)
                .Scale(200, 200, 200);

            RenderScene->Insert(Cube);
        }

        void CreateSizedResources() override
        {
            BasicRenderer::CreateSizedResources();
            Cube.Position(Vector3(RenderWindow->ClientArea().Center(), 50));
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Depth.psl");
        }

        void UpdateScene() override
        {
            Cube.Rotate(Vector3(0.0f, 0.01f, 0.0f));
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