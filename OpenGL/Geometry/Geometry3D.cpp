#include "Constants.h"
#include "Utilities.h"
#include "Geometry/Geometry3D.h"


namespace Cyclone
{
    namespace OpenGL
    {

        /** UTILITIES **/
        void Geometry3D::CalculateNormals()
        {
            const auto& vertices = Points();
            _normals = Vector<Vector3>(vertices.Count());

            for (uint a = 0; a < vertices.Count(); a += 3)
            {
                Vector3 diff1 = vertices(a + 1) - vertices(a);
                Vector3 diff2 = vertices(a + 2) - vertices(a);
                Vector3 diff3 = vertices(a + 2) - vertices(a + 1);
   
                _normals(a)     = Math::Cross(diff1, diff2).Normalize();
                _normals(a + 1) = Math::Cross(diff3, -diff1).Normalize();
                _normals(a + 2) = Math::Cross(-diff2, -diff3).Normalize();
            }
        }
        void Geometry3D::Tessellate(uint n)
        {

            if (n > 1)
                Geometry3D::Tessellate(n - 1);

            Vector<Vector3> vertices = Points();
            uint nvertices = vertices.Count() * 12;

            _points = Vector<Vector3>(nvertices);

            uint idx = 0;
            for (uint a = 0; a < vertices.Count(); a += 3)
            {
                Vector3 midpt1 = vertices(a) + ((vertices(a + 1) - vertices(a)) * 0.5f);
                Vector3 midpt2 = vertices(a) + ((vertices(a + 2) - vertices(a)) * 0.5f);
                Vector3 midpt3 = vertices(a + 1) + ((vertices(a + 2) - vertices(a + 1)) * 0.5f);

                _points(idx++) = vertices(a);
                _points(idx++) = midpt1;
                _points(idx++) = midpt2;

                _points(idx++) = midpt1;
                _points(idx++) = vertices(a + 1);
                _points(idx++) = midpt3;
                
                _points(idx++) = midpt2;
                _points(idx++) = midpt1;
                _points(idx++) = midpt3;

                _points(idx++) = midpt2;
                _points(idx++) = midpt3;
                _points(idx++) = vertices(a + 2);
            }
        }



        /** GEOMETRY GENERATING FUNCTIONS **/
        Geometry3D Geometry3D::Cube(bool isIndexed)
        {
            Geometry3D geometry;

            if (isIndexed)
            {
                geometry.Indices
                ({
                     0,  1,  2,  2,  1,  3,
                     4,  5,  6,  6,  5,  7,
                     8,  9, 10, 10,  9, 11,
                    12, 13, 14, 14, 13, 15,
                    16, 17, 18, 18, 17, 19,
                    20, 21, 22, 22, 21, 23,
                });

                // Front
                geometry.Add({ -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f, 0.0f });

                // Top
                geometry.Add({ -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Bottom
                geometry.Add({ -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Left
                geometry.Add({ -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Right
                geometry.Add({  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Back
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f });
            }
            else
            {
                // Front
                geometry.Add({ -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Add({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f, 0.0f });

                // Top
                geometry.Add({ -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Add({ -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Bottom
                geometry.Add({ -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Add({ -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Left
                geometry.Add({ -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Add({ -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Right
                geometry.Add({  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Add({  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Back
                geometry.Add({  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Add({  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({ -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f });
            }

            return geometry;
        }
        Geometry3D Geometry3D::Cylinder(uint nfaces, bool isIndexed)
        {
            Geometry3D geometry;
            if (isIndexed)
            {

            }
            else
            {
                nfaces = Math::Max(3, nfaces);

                float angleStep = Constants::TwoPi / nfaces;
                float hAngleStep = angleStep / 2.0f;

                for (int a = 0; a < nfaces; a++)
                {
                    float ctAngle = angleStep * a;
                    float hAngle = ctAngle * hAngleStep;
                    float ntAngle = angleStep * (a + 1);

                    float x1 = cosf(ctAngle);
                    float z1 = -sinf(ctAngle);
                    float x2 = cosf(ntAngle);
                    float z2 = -sinf(ntAngle);

                    geometry.Add({ x1, -0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Add({ x2, -0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Add({ x1,  0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Add({ x1,  0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Add({ x2, -0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Add({ x2,  0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                }
            }

            return geometry;
        }
        Geometry3D Geometry3D::Icosahedron(bool isIndexed)
        {
            Geometry3D geometry;

            if (isIndexed)
            {

            }
            else
            {
                geometry.Add({  0.525731f,          0,  0.850651f }); // 1
                geometry.Add({          0,  0.850651f,  0.525731f }); // 4
                geometry.Add({ -0.525731f,          0,  0.850651f }); // 0

                geometry.Add({          0,  0.850651f,  0.525731f }); // 4
                geometry.Add({ -0.850651f,  0.525731f,          0 }); // 9
                geometry.Add({ -0.525731f,          0,  0.850651f }); // 0

                geometry.Add({          0,  0.850651f,  0.525731f }); // 4
                geometry.Add({          0,  0.850651f, -0.525731f }); // 5
                geometry.Add({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Add({  0.850651f,  0.525731f,          0 }); // 8
                geometry.Add({          0,  0.850651f, -0.525731f }); // 5
                geometry.Add({          0,  0.850651f,  0.525731f }); // 4

                geometry.Add({  0.525731f,          0,  0.850651f }); // 1
                geometry.Add({  0.850651f,  0.525731f,          0 }); // 8
                geometry.Add({          0,  0.850651f,  0.525731f }); // 4

                geometry.Add({  0.525731f,          0,  0.850651f }); // 1
                geometry.Add({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Add({  0.850651f,  0.525731f,          0 }); // 8

                geometry.Add({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Add({  0.525731f,          0, -0.850651f }); // 3
                geometry.Add({  0.850651f,  0.525731f,          0 }); // 8

                geometry.Add({  0.850651f,  0.525731f,          0 }); // 8
                geometry.Add({  0.525731f,          0, -0.850651f }); // 3
                geometry.Add({          0,  0.850651f, -0.525731f }); // 5

                geometry.Add({  0.525731f,          0, -0.850651f }); // 3
                geometry.Add({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Add({          0,  0.850651f, -0.525731f }); // 5

                geometry.Add({  0.525731f,          0, -0.850651f }); // 3
                geometry.Add({          0, -0.850651f, -0.525731f }); // 7
                geometry.Add({ -0.525731f,          0, -0.850651f }); // 2

                geometry.Add({  0.525731f,          0, -0.850651f }); // 3
                geometry.Add({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Add({          0, -0.850651f, -0.525731f }); // 7

                geometry.Add({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Add({          0, -0.850651f,  0.525731f }); // 6
                geometry.Add({          0, -0.850651f, -0.525731f }); // 7

                geometry.Add({          0, -0.850651f,  0.525731f }); // 6
                geometry.Add({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Add({          0, -0.850651f, -0.525731f }); // 7

                geometry.Add({          0, -0.850651f,  0.525731f }); // 6
                geometry.Add({ -0.525731f,          0,  0.850651f }); // 0
                geometry.Add({ -0.850651f, -0.525731f,          0 }); // 11

                geometry.Add({          0, -0.850651f,  0.525731f }); // 6
                geometry.Add({  0.525731f,          0,  0.850651f }); // 1
                geometry.Add({ -0.525731f,          0,  0.850651f }); // 0

                geometry.Add({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Add({  0.525731f,          0,  0.850651f }); // 1
                geometry.Add({          0, -0.850651f,  0.525731f }); // 6

                geometry.Add({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Add({ -0.525731f,          0,  0.850651f }); // 0
                geometry.Add({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Add({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Add({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Add({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Add({          0,  0.850651f, -0.525731f }); // 5
                geometry.Add({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Add({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Add({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Add({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Add({          0, -0.850651f, -0.525731f }); // 7
            }

            geometry.CalculateNormals();
            return geometry;
        }
        Geometry3D Geometry3D::Line()
        {
            Geometry3D geometry;
            geometry.Add({ -0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            geometry.Add({  0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            return geometry;
        }
        Geometry3D Geometry3D::Point()
        {
            Geometry3D geometry;
            geometry.Add({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            return geometry;
        }
        Geometry3D Geometry3D::Quad(bool isIndexed)
        {
            Geometry3D geometry;

            if (isIndexed)
            {

            }
            else
            {
                geometry.Add({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Add({  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
                geometry.Add({  0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
            }

            return geometry;
        }
        Geometry3D Geometry3D::Sphere(uint n)
        {
            Geometry3D geometry = Geometry3D::Icosahedron();
            geometry.Tessellate(n);

            Vector<Vector3> points = geometry.Points();
            Vector<Vector3> normals = Vector<Vector3>(points.Count());
            Vector<Vector3> mapping = Vector<Vector3>(points.Count());

            for (uint a = 0; a < points.Count(); a++)
            {
                points(a).Normalize();
                normals(a) = points(a);
                mapping(a) = Vector3::Zero;
            }

            geometry
                .Mapping(mapping)
                .Normals(normals)
                .Points(points);

            return geometry;
        }
        Geometry3D Geometry3D::Triangle()
        {
            Geometry3D geometry;
            geometry.Add({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            geometry.Add({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
            geometry.Add({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
            return geometry;
        }

    }
}
