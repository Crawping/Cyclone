/* CHANGELOG
 * Written by Josh Grooms on 20160922
 */

#include "Console.h"
#include "EnumerationsSVG.h"
#include "GPU.h"
#include "NVPR.h"
#include "PathRenderer.h"
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



class Program : public PathRenderer
{
    public:

        Program() :
            PathRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Rounded Rectangle Rendering")
        {
            Initialize();
        }

    protected:

        Path2D          Path;



        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            Vector<ControlPoint2D> path =
            {
                { PathCommands::RoundedRectangle, { -50, -50, 100, 100, 12 } },
                { PathCommands::Close, { } },
            };

            Path.Add(path)
                .StrokeColor(Color4::Cyan)
                .StrokeWidth(2)

                .Color(Color4::Red)
                .Scale(3)
                .Position(Vector3(RenderWindow->ClientArea().Scale() / 3.0f, 0));

            PathScene->Add(Path);
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Path.Z(-250 * sin(count));
            Path.Roll(count);
            count += 0.02f;

            PathRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
