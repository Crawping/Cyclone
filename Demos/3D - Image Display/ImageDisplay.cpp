/* CHANGELOG
 * Written by Josh Grooms on 20161001
 */

#include "AdvancedRenderer.h"
#include "Console.h"
#include "EnumerationsGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Geometry/Mesh3D.h"
#include "Geometry/Model3D.h"
#include "Imaging/Bitmap.h"
#include "Pipelines/ShaderPipeline.h"
#include "Textures/Texture2D.h"
using namespace Renderers;



class Program : public AdvancedRenderer
{
    public:

        Program() :
            AdvancedRenderer(Area(0, 0, 1024, 960), "Image Display", 0)
            //Image(nullptr)
        {
            Initialize();
        }

        ~Program()
        {
            //Quads.Clear();
            //Images.Clear();
            //if (Image) { delete Image; }
            //for (auto i : Images)
            //    delete i;
        }

    protected:

        //Vector<Texture2D>  Images;
        Texture2D           Image;
        Model3D      Quad;
        //Vector<Model3D> Quads;


        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();

            Vector<string> images = 
            {
                "../3D - Image Display/World (21600x10800).jpg",
                "../3D - Image Display/Dorset Durdle (6400x4000).jpg",
                "../3D - Image Display/Scottish Beach (1080x1920).jpg",
                "../3D - Image Display/Solar System (12000x7000).jpg",
            };

            uint nimgs = images.Count();
            //Images = Vector<Texture2D>(nimgs);
            //Quads = Vector<Model3D>(nimgs);

            Texture2D Image(images(3));
            Image.GenerateMipmap();
            Image.MakeResident();

            Quad
                .Geometry(Mesh3D::Quad(true))
                .PrimaryColor(Color4::Blue)
                .Position(RenderWindow->ClientArea().Center())
                .Scale(Image.Width() / 10.0f, Image.Height() / 10.0f)
                .Texture((const Texture2D*)&Image);

            RenderScene->Insert(Quad);

            //Image = new Texture2D("../3D - Image Display/World (21600x10800).jpg");
            //Image = new Texture2D("../ImageDisplay/Dorset Durdle (6400x4000).jpg");
            //Image = new Texture2D("../ImageDisplay/Scottish Beach (1080x1920).jpg");
            //Image = new Texture2D("../ImageDisplay/Solar System (12000x7000).jpg");

            //for (auto& i : images)
            //for (uint a = 0; a < 1; a++)
            //{
            //    Images(a) = Texture2D(images(a));
            //    Images(a).Sampler.EdgeWrap(WrapModes::Repeat);
            //    Images(a).GenerateMipmap();
            //    Images(a).Bind();
            //    Images(a).MakeResident();


            //    Quads(a) = Model3D(Mesh3D::Quad(true));
            //    Quads(a)
            //        .PrimaryColor(Color4::Blue)
            //        .Position(RenderWindow->ClientArea().Center())
            //        .Scale(Images(a).Width() / 10.0f, Images(a).Height() / 10.0f)
            //        .Texture(&Images(a));

            //    RenderScene->Insert(Quads(a));
            //}

            //Image->Sampler.EdgeWrap(WrapModes::Repeat);
            //Image->GenerateMipmap();
            //Image->Bind();
            //Image->MakeResident();

            //Quad
            //    .Geometry(Mesh3D::Quad(true))
            //    .PrimaryColor(Color4::Blue)
            //    .Position(RenderWindow->ClientArea().Center())
            //    .Scale(Image->Width() / 10.0f, Image->Height() / 10.0f)
            //    .Texture(Image);

            //RenderScene->Insert(Quad);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../3D - Image Display/TexturedShading.psl");
            //RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../Renderers/Shaders/Default.psl");
        }


};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
