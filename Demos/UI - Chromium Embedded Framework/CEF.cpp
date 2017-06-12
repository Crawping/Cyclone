/* CHANGELOG
 * Written by Josh Grooms on 20170612
 */

#include "BasicRenderer.h"
#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"
#include "Scenes/Scene3D.h"
#include "include/cef_app.h"
using namespace Renderers;
using namespace Cyclone::OpenGL;



class Program: public BasicRenderer
{
    public:

        Program():
            BasicRenderer(Area(0, 0, 1024, 960), "UI - CEF"),
            Cube()
        {
            Initialize();
        }



    protected:

        Entity3D Cube;


        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Cube
                .Geometry(Mesh3D::Cube(true))
                .PrimaryColor(Color4::Blue)
                .Translate(Vector3(512, 480, 50))
                .Scale(Vector3(200, 200, 200));

            RenderScene->Insert(Cube);
            RenderScene->Update(Cube);
        }
};




int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}