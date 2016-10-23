/* CHANGELOG
 * Written by Josh Grooms on 20160915
 */

#include "PathRenderer.h"
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



class Program : public PathRenderer
{
    public:

        Program() :
            PathRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Text Rendering")
        {
            Initialize();
        }

    protected:

        Text2D Text;


		
		void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            Text
                .Text("Testing!")
                .Position(224, 320)
                .PrimaryColor(Color4::Green)
                .Scale(0.05f, 0.05f)
                .SecondaryColor(Color4::Black);

            PathScene->Add(Text);
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Text.Z(-1024 * sin(count) - 1024);
            Text.Yaw(count);
            count += 0.02f;

            PathScene->Update(Text);

            PathRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
