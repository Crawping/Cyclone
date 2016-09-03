/* CHANGELOG 
 * Written by Josh Grooms on 20160902
 */


#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Point3D.h"
#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"
using namespace Renderers;



class Program : public BasicRenderer
{
    public:

        Program() : 
            BasicRenderer("Mixed Topology Rendering"),
            Cube(Geometry::Cube()),
            IndexedCube(nullptr),
            Point()
        {
            Array<uint> indices;
            Array<Vertex::Standard> vertices = Geometry::Cube(indices);
            IndexedCube = new Mesh3D(vertices, indices);

            Initialize();

            glEnable(GL_CULL_FACE);
        }

    protected:
        
        Mesh3D  Cube;
        Mesh3D* IndexedCube;
        Point3D Point;


        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            Vector2 ctrWin = RenderWindow->ClientArea().Center();
            Vector2 szWin = RenderWindow->Size();

            Cube.Scale(100, 100, 100)
                .Color(Color4::Yellow)
                .Translate(Vector3(ctrWin - (szWin / 8.0f), 50));

            IndexedCube->Scale(100, 100, 100)
                .Color(Color4::Magenta)
                .Translate(Vector3(ctrWin + (szWin / 8.0f), 50));

            Point.Scale(100, 100, 1)
                .Color(Color4::Cyan)
                .Translate(Vector3(ctrWin + (szWin / Vector2(-8.0f, 8.0f))));

            RenderScene->Add(Cube);
            RenderScene->Add(*IndexedCube);
            RenderScene->Add(Point);
        }
        

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Depth.psl");
            Renderer->RenderPipeline(RenderPipeline);
        }

        void UpdateScene() override
        {
            Cube.Rotate(Vector3(0.0f, 0.01f, 0.0f));
            IndexedCube->Rotate(Vector3(0.01f, 0.0f, 0.0f));
            Point.Rotate(Vector3(0.01f));                       // <-- Points can only be scaled and translated.

            RenderScene->Add(Cube);
            RenderScene->Add(*IndexedCube);
            RenderScene->Add(Point);

            BasicRenderer::UpdateScene();
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}