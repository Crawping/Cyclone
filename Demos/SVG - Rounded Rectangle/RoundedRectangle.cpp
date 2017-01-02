/* CHANGELOG
 * Written by Josh Grooms on 20160922
 */

#include "PathRenderer.h"
#include "Geometry/Rectangle2D.h"
#include "Imaging/Color4.h"
#include "Scenes/Scene3D.h"

using namespace Cyclone::SVG;
using namespace Cyclone::Utilities;
using namespace Renderers;



class Program : public PathRenderer
{
    public:

        Program() :
            PathRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Rounded Rectangle Rendering"),
            Path(0.25f)
        {
            Initialize();
        }

    protected:

        Rectangle2D     Path;



        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            Path
                .StrokeWidth(0.0625f)
                .PrimaryColor(Color4::Red)
                .SecondaryColor(Color4::Cyan)
                .Position(Vector3(RenderWindow->ClientArea().Scale() / 3.0f, 0))
                .Scale(128);

            PathScene->Insert(Path);
        }
        void UpdateScene() override
        {
            static float count = 0.0f;
            Path.Z(-250 * sin(count));
            Path.Roll(count);
            Path.CornerRadius(0.5f * abs(sin(count)));
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