/* CHANGELOG 
 * Written by Josh Grooms on 20161001
 */

#include "AdvancedRenderer.h"
#include "Console.h"
#include "EnumerationsGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Geometry/Quad3D.h"
#include "Geometry/Scene3D.h"
#include "Imaging/Bitmap.h"
#include "Pipelines/ShaderPipeline.h"
#include "Textures/Texture2D.h"
using namespace Renderers;



class Program : public AdvancedRenderer
{
    public:

        Program() : 
            AdvancedRenderer(Area(0, 0, 1024, 960), "Image Display", 0),
            Image(nullptr)
        {
            Initialize();
        }

        ~Program()
        {
            if (Image) { delete Image; }
        }

    protected:

        Texture2D*  Image;
        Quad3D      Quad;

        
        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();

            Image = new Texture2D("../ImageDisplay/World (21600x10800).jpg");
            //Image = new Texture2D("../ImageDisplay/Dorset Durdle (6400x4000).jpg");
            //Image = new Texture2D("../ImageDisplay/Scottish Beach (1080x1920).jpg");
            //Image = new Texture2D("../ImageDisplay/Solar System (12000x7000).jpg");

            Image->Sampler.EdgeWrap = WrapModes::Repeat;
            Image->GenerateMipmap();
            Image->Bind();

            Quad
                .Color(Color4::Blue)
                .Position(RenderWindow->ClientArea().Center())
                .Scale(Image->Width() / 10.0f, Image->Height() / 10.0f);

            RenderScene->Add(Quad);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../ImageDisplay/TexturedShading.psl");
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}