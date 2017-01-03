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
            PathRenderer(Area(0, 0, 1024, 960), "NVIDIA Basic Rounded Rectangle Rendering")
        {
            Initialize();
        }

    protected:

        Rectangle2D     Path;



        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            Path
                .CornerRadius(0.25f)
                .StrokeWidth(0.0625f)

                .PrimaryColor(Color4::Red)
                .Position(Vector3(RenderWindow->ClientArea().Scale() / 3.0f, 0))
                .SecondaryColor(Color4::Cyan)
                .Scale(128)
                .Size(2.0f, 1.0f, 1.0f);

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
