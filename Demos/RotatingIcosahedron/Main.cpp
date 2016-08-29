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
            BasicRenderer("Rotating Cube"),
            Icosahedron(Geometry::Icosahedron())
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
                .Color(Color4::Cyan)
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
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Depth.psl");
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