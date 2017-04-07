/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#include "AdvancedRenderer.h"
#include "Console.h"
#include "GPU.h"
#include "Utilities.h"
#include "Window3D.h"

#include "Geometry/Mesh3D.h"
#include "Geometry/Model3D.h"
#include "Geometry/Point3D.h"
#include "Geometry/Vertex.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "Spatial/Camera.h"

using namespace Renderers;
using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;



class Program : public AdvancedRenderer
{
    public:
        Program() :
            AdvancedRenderer(Area(0, 0, 1024, 960), "Navigable 3D Scene")
        {
            Initialize();
        }



    protected:

        Model3D  Cube;
        Model3D  Cylinder;
        Model3D  Icosahedron;
        Point3D Point;


        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();

            Cube = Model3D(Mesh3D::Cube(true));
            Icosahedron = Model3D(Mesh3D::Icosahedron());
            Cylinder = Model3D(Mesh3D::Cylinder(64));
        
            Vector2 ctrWin = RenderWindow->ClientArea().Center();
            Vector2 szWin = RenderWindow->Size();

            Cube
                .PrimaryColor(Color4::Yellow)
                .Scale(100, 100, 100)
                .Translate(Vector3(ctrWin - (szWin / 8.0f), 50));

            Cylinder
                .PrimaryColor(Color4(0.0f, 0.75f, 1.0f))
                .Scale(50, 125, 50)
                .Translate(Vector3(ctrWin + (szWin / Vector2(8.0f, -8.0f)), 50));

            Icosahedron
                .PrimaryColor(Color4::Magenta)
                .Scale(100, 100, 100)
                .Translate(Vector3(ctrWin + (szWin / 8.0f), 50));

            Point
                .PrimaryColor(Color4::Cyan)
                .Scale(100, 100, 1)
                .Translate(Vector3(ctrWin + (szWin / Vector2(-8.0f, 8.0f))));

            RenderScene->Insert(Cube);
            RenderScene->Insert(Cylinder);
            RenderScene->Insert(Icosahedron);
            RenderScene->Insert(Point);
        }
        void UpdateScene() override
        {
            Cube.Rotate(Vector3(0.0f, 0.01f, 0.0f));
            Cylinder.Rotate(Vector3(0.0f, 0.0f, 0.01f));
            Icosahedron.Rotate(Vector3(0.01f, 0.0f, 0.0f));
            Point.Rotate(Vector3(0.01f));                       // <-- Points can only be scaled and translated, so this has no effect.

            RenderScene->Update(Cube);
            RenderScene->Update(Cylinder);
            RenderScene->Update(Icosahedron);
            RenderScene->Update(Point);

            AdvancedRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
