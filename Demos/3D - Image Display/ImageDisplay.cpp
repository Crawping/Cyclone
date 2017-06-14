/* CHANGELOG
 * Written by Josh Grooms on 20161001
 */

#include "AdvancedRenderer.h"
#include "EnumerationsGL.h"
#include "GPU.h"
#include "Window3D.h"

#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"
#include "Imaging/Bitmap.h"
#include "IO/Console.h"
#include "Models/Model3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Textures/Texture2D.h"
using namespace Renderers;



class Program : public AdvancedRenderer
{
    public:

        Program() :
            AdvancedRenderer(Area(0, 0, 1024, 960), "Image Display", 0)
        {
            Initialize();
        }

        ~Program()
        {
            for (auto i : Images)
                delete i;

            for (auto q : Quads)
                delete q;
        }

    protected:

        Vector<Texture2D*>  Images;
        Vector<Entity3D*> Quads;


        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();

            Vector<string> images = 
            {
                "../3D - Image Display/World (21600x10800).jpg",
                "../3D - Image Display/Solar System (12000x7000).jpg",
                "../3D - Image Display/Dorset Durdle (6400x4000).jpg",
                "../3D - Image Display/Scottish Beach (1080x1920).jpg",
            };

            uint nimgs = images.Count();
            Images = Vector<Texture2D*>(nimgs);
            Quads = Vector<Entity3D*>(nimgs);

            for (uint a = 0; a < nimgs; a++)
            {
                Images(a) = new Texture2D(images(a));
                Images(a)->GenerateMipmap();
                Images(a)->MakeResident();

                Quads(a) = new Entity3D();
                Quads(a)->
                     Geometry(Mesh3D::Quad(true))
                    .PrimaryColor(Color4::Blue)
                    .Position(RenderWindow->ClientArea().Center())
                    .Scale(Vector3(Images(a)->Width() / 10.0f, Images(a)->Height() / 10.0f))
                    .Texture(Images(a))
                    .Z(a * 100);

                RenderScene->Insert(*Quads(a));
            }
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline
            (
                "../Renderers/Shaders/Default.vsl",
                "../3D - Image Display/TexturedShading.psl"
            );
        }


};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
