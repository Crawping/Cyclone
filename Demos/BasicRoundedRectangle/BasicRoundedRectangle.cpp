/* CHANGELOG
 * Written by Josh Grooms on 20160922
 */

#include "BasicRenderer.h"
#include "Console.h"
#include "EnumerationsSVG.h"
#include "GPU.h"
#include "NVPR.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Collections/Vector.h"
#include "Geometry/Scene3D.h"
#include "Geometry/Path2D.h"

#include "Imaging/Color4.h"
#include "Pipelines/ShaderPipeline.h"

using namespace Cyclone::Platform;
using namespace Cyclone::SVG;
using namespace Cyclone::Utilities;
using namespace Renderers;



class Program : public BasicRenderer
{
    public:

        Program() :
            BasicRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Rounded Rectangle Rendering")
        {
            Initialize();
            nvPathStencilDepthOffset(-0.05f, -1);
            nvPathCoverDepthFunc(GL_ALWAYS);
        }

    protected:

        Path2D          Path;



        void CreateRenderTarget() override
        {
            if (RenderTarget)
                delete RenderTarget;

            RenderTarget = new FrameBuffer(RenderWindow->ClientArea().Scale(), TextureFormats::Byte4, TextureFormats::DepthStencil);
            Renderer->RenderTarget(RenderTarget);
        }
        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Vector<ControlPoint2D> path =
            {
                { PathCommands::RoundedRectangle, { -50, -50, 100, 100, 12 } },
                { PathCommands::Close, { } },
            };

            Path.Add(path)
                .StrokeColor(Color4::Cyan)
                .StrokeWidth(4)

                .Color(Color4::Red)
                .Scale(3)
                .Position(Vector3(RenderWindow->ClientArea().Scale() / 3.0f, -100));

            RenderScene->Add(Path);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/SVG.psl");
            Renderer->RenderPipeline(RenderPipeline);
        }
        void CreateTransformations() override
        {
            BasicRenderer::CreateTransformations();

            const Matrix4x4& projection = Renderer->Projection().ToMatrix4x4();
            const Matrix4x4& view = Renderer->View().ToMatrix4x4();

            nvMatrixLoadIdentity(TransformMatrices::Projection);
            nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Path.Z(-250 * sin(count));
            Path.Roll(count);
            count += 0.02f;

            BasicRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
