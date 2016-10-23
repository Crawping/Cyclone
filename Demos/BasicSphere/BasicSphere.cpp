#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;



class Program : public BasicRenderer
{
    public:
        Program() :
            BasicRenderer(Area(0, 0, 1024, 960), "Rotating Sphere"),
            Sphere(Geometry3D::Sphere(3))
        {
            Initialize();
        }

    protected:
        Mesh3D Sphere;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Sphere
                .Pitch(90)
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .PrimaryColor(Color4(0.0f, 0.75f, 1.0f))
                .Roll(90)
                .Scale(100);

            RenderScene->Add(Sphere);
        }

        void CreateSizedResources() override
        {
            BasicRenderer::CreateSizedResources();
            Sphere.Position(Vector3(RenderWindow->ClientArea().Center(), 50));
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/BlinnPhong.vsl", "../Renderers/Shaders/BlinnPhong.psl");
        }

        void UpdateScene() override
        {
            Color4 color
            (
                0.5f * sinf(Sphere.Pitch()) + 0.5f,
                0.25f * cosf(Sphere.Yaw()) + 0.75f,
                0.125f * sinf(Sphere.Roll()) + 0.875
            );

            Sphere.Color(color).Rotate(0.01f);
            RenderScene->Update(Sphere);

            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
