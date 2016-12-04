#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/Line3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;



class Program : public BasicRenderer
{
    public:
        Program() :
            BasicRenderer(Area(0, 0, 1024, 960), "Basic Line")
        {
            Initialize();
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(32);
        }

    protected:
        Line3D Line;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Line
                .PrimaryColor(Color4(0.0f, 0.75f, 1.0f))
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .Pitch(90)
                .Scale(256)
                .Roll(90);

            RenderScene->Add(Line);
        }

        void CreateSizedResources() override
        {
            BasicRenderer::CreateSizedResources();
            Line.Position(Vector3(RenderWindow->ClientArea().Center(), 50));
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Depth.psl");
        }

        void UpdateScene() override
        {
            Color4 color
            (
                0.5f * sinf(Line.Pitch()) + 0.5f,
                0.25f * cosf(Line.Yaw()) + 0.75f,
                0.125f * sinf(Line.Roll()) + 0.875
            );

            Line.PrimaryColor(color).Rotate(0.01f);
            RenderScene->Update(Line);

            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
