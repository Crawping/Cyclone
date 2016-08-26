
#include "BasicRenderer.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Spatial/Geometry.h"

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
            CreateSizedResources();
            CreateSceneResources();
        }

    protected:
        Mesh3D  Triangle;

        void CreateSceneResources() override
        {
            Triangle.Scale(100, 100).Translate(512 - 50, 480 - 50);
            RenderScene->Add(Triangle);
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}