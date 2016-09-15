#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "Geometry/Geometry.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;



class Program : public BasicRenderer
{
    public:
        Program() :
            BasicRenderer("Rotating Sphere"),
            Sphere(Geometry::Sphere(3))
        {
            Initialize();
        }

    protected:
        Mesh3D Sphere;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Sphere.Scale(100, 100, 100)
                .Color(Color4(0.0f, 0.75f, 1.0f))
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .Pitch(90)
                .Roll(90);

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
            Renderer->RenderPipeline(RenderPipeline);
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