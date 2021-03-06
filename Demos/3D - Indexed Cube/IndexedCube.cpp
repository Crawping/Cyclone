
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
            BasicRenderer(Area(0, 0, 1024, 960), "Indexed Cube"),
            Cube(Mesh3D::Cube(true))
        {
            Initialize();
        }

    protected:
        Entity3D Cube;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Cube
                .PrimaryColor(Color4::Green)
                .Position(Vector3(RenderWindow->ClientArea().Center(), -50))
                .Pitch(90)
                .Scale(100, 100, 100)
                .Roll(90);
            RenderScene->Insert(Cube);
        }

        void CreateSizedResources() override
        {
            BasicRenderer::CreateSizedResources();
            Cube.Position(Vector3(RenderWindow->ClientArea().Center(), -50));
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline
            (
                "../../Renderers/Shaders/BlinnPhong.vsl",
                "../../Renderers/Shaders/BlinnPhong.psl"
            );
        }

        void UpdateScene() override
        {
            Color4 color
            (
                0.5f * sinf(Cube.Pitch()) + 0.5f,
                0.25f * cosf(Cube.Yaw()) + 0.75f,
                0.125f * sinf(Cube.Roll()) + 0.875f
            );

            Cube
                .PrimaryColor(color)
                .Rotate(Vector3(0.01f, 0.05f, 0.01f));
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
