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
            return (v + u) * 0.5f;
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



        /** PROPERTIES **/
        Vector<Vertex> Mesh3D::Vertices() const
        {
            Vector<Vector3> mapping(Mapping()), normals(Normals()), points(Points());
            Vector<Vertex> vertices(points.Count());
            for (uint a = 0; a < points.Count(); a++)
                vertices(a) = Vertex( points(a), normals(a), (Vector2)mapping(a) );

            return vertices;
        }

        Mesh3D& Mesh3D::Vertices(const ICollection<Vertex>& value)
        {
            uint count = value.Count();
            Vector<Vector3> mapping(count), normals(count), points(count);
            for (uint a = 0; a < count; a++)
            {
                Vertex vertex = value(a);
                mapping(a) = vertex.UV;
                normals(a) = vertex.Normal;
                points(a) = vertex.Position;
            }

            Mapping(mapping)
                .Normals(normals)
                .Points(points);

            return *this;
        }



        /** PUBLIC UTILITIES **/
        void Mesh3D::CalculateNormals()
        {
            auto pts = Points();
            auto nms = Normals();

            auto newNormals = Vector<Vector3>(Count());
            for (uint a = 0; a < pts.Count(); a += 3)
            {
                Vector3 diff1 = pts(a + 1) - pts(a);
                Vector3 diff2 = pts(a + 2) - pts(a);
                Vector3 diff3 = pts(a + 2) - pts(a + 1);

                newNormals(a) = Math::Cross(diff1, diff2).Normalize();
                newNormals(a + 1) = Math::Cross(diff3, -diff1).Normalize();
                newNormals(a + 2) = Math::Cross(-diff2, -diff3).Normalize();
            }

            Normals(newNormals);
        }
        void Mesh3D::Tessellate(uint n)
        {
            if (n == 0)         return;
            else if (n > 1)     Mesh3D::Tessellate(n - 1);

            uint idx = 0;
            uint newCount = Count() * 12;
            Vector<Vertex> vertices(Vertices()), newVertices(newCount);
            for (uint a = 0; a < vertices.Count(); a += 3)
            {
                Vertex v1 = vertices(a), v2 = vertices(a + 1), v3 = vertices(a + 2);
                Vertex m1 = midpoint(v1, v2), m2 = midpoint(v1, v3), m3 = midpoint(v2, v3);

                newVertices(idx++) = v1;
                newVertices(idx++) = m1;
                newVertices(idx++) = m2;

                newVertices(idx++) = m2;
                newVertices(idx++) = m1;
                newVertices(idx++) = m3;

                newVertices(idx++) = m3;
                newVertices(idx++) = m1;
                newVertices(idx++) = v2;

                newVertices(idx++) = m2;
                newVertices(idx++) = m3;
                newVertices(idx++) = v3;
            }

            Vertices(newVertices);
        }
        void Mesh3D::Unindex()
        {
            Vector<uint> indices(Indices());
            Vector<Vertex> vertices(Vertices()), newVertices(indices.Count());
            for (uint a = 0; a < indices.Count(); a++)
                newVertices(a) = vertices(indices(a));

            Indices(Vector<uint>());
            Vertices(newVertices);
        }


        /** GEOMETRY GENERATING FUNCTIONS **/
        Mesh3D Mesh3D::Cube(bool isIndexed)
        {
            Mesh3D geometry;

            Vector<uint> indices =
            {
                 0,  1,  2,  2,  1,  3,
                 4,  5,  6,  6,  5,  7,
                 8,  9, 10, 10,  9, 11,
                12, 13, 14, 14, 13, 15,
                16, 17, 18, 18, 17, 19,
                20, 21, 22, 22, 21, 23,
            };

            geometry.Indices(indices);

            // Front
            geometry.Append({ -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f, 0.0f }); // 0
            geometry.Append({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f }); // 1
            geometry.Append({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f }); // 2
            geometry.Append({  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f, 0.0f }); // 3

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

            if (!isIndexed); geometry.Unindex();
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

                    float x1 =  cosf(ctAngle);
                    float z1 = -sinf(ctAngle);
                    float x2 =  cosf(ntAngle);
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

            Vector<uint> indices =
            {
                 1,  4,  0,     4,  9,  0,     4,  5,  9,     8,  5,  4,     1,  8,  4,
                 1, 10,  8,    10,  3,  8,     8,  3,  5,     3,  2,  5,     3,  7,  2,
                 3, 10,  7,    10,  6,  7,     6, 11,  7,     6,  0, 11,     6,  1,  0,
                10,  1,  6,    11,  0,  9,     2, 11,  9,     5,  2,  9,    11,  2,  7,
            };

            geometry.Indices(indices);

            geometry.Append({ -0.525731f,          0,  0.850651f }); // 0
			geometry.Append({  0.525731f,          0,  0.850651f }); // 1
			geometry.Append({ -0.525731f,          0, -0.850651f }); // 2
			geometry.Append({  0.525731f,          0, -0.850651f }); // 3
			geometry.Append({          0,  0.850651f,  0.525731f }); // 4
			geometry.Append({          0,  0.850651f, -0.525731f }); // 5
			geometry.Append({          0, -0.850651f,  0.525731f }); // 6
			geometry.Append({          0, -0.850651f, -0.525731f }); // 7
			geometry.Append({  0.850651f,  0.525731f,          0 }); // 8
			geometry.Append({ -0.850651f,  0.525731f,          0 }); // 9
			geometry.Append({  0.850651f, -0.525731f,          0 }); // 10
            geometry.Append({ -0.850651f, -0.525731f,          0 }); // 11

            if (!isIndexed)
            {
                geometry.Unindex();
                geometry.CalculateNormals();
            }

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

            if (!isIndexed) geometry.Unindex();
            return geometry;
        }
        Mesh3D Mesh3D::Sphere(uint n)
        {
            Mesh3D geometry = Mesh3D::Icosahedron();
            geometry.Tessellate(n);

            Vector<Vector3> points(geometry.Points()), normals(geometry.Normals());
            for (uint a = 0; a < points.Count(); a++)
            {
                points(a).Normalize();
                normals(a) = points(a);
            }

            geometry.Points(points).Normals(normals);
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
