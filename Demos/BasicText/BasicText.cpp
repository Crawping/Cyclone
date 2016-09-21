/* CHANGELOG
 * Written by Josh Grooms on 20160915
 */

#include "BasicRenderer.h"
#include "Console.h"
#include "EnumerationsSVG.h"
#include "GPU.h"
#include "NVPR.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Geometry/Scene3D.h"
#include "Imaging/Color4.h"
#include "Pipelines/ShaderPipeline.h"
#include "Text/Text2D.h"

using namespace Cyclone::Platform;
using namespace Cyclone::SVG;
using namespace Cyclone::Utilities;
using namespace Renderers;



class Program : public BasicRenderer
{
    public:

        Program() : 
            BasicRenderer("NVIDIA Basic Path Rendering")
        {
            Initialize();
        }

    protected:

        Text2D Text;



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

            Text
                .Text("Testing!")
                .FillColor(Color4::Green)

                .Scale(0.1f, 0.1f)
                .Position(128, 512);

            RenderScene->Add(Text);
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
            nvMatrixFrustum
            (
                TransformMatrices::Projection,
                0, RenderWindow->Width(),
                0, RenderWindow->Height(),
                1, 1000
            );
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Text.Z(-5 * sin(count) - 6);
            count += 0.01f;

            BasicRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
