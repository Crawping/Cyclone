/* CHANGELOG 
 * Written by Josh Grooms on 20160825
 */

#include "BasicRenderer.h"
#include "Window3D.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
//#include "Spatial/Geometry.h"
#include "Geometry/Geometry.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;
using namespace Cyclone::Utilities;



class Program : public BasicRenderer
{
    public:
        Program() : 
            BasicRenderer("Basic Triangle Rendering"),
            Triangle(Geometry::Triangle())
        { 
            Initialize();
        }

    protected:
        Mesh3D  Triangle;

        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();
            Triangle.Scale(100, 100).Position(RenderWindow->ClientArea().Center());
            RenderScene->Add(Triangle);
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}