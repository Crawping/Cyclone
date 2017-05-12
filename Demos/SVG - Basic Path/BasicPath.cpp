/* CHANGELOG
 * Written by Josh Grooms on 20160915
 */

#include "PathRenderer.h"
#include "EnumerationsSVG.h"
#include "GPU.h"
#include "NVPR.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Collections/Vector.h"
#include "Geometry/Geometry2D.h"
#include "Geometry/Path2D.h"
#include "Imaging/Color4.h"
#include "IO/Console.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"

using namespace Cyclone::Platform;
using namespace Cyclone::SVG;
using namespace Cyclone::Utilities;
using namespace Renderers;



class Program : public PathRenderer
{
    public:

        Program() :
            PathRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Path Rendering"),
            Path(Geometry2D::Star())
        {            
			Initialize();
        }
        
    protected:

        Path2D          Path;



        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            Path
                .JoinStyle(JoinStyles::Round)
                .StrokeWidth(6.5f)

                .Offset(-200.0f, 0.0f, 0.0f)
                .Position(Vector3(RenderWindow->ClientArea().Scale() / Vector2(2.0f, 3.0f), -100))
                .PrimaryColor(Color4::Blue)
                .Scale(2)
                .SecondaryColor(Color4::Black);

            PathScene->Insert(Path);
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Path.Z(-225 * sin(count));
            Path.Yaw(count);
            count += 0.02f;

            PathScene->Update(Path);
            PathRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
