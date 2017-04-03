#include "Utilities.h"
#include "Geometry/Mesh3D.h"
#include "Math/Constants.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /** INTERNAL FUNCTIONS**/
        constexpr Vector3 midpoint(const Vector3& u, const Vector3& v)
        {
            return (v - u) * 0.5f + u;
        }
        static Vertex midpoint(const Vertex& u, const Vertex& v)
        {
            return Vertex
            (
                midpoint(u.Position, v.Position),
                midpoint(u.Normal, v.Normal),
                (Vector2)midpoint(u.UV, v.UV)
            );
        }



        /** PUBLIC UTILITIES **/
        void Mesh3D::CalculateNormals()
        {
            auto pts = Points();
            auto nms = Normals();

            for (uint a = 0; a < pts.Count(); a += 3)
            {
                Vector3 diff1 = pts(a + 1) - pts(a);
                Vector3 diff2 = pts(a + 2) - pts(a);
                Vector3 diff3 = pts(a + 2) - pts(a + 1);

                SetNormal(a, Math::Cross(diff1, diff2).Normalize());
                SetNormal(a + 1, Math::Cross(diff3, -diff1).Normalize());
                SetNormal(a + 2, Math::Cross(-diff2, -diff3).Normalize());
            }
        }
        void Mesh3D::Tessellate(uint n)
        {
            if (n > 1)
                Mesh3D::Tessellate(n - 1);

            uint nNewVertices = Vertices.Count() * 12;
            Vector<Vertex> newVertices = Vector<Vertex>(nNewVertices);

            uint idx = 0;
            for (uint a = 0; a < Vertices.Count(); a += 3)
            {
                Vertex v1 = Vertices(a), v2 = Vertices(a + 1), v3 = Vertices(a + 2);
                Vertex m1 = midpoint(v1, v2), m2 = midpoint(v1, v3), m3 = midpoint(v2, v3);

                newVertices(idx++) = v1;
                newVertices(idx++) = m1;
                newVertices(idx++) = m2;

                newVertices(idx++) = m1;
                newVertices(idx++) = v2;
                newVertices(idx++) = m3;

                newVertices(idx++) = m2;
                newVertices(idx++) = m1;
                newVertices(idx++) = m3;

                newVertices(idx++) = m2;
                newVertices(idx++) = m3;
                newVertices(idx++) = v3;
            }

            Vertices = newVertices;
        }



        /** GEOMETRY GENERATING FUNCTIONS **/
        Mesh3D Mesh3D::Cube(bool isIndexed)
        {
            Mesh3D geometry;

            if (isIndexed)
            {
                Vector<uint> indices = 
                {
                     0,  1,  2,  2,  1,  3,
                     4,  5,  6,  6,  5,  7,
                     8,  9, 10, 10,  9, 11,
                    12, 13, 14, 14, 13, 15,
                    16, 17, 18, 18, 17, 19,
                    20, 21, 22, 22, 21, 23,
                };

                geometry.Append(indices);

                // Front
                geometry.Append({ -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f, 0.0f });

                // Top
                geometry.Append({ -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Bottom
                geometry.Append({ -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Left
                geometry.Append({ -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Right
                geometry.Append({  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Back
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f });
            }
            else
            {
                // Front
                geometry.Append({ -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Append({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f, 0.0f });

                // Top
                geometry.Append({ -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Append({ -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Bottom
                geometry.Append({ -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Append({ -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Left
                geometry.Append({ -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Append({ -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Right
                geometry.Append({  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Append({  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

                // Back
                geometry.Append({  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });

                geometry.Append({  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({ -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f });
            }

            return geometry;
        }
        Mesh3D Mesh3D::Cylinder(uint nfaces, bool isIndexed)
        {
            Mesh3D geometry;
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

                    geometry.Append({ x1, -0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Append({ x2, -0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Append({ x1,  0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Append({ x1,  0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Append({ x2, -0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                    geometry.Append({ x2,  0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                }
            }

            return geometry;
        }
        Mesh3D Mesh3D::Icosahedron(bool isIndexed)
        {
            Mesh3D geometry;

            if (isIndexed)
            {

            }
            else
            {
                geometry.Append({  0.525731f,          0,  0.850651f }); // 1
                geometry.Append({          0,  0.850651f,  0.525731f }); // 4
                geometry.Append({ -0.525731f,          0,  0.850651f }); // 0

                geometry.Append({          0,  0.850651f,  0.525731f }); // 4
                geometry.Append({ -0.850651f,  0.525731f,          0 }); // 9
                geometry.Append({ -0.525731f,          0,  0.850651f }); // 0

                geometry.Append({          0,  0.850651f,  0.525731f }); // 4
                geometry.Append({          0,  0.850651f, -0.525731f }); // 5
                geometry.Append({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Append({  0.850651f,  0.525731f,          0 }); // 8
                geometry.Append({          0,  0.850651f, -0.525731f }); // 5
                geometry.Append({          0,  0.850651f,  0.525731f }); // 4

                geometry.Append({  0.525731f,          0,  0.850651f }); // 1
                geometry.Append({  0.850651f,  0.525731f,          0 }); // 8
                geometry.Append({          0,  0.850651f,  0.525731f }); // 4

                geometry.Append({  0.525731f,          0,  0.850651f }); // 1
                geometry.Append({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Append({  0.850651f,  0.525731f,          0 }); // 8

                geometry.Append({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Append({  0.525731f,          0, -0.850651f }); // 3
                geometry.Append({  0.850651f,  0.525731f,          0 }); // 8

                geometry.Append({  0.850651f,  0.525731f,          0 }); // 8
                geometry.Append({  0.525731f,          0, -0.850651f }); // 3
                geometry.Append({          0,  0.850651f, -0.525731f }); // 5

                geometry.Append({  0.525731f,          0, -0.850651f }); // 3
                geometry.Append({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Append({          0,  0.850651f, -0.525731f }); // 5

                geometry.Append({  0.525731f,          0, -0.850651f }); // 3
                geometry.Append({          0, -0.850651f, -0.525731f }); // 7
                geometry.Append({ -0.525731f,          0, -0.850651f }); // 2

                geometry.Append({  0.525731f,          0, -0.850651f }); // 3
                geometry.Append({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Append({          0, -0.850651f, -0.525731f }); // 7

                geometry.Append({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Append({          0, -0.850651f,  0.525731f }); // 6
                geometry.Append({          0, -0.850651f, -0.525731f }); // 7

                geometry.Append({          0, -0.850651f,  0.525731f }); // 6
                geometry.Append({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Append({          0, -0.850651f, -0.525731f }); // 7

                geometry.Append({          0, -0.850651f,  0.525731f }); // 6
                geometry.Append({ -0.525731f,          0,  0.850651f }); // 0
                geometry.Append({ -0.850651f, -0.525731f,          0 }); // 11

                geometry.Append({          0, -0.850651f,  0.525731f }); // 6
                geometry.Append({  0.525731f,          0,  0.850651f }); // 1
                geometry.Append({ -0.525731f,          0,  0.850651f }); // 0

                geometry.Append({  0.850651f, -0.525731f,          0 }); // 10
                geometry.Append({  0.525731f,          0,  0.850651f }); // 1
                geometry.Append({          0, -0.850651f,  0.525731f }); // 6

                geometry.Append({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Append({ -0.525731f,          0,  0.850651f }); // 0
                geometry.Append({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Append({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Append({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Append({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Append({          0,  0.850651f, -0.525731f }); // 5
                geometry.Append({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Append({ -0.850651f,  0.525731f,          0 }); // 9

                geometry.Append({ -0.850651f, -0.525731f,          0 }); // 11
                geometry.Append({ -0.525731f,          0, -0.850651f }); // 2
                geometry.Append({          0, -0.850651f, -0.525731f }); // 7
            }

            geometry.CalculateNormals();
            return geometry;
        }
        Mesh3D Mesh3D::Line()
        {
            Mesh3D geometry;
            geometry.Topology(PointTopologies::Lines);
            geometry.Append({ -0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            geometry.Append({  0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            return geometry;
        }
        Mesh3D Mesh3D::Point()
        {
            Mesh3D geometry;
            geometry.Topology(PointTopologies::Points);
            geometry.Append({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            return geometry;
        }
        Mesh3D Mesh3D::Quad(bool isIndexed)
        {
            Mesh3D geometry;

            if (isIndexed)
            {
                Vector<uint> indices =
                {
                    0, 1, 2,
                    2, 1, 3,
                };

                geometry.Append(indices);

                geometry.Append({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
            }
            else
            {
                geometry.Append({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
                geometry.Append({  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
                geometry.Append({  0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
            }

            return geometry;
        }
        Mesh3D Mesh3D::Sphere(uint n)
        {
            Mesh3D geometry = Mesh3D::Icosahedron();
            geometry.Tessellate(n);

            auto& vertices = geometry.Vertices;
            for (uint a = 0; a < vertices.Count(); a++)
                vertices(a) = Vertex
                (
                    vertices(a).Position.Normalize(),
                    vertices(a).Position,
                    Vector2::Zero
                );

            return geometry;
        }
        Mesh3D Mesh3D::Triangle()
        {
            Mesh3D geometry;
            geometry.Append({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            geometry.Append({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
            geometry.Append({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
            return geometry;
        }

    }
}