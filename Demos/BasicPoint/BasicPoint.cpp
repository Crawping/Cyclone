/* CHANGELOG
 * Written by Josh Grooms on 20160827
 */

#include "BasicRenderer.h"
#include "Window3D.h"
#include "Geometry/Point3D.h"
#include "Geometry/Scene3D.h"

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
            Point.Color(Color4::Blue).Scale(100, 100).Position(RenderWindow->ClientArea().Center());
            RenderScene->Add(Point);
        }
        
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}