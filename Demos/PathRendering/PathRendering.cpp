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
#include "Geometry/Path2D.h"
#include "Text/Text2D.h"
#include "Imaging/Color4.h"
#include "Pipelines/ShaderPipeline.h"

using namespace Cyclone::Platform;
using namespace Cyclone::SVG;
using namespace Cyclone::Utilities;
using namespace Renderers;



class Program : public BasicRenderer
{
    public:

        Program() : BasicRenderer("NVIDIA Path Rendering"),
            FBO(nullptr)
        {
            Initialize();
        }
        ~Program()
        {
            if (FBO) { delete FBO; }
        }


    protected:

        FrameBuffer*    FBO;
        Path2D          Path;
        Text2D          Text;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            nvMatrixLoadIdentity(TransformMatrices::Projection);
            nvMatrixOrtho
            (
                TransformMatrices::Projection,
                 0, RenderWindow->Width(),
                 0, RenderWindow->Height(),
                -1, 1
            );

            string svgString = "M100, 180 L40, 10 L190, 120 L10, 120 L160, 10 z";
            Path
                .FillColor(Color4::Blue)
                .Path(svgString)
                .StrokeWidth(6.5f);

            Path
                .Scale(0.5f, 0.5f)
                .Position(128, 128);

            Text
                .Text("Testing!")
                .Scale(0.1f, 0.1f, 0.1f)
                .Position(128, 512);

            RenderScene->Add(Path);
            RenderScene->Add(Text);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/SVG.psl");
            Renderer->RenderPipeline(RenderPipeline);
        }
        void CreateSizedResources() override
        {
            FBO = new FrameBuffer(RenderWindow->ClientArea().Scale(), TextureFormats::Byte4, TextureFormats::DepthStencil);
            Renderer->RenderTarget(FBO);
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
