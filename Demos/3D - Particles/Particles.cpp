/* CHANGELOG
 * Written by Josh Grooms on 20161226
 */

#include "AdvancedRenderer.h"
#include "Geometry/Point3D.h"

using namespace Renderers;


class PointCloud : public Point3D
{
    public:

        PointCloud() 
        {
            Geometry().Topology(VertexTopologies::Points);
        }

        virtual void Add(const Vector3& position, const Vector3& normal = 0, const Vector3& mapping = 0)
        {
            Geometry().Add(position, normal, mapping);
        }

};



class Program : public AdvancedRenderer
{
    public:
        Program() : 
            AdvancedRenderer(Area(0, 0, 1024, 960), "Particle Rendering")
        {
            Initialize();
        }        

    protected:

        PointCloud Points;


        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();

            for (uint a = 0; a < 10000; a++)
            {
                Color4 color = Color4::Random();
                Points.Add(Vector3(color.R * 128, color.G * 96, color.B * 100), Vector3::UnitZ);
            }

            Points
                .PrimaryColor(Color4::Blue)
                .Scale(10);

            RenderScene->Insert(Points);
        }

        void UpdateScene() override
        {
            Points
                .PrimaryColor(Color4::Random())
                .Rotate(0.0f, 0.01f, 0.0f);

            RenderScene->Update(Points);
            AdvancedRenderer::UpdateScene();
        }
        
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}