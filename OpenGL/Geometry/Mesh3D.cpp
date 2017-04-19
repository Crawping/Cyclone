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
                vertices(a) = Vertex( points(a), normals(a), mapping(a) );

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
            auto newNormals = Vector<Vector3>(pts.Count());

            if (IsIndexed())
                for (uint a = 0; a < pts.Count(); a++)
                    newNormals(a) = pts(a).Normalize();
            else
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
            else if (n > 1)     Tessellate(n - 1);

            Vector<Vertex> vertices(Vertices());

            if (IsIndexed())
            {
                Vector<uint> indices(Indices());
                Vector<uint> newIndices(indices.Count() * 4);
                Vector<Vertex> newVertices(indices.Count() * 2);

                uint idxIndex = 0, idxVertex = 0;
                for (uint a = 0; a < indices.Count(); a += 3)
                {
                    uint idx1 = indices(a), idx2 = indices(a + 1), idx3 = indices(a + 2);
                    Vertex v1 = vertices(idx1), v2 = vertices(idx2), v3 = vertices(idx3);
                    Vertex m1 = midpoint(v1, v2), m2 = midpoint(v1, v3), m3 = midpoint(v2, v3);

                    newIndices(idxIndex)        = idxVertex;
                    newIndices(idxIndex + 1)    = idxVertex + 1;
                    newIndices(idxIndex + 2)    = idxVertex + 2;

                    newIndices(idxIndex + 3)    = idxVertex + 2;
                    newIndices(idxIndex + 4)    = idxVertex + 1;
                    newIndices(idxIndex + 5)    = idxVertex + 3;

                    newIndices(idxIndex + 6)    = idxVertex + 3;
                    newIndices(idxIndex + 7)    = idxVertex + 1;
                    newIndices(idxIndex + 8)    = idxVertex + 4;

                    newIndices(idxIndex + 9)    = idxVertex + 2;
                    newIndices(idxIndex + 10)   = idxVertex + 3;
                    newIndices(idxIndex + 11)   = idxVertex + 5;

                    newVertices(idxVertex)      = v1;
                    newVertices(idxVertex + 1)  = m1;
                    newVertices(idxVertex + 2)  = m2;
                    newVertices(idxVertex + 3)  = m3;
                    newVertices(idxVertex + 4)  = v2;
                    newVertices(idxVertex + 5)  = v3;

                    idxIndex += 12;
                    idxVertex += 6;
                }

                Indices(newIndices);
                Vertices(newVertices);
            }
            else
            {
                uint idx = 0;
                Vector<Vertex> newVertices(vertices.Count() * 4);
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



        /** PROTECTED UTILITIES **/
        void Mesh3D::Append(uint index)
        {

        }
        void Mesh3D::Append(const Vertex& vertex)
        {

        }
        void Mesh3D::Append(const ICollection<uint>& indices)
        {

        }
        void Mesh3D::Append(const ICollection<Vertex>& vertices)
        {

        }
        void Mesh3D::Append(const Vector3& position, const Vector3& normal, const Vector3& mapping)
        {

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

            Vector<Vertex> vertices(24);

            // Front
            vertices(0)  = Vertex({ -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f, 0.0f }); // 0
            vertices(1)  = Vertex({  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f, 0.0f }); // 1
            vertices(2)  = Vertex({ -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f, 0.0f }); // 2
            vertices(3)  = Vertex({  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f, 0.0f }); // 3

            // Top
            vertices(4)  = Vertex({ -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
            vertices(5)  = Vertex({  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
            vertices(6)  = Vertex({ -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
            vertices(7)  = Vertex({  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

            // Bottom
            vertices(8)  = Vertex({ -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
            vertices(9)  = Vertex({  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
            vertices(10) = Vertex({ -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
            vertices(11) = Vertex({  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

            // Left
            vertices(12) = Vertex({ -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
            vertices(13) = Vertex({ -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
            vertices(14) = Vertex({ -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
            vertices(15) = Vertex({ -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

            // Right
            vertices(16) = Vertex({  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 0.0f });
            vertices(17) = Vertex({  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 0.0f });
            vertices(18) = Vertex({  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f });
            vertices(19) = Vertex({  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f, 0.0f });

            // Back
            vertices(20) = Vertex({  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f });
            vertices(21) = Vertex({ -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f });
            vertices(22) = Vertex({  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
            vertices(23) = Vertex({ -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f });

            geometry.Indices(indices);
            geometry.Vertices(vertices);

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
                Vector<Vertex> vertices(nfaces * 6);

                float angleStep = Constants::TwoPi / nfaces;
                float hAngleStep = angleStep / 2.0f;

                uint idx = 0;
                for (int a = 0; a < nfaces; a++)
                {
                    float ctAngle = angleStep * a;
                    float hAngle = ctAngle * hAngleStep;
                    float ntAngle = angleStep * (a + 1);

                    float x1 =  cosf(ctAngle);
                    float z1 = -sinf(ctAngle);
                    float x2 =  cosf(ntAngle);
                    float z2 = -sinf(ntAngle);

                    vertices(idx++) = Vertex({ x1, -0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    vertices(idx++) = Vertex({ x2, -0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                    vertices(idx++) = Vertex({ x1,  0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    vertices(idx++) = Vertex({ x1,  0.5f, z1 }, { x1, 0.0f, z1 }, { 0.0f, 0.0f, 0.0f });
                    vertices(idx++) = Vertex({ x2, -0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                    vertices(idx++) = Vertex({ x2,  0.5f, z2 }, { x2, 0.0f, z2 }, { 0.0f, 0.0f, 0.0f });
                }

                geometry.Vertices(vertices);
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

            Vector<Vector3> points =
            {
                { -0.525731f,          0,  0.850651f }, // 0
                {  0.525731f,          0,  0.850651f }, // 1
                { -0.525731f,          0, -0.850651f }, // 2
                {  0.525731f,          0, -0.850651f }, // 3
                {          0,  0.850651f,  0.525731f }, // 4
                {          0,  0.850651f, -0.525731f }, // 5
                {          0, -0.850651f,  0.525731f }, // 6
                {          0, -0.850651f, -0.525731f }, // 7
                {  0.850651f,  0.525731f,          0 }, // 8
                { -0.850651f,  0.525731f,          0 }, // 9
                {  0.850651f, -0.525731f,          0 }, // 10
                { -0.850651f, -0.525731f,          0 }, // 11
            };

            geometry.Indices(indices);
            geometry.Points(points);

            if (!isIndexed)
                geometry.Unindex();

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
            Vector<Vertex, 1> vertices( Vertex({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }) );
            geometry.Topology(PointTopologies::Points);
            geometry.Vertices(vertices);
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

            Vector<Vertex> vertices(4);
            vertices(0) = Vertex({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
            vertices(1) = Vertex({  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
            vertices(2) = Vertex({ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            vertices(3) = Vertex({  0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });

            geometry.Indices(indices);
            geometry.Vertices(vertices);

            if (!isIndexed) geometry.Unindex();
            return geometry;
        }
        Mesh3D Mesh3D::Sphere(uint n, bool isIndexed)
        {
            Mesh3D geometry = Mesh3D::Icosahedron(isIndexed);
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
