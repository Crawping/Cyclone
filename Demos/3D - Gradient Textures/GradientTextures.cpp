/* CHANGELOG
 * Written by Josh Grooms on 20161110
 */



#include "Console.h"
#include "BasicRenderer.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Model3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "Textures/GradientTexture.h"
using namespace Renderers;



class Program : public BasicRenderer
{
    public:

        Program() : 
            BasicRenderer(Area(0, 0, 1024, 960), "3D - Gradient Textures"),
            Gradient(nullptr)
        {
            Initialize();
        }
        ~Program()
        {
            if (Gradient) { delete Gradient; }
        }

    protected:

        GradientTexture*    Gradient;
        Model3D              Quad;



        void CreateSceneResources() override
        {
            BasicRenderer::CreateSceneResources();

            ColorGradient gradient =
            {
                { 0.00f, Color4::Blue },
                //{ 0.875f, Color4::Gray },
                //{ 0.50f, Color4::Cyan },
                //{ 0.25f, Color4::Green },
                //{ 0.50f, Color4::Red },
                //{ 0.75f, Color4::Green },
                { 1.00f, Color4::Cyan },
            };

            Gradient = new GradientTexture(8, gradient);
            Gradient->Update();
            Gradient->Bind();

            Vector<Color4> g = gradient.ToVector(2);
            for (uint a = 0; a < g.Count(); a++)
                Console::WriteLine(g(a).ToString());

            Quad
                .Geometry(Mesh3D::Quad(true))
                .Position(RenderWindow->ClientArea().Center())
                .Scale(512, 256);

            RenderScene->Insert(Quad);
        }

        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../3D - Gradient Textures/GradientTexture.psl");
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}