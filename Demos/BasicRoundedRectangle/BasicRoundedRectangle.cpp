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
            BasicRenderer("NVIDIA Basic Rounded Rectangle Rendering")
        {
            Initialize();
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
                { PathCommands::Close,{ } },
            };

            Path
                .StrokeWidth(6.5f)

                .Color(Color4::Red)
                .Scale(1)
                .Position(Vector3(RenderWindow->ClientArea().Scale() / 3.0f, -100));

            Path.Add(path);
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

            nvMatrixLoadIdentity(TransformMatrices::Projection);
            nvMatrixLoadf(TransformMatrices::Projection, (Renderer->Projection() * Renderer->View()).ToArray());
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Path.Z(-250 * sin(count));
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
