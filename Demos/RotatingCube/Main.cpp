
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
            Cube(Geometry::Cube())
        {
            Initialize();
            glEnable(GL_CULL_FACE);
        }

    protected:
        Mesh3D Cube;
        Vector3 Rotation;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Cube.Scale(100, 100, 100)
                .Color(Color4::Green)
                .Position(RenderWindow->ClientArea().Center())
                .Pitch(90)
                .Roll(90);
            RenderScene->Add(Cube);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Depth.psl");
            Renderer->RenderPipeline(RenderPipeline);
        }

        void UpdateScene() override
        {
            Cube.Rotate(Vector3(0.0f, 0.01f, 0.0f));
            //Cube.Rotate(0.01f);
            RenderScene->Add(Cube);
            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}