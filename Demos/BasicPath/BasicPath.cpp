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
#include "Collections/Vector.h"
#include "Geometry/Geometry2D.h"
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
            BasicRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Path Rendering", 4)
        {
            nvPathStencilDepthOffset(-0.05f, -1);
            nvPathCoverDepthFunc(GL_ALWAYS);
            
			Initialize();
        }

    protected:

        Path2D          Path;



        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Path.Add(Geometry2D::Star())
                .JoinStyle(JoinStyles::Round)
                .StrokeWidth(6.5f)

                .Color(Color4::Blue)
                .Scale(1)
                .Position(Vector3(RenderWindow->ClientArea().Scale() / Vector2(2.0f, 3.0f), -100));

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

			const Matrix4x4& projection = Projection.ToMatrix4x4();
			const Matrix4x4& view = View.ToMatrix4x4();

			nvMatrixLoadIdentity(TransformMatrices::Projection);
			nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Path.Z(-225 * sin(count));
            Path.Yaw(count);
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
