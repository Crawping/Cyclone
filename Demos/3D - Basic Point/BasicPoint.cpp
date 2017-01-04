/* CHANGELOG
 * Written by Josh Grooms on 20160827
 */

#include "BasicRenderer.h"
#include "Window3D.h"
#include "Geometry/Point3D.h"
#include "Scenes/Scene3D.h"

using namespace Renderers;



class Program : public BasicRenderer
{
    public:
        Program() : 
            BasicRenderer(Area(0, 0, 1024, 960), "Basic Point Rendering")
        {
            Initialize();
        }

    protected:
        Point3D Point;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Point
                .PrimaryColor(Color4::Blue)
                .Position(RenderWindow->ClientArea().Center())
                .Scale(100);

            RenderScene->Insert(Point);
        }
        
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}