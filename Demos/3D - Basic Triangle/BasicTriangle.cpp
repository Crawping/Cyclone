/* CHANGELOG 
 * Written by Josh Grooms on 20160825
 */

#include "BasicRenderer.h"
#include "Window3D.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Geometry3D.h"
#include "Scenes/Scene3D.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;
using namespace Cyclone::Utilities;



class Program : public BasicRenderer
{
    public:
        Program() : 
            BasicRenderer(Area(0, 0, 1024, 960), "Basic Triangle Rendering"),
            Triangle(Geometry3D::Triangle())
        { 
            Initialize();
        }

    protected:
        Mesh3D  Triangle;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Triangle
                .Position(RenderWindow->ClientArea().Center())
                .Scale(100);

            RenderScene->Insert(Triangle);
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}