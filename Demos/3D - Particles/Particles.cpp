/* CHANGELOG
 * Written by Josh Grooms on 20161226
 */

#include "AdvancedRenderer.h"
#include "Collections/Vector.h"
#include "Geometry/Point3D.h"

using namespace Renderers;


class PointCloud : public Point3D
{
    public:

        PointCloud() 
        {
            Geometry().Topology(VertexTopologies::Points);
        }

        void Add(const Vector<Vector3>& points)
        {
            Geometry().Points(points);
            Geometry().Normals(Vector<Vector3>(points.Count()).Fill(Vector3::UnitZ));
            Geometry().Mapping(Vector<Vector3>(points.Count()).Fill(0));
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
            Vector3 szPoints = Vector3(256);
            uint npts = 1000000;
            Vector<Vector3> vertices = Vector<Vector3>(npts);

            for (uint a = 0; a < vertices.Count(); a++)
            {
                Color4 color = Color4::Random();
                vertices(a) = (Vector3(color.R, color.G, color.B) * szPoints) - (szPoints / 2.0f);
            }

            Points.Add(vertices);
            Points
                .PrimaryColor(Color4::Blue)
                .Scale(16);

            RenderScene->Insert(Points);
            RenderScene->IsDepthTestEnabled(true);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../3D - Particles/Points.psl");
        }

        void UpdateScene() override
        {
            Color4 color
            (
                0.5f * sinf(Points.Yaw()) + 0.5f,
                0.25f * cosf(Points.Yaw()) + 0.75f,
                0.125f * sinf(Points.Yaw()) + 0.875,
                0.25f
            );

            Points
                .PrimaryColor(color)
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