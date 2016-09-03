
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
            BasicRenderer("Indexed Cube"),
            Cube(nullptr)
        {
            Array<uint> indices;
            Array<Vertex::Standard> vertices = Geometry::Cube(indices);
            Cube = new Mesh3D(vertices, indices);

            Initialize();
            glEnable(GL_CULL_FACE);
        }
        ~Program()
        {
            if (Cube) { delete Cube; }
        }

    protected:
        Mesh3D* Cube;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Cube->Scale(100, 100, 100)
                .Color(Color4::Green)
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .Pitch(90)
                .Roll(90);
            RenderScene->Add(*Cube);
        }

        void CreateSizedResources() override
        {
            BasicRenderer::CreateSizedResources();
            Cube->Position(Vector3(RenderWindow->ClientArea().Center(), 50));
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Depth.psl");
            Renderer->RenderPipeline(RenderPipeline);
        }

        void UpdateScene() override
        {
            Color4 color
            (
                0.5f * sinf(Cube->Pitch()) + 0.5f,
                0.25f * cosf(Cube->Yaw()) + 0.75f,
                0.125f * sinf(Cube->Roll()) + 0.875f
            );

            Cube->Rotate(Vector3(0.01f, 0.05f, 0.01f))
                .Color(color);
            RenderScene->Add(*Cube);
            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}