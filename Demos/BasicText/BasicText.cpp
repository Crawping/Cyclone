/* CHANGELOG
 * Written by Josh Grooms on 20160915
 */

#include "AdvancedRenderer.h"
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



class Program : public AdvancedRenderer
{
    public:

        Program() :
            AdvancedRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Text Rendering")
        {
            Initialize();
            nvPathStencilDepthOffset(-0.05f, -1);
            nvPathCoverDepthFunc(GL_ALWAYS);
        }

    protected:

        Text2D Text;


		
		void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Text
                .Text("Testing!")

                .Color(Color4::Green)
                .Scale(0.05f, 0.05f)
                .Position(224, 320);

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

            const Matrix4x4& projection = Renderer->Projection().ToMatrix4x4();
            const Matrix4x4& view = Renderer->View().ToMatrix4x4();

            nvMatrixLoadIdentity(TransformMatrices::Projection);
            nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Text.Z(-1024 * sin(count) - 1024);
            Text.Yaw(count);
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
