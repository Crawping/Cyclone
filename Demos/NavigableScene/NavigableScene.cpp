/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#include "AdvancedRenderer.h"
#include "Console.h"
#include "GPU.h"
#include "Utilities.h"
#include "Window3D.h"

#include "Geometry/Geometry3D.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Point3D.h"
#include "Geometry/Scene3D.h"
#include "Geometry/Vertex.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"
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
        ~Program()
        {
            if (Cylinder) { delete Cylinder; }
            if (Icosahedron) { delete Icosahedron; }
            if (Cube) { delete Cube; }
        }




    protected:

        Mesh3D* Cube;
        Mesh3D* Cylinder;
        Mesh3D* Icosahedron;
        Point3D Point;


        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();

            Vector<uint> indices;
            Vector<Vertex::Standard> vertices = Geometry3D::Cube(indices);
            Cube = new Mesh3D(vertices, indices);

            vertices = Geometry3D::Icosahedron();
            Icosahedron = new Mesh3D(vertices);

            vertices = Geometry3D::Cylinder(64);
            Cylinder = new Mesh3D(vertices);

            Vector2 ctrWin = RenderWindow->ClientArea().Center();
            Vector2 szWin = RenderWindow->Size();

            Cube->Scale(100, 100, 100)
                .Color(Color4::Yellow)
                .Translate(Vector3(ctrWin - (szWin / 8.0f), 50));

            Cylinder->Color(Color4(0.0f, 0.75f, 1.0f))
                .Scale(50, 125, 50)
                .Translate(Vector3(ctrWin + (szWin / Vector2(8.0f, -8.0f)), 50));

            Icosahedron->Scale(100, 100, 100)
                .Color(Color4::Magenta)
                .Translate(Vector3(ctrWin + (szWin / 8.0f), 50));

            Point.Scale(100, 100, 1)
                .Color(Color4::Cyan)
                .Translate(Vector3(ctrWin + (szWin / Vector2(-8.0f, 8.0f))));

            RenderScene->Add(*Cube);
            RenderScene->Add(*Cylinder);
            RenderScene->Add(*Icosahedron);
            RenderScene->Add(Point);
        }
        void UpdateScene() override
        {
            Cube->Rotate(Vector3(0.0f, 0.01f, 0.0f));
            Cylinder->Rotate(Vector3(0.0f, 0.0f, 0.01f));
            Icosahedron->Rotate(Vector3(0.01f, 0.0f, 0.0f));
            Point.Rotate(Vector3(0.01f));                       // <-- Points can only be scaled and translated, so this has no effect.

            RenderScene->Update(*Cube);
            RenderScene->Update(*Cylinder);
            RenderScene->Update(*Icosahedron);
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
