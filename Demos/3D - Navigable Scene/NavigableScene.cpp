/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#include "AdvancedRenderer.h"
#include "GPU.h"
#include "Utilities.h"
#include "Window3D.h"

#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"
#include "Models/Model3D.h"
#include "Models/Point3D.h"
#include "Geometry/Vertex.h"
#include "IO/Console.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "Spatial/Camera.h"

using namespace Cyclone::Platform;
using namespace Cyclone::Renderers;
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

        Resource<Entity3D> Cube;
        Resource<Entity3D> Cylinder;
        Resource<Entity3D> Icosahedron;
        //Point3D Point;


        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();

            Cube            = Create<Entity3D>("Cube");
            Cylinder        = Create<Entity3D>("Cylinder");
            Icosahedron     = Create<Entity3D>("Icosahedron");

            auto cube       = Create("Cube", Function<Mesh3D, bool>(&Mesh3D::Cube), true);
            auto cyl        = Create("Cylinder", Function<Mesh3D, uint, bool>(&Mesh3D::Cylinder), 64U, false);
            auto icos       = Create("Icosahedron", Function<Mesh3D, bool>(&Mesh3D::Icosahedron), false);

            Vector2 ctrWin  = RenderWindow->ClientArea().Center();
            Vector2 szWin   = RenderWindow->Size();

            Cube->
                 Material(Create<Material3D>("Cube"))
                .Model(Create<Model3D>("Cube"))
                .Geometry(cube)
                .PrimaryColor(Color4(0.0f, 0.5f, 0.5f))
                .Translate(Vector3(ctrWin - (szWin / 8.0f), 50))
                .Scale(100, 100, 100);

            Cylinder->
                 Material(Create<Material3D>("Cylinder"))
                .Model(Create<Model3D>("Cylinder"))
                .Geometry(cyl)
                .PrimaryColor(Color4(0.0f, 0.75f, 1.0f))
                .Translate(Vector3(ctrWin + (szWin / Vector2(8.0f, -8.0f)), 50))
                .Scale(50, 125, 50);

            Icosahedron->
                 Material(Create<Material3D>("Icosahedron"))
                .Model(Create<Model3D>("Icosahedron"))
                .Geometry(icos)
                .PrimaryColor(Color4::Magenta)
                .Translate(Vector3(ctrWin + (szWin / 8.0f), 50))
                .Scale(100, 100, 100);

            //Point
            //    .PrimaryColor(Color4::Cyan)
            //    .Scale(100, 100, 1)
            //    .Translate(Vector3(ctrWin + (szWin / Vector2(-8.0f, 8.0f))));

            RenderScene->Insert(Cube);
            RenderScene->Insert(Cylinder);
            RenderScene->Insert(Icosahedron);
            //RenderScene->Insert(Point);
        }
        void UpdateScene() override
        {
            Cube->Rotate(Vector3(0.0f, 0.01f, 0.0f));
            Cylinder->Rotate(Vector3(0.0f, 0.0f, 0.01f));
            Icosahedron->Rotate(Vector3(0.01f, 0.0f, 0.0f));
            //Point.Rotate(Vector3(0.01f));                       // <-- Points can only be scaled and translated, so this has no effect.

            RenderScene->Update(Cube);
            RenderScene->Update(Cylinder);
            RenderScene->Update(Icosahedron);
            //RenderScene->Update(Point);

            AdvancedRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
