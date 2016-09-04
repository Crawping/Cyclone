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
            Icosahedron(Geometry::Sphere(2))
        {
            Initialize();
            glEnable(GL_CULL_FACE);
        }

    protected:
        Mesh3D Icosahedron;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Icosahedron.Scale(100, 100, 100)
                .Color(Color4(0.0f, 0.75f, 1.0f))
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .Pitch(90)
                .Roll(90);

            RenderScene->Add(Icosahedron);
        }

        void CreateSizedResources() override
        {
            BasicRenderer::CreateSizedResources();
            Icosahedron.Position(Vector3(RenderWindow->ClientArea().Center(), 50));
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/BlinnPhong.vsl", "../Renderers/Shaders/BlinnPhong.psl");
            Renderer->RenderPipeline(RenderPipeline);
        }

        void UpdateScene() override
        {
            Icosahedron.Rotate(0.01f);
            RenderScene->Add(Icosahedron);
            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}