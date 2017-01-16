#include "Utilities.h"
#include "Geometry/Geometry3D.h"
#include "Math/Constants.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** HELPER FUNCTIONS**/
        constexpr Vector3 midpoint(const Vector3& u, const Vector3& v)
        {
            return (v - u) * 0.5f + u;
        }
        Vertex midpoint(const Vertex& u, const Vertex& v)
        {
            return Vertex
            (
                midpoint(u.Position, v.Position),
                midpoint(u.Normal, v.Normal),
                (Vector2)midpoint(u.UV, v.UV)
            );
        }



        /** PROPERTIES **/
        GeometryData Geometry3D::Data()             const
        {
            GeometryData data =
            {
                _bounds,
                _indices,
                Vector<Vector3>(Count()),
                Vector<Vector3>(Count()),
                Vector<Vector3>(Count()),
                _topology,
            };

            for (uint a = 0; a < Vertices.Count(); a++)
            {
                Vertex v = Vertices(a);
                data.Mapping(a) = v.UV;
                data.Normals(a) = v.Normal;
                data.Points(a) = v.Position;
            }

            return data;
        }
        Vector<uint> Geometry3D::Indices()          const
        {
            return _indices;
        }
        Vector<Vector3> Geometry3D::Mapping()       const
        {
            Vector<Vector3> mapping(Count());
            for (uint a = 0; a < Vertices.Count(); a++)
                mapping(a) = Vertices(a).UV;

            return mapping;
        }
        Vector<Vector3> Geometry3D::Normals()       const
        {
            Vector<Vector3> normals(Count());
            for (uint a = 0; a < Vertices.Count(); a++)
                normals(a) = Vertices(a).Normal;
            
            return normals;
        }
        Vector<Vector3> Geometry3D::Points()        const
        {
            Vector<Vector3> points(Count());
            for (uint a = 0; a < Vertices.Count(); a++)
                points(a) = Vertices(a).Position;

            return points;
        }

        Geometry3D& Geometry3D::Bounds(const Volume& value)
        {
            _bounds = value;
            return *this;
        }
        Geometry3D& Geometry3D::Data(const GeometryData& value)
        {
            Vector<Vertex> newVertices(value.Points.Count());
            for (uint a = 0; a < newVertices.Count(); a++)
                newVertices(a) = Vertex(value.Points(a), value.Normals(a), (Vector2)value.Mapping(a));

            Vertices = newVertices;
            return Bounds(value.Bounds)
                .Indices(value.Indices)
                .Topology(value.Topology);
        }
        Geometry3D& Geometry3D::Indices(const Vector<uint>& value)
        {
            _indices = value;
            return *this;
        }
        Geometry3D& Geometry3D::Topology(VertexTopologies value)
        {
            _topology = value;
            return *this;
        }



        /** UTILITIES **/
        void Geometry3D::Append(const Vertex& vertex)
        {
            Vertices.Append(vertex);
        }
        void Geometry3D::Append(const ICollection<Vertex>& vertices)
        {
            Vertices.Append(vertices);
        }
        void Geometry3D::CalculateNormals()
        {
            for (uint a = 0; a < Vertices.Count(); a += 3)
            {
                Vector3 diff1 = Vertices(a + 1).Position - Vertices(a).Position;
                Vector3 diff2 = Vertices(a + 2).Position - Vertices(a).Position;
                Vector3 diff3 = Vertices(a + 2).Position - Vertices(a + 1).Position;
   
                Vertices(a).Normal     = Math::Cross(diff1, diff2).Normalize();
                Vertices(a + 1).Normal = Math::Cross(diff3, -diff1).Normalize();
                Vertices(a + 2).Normal = Math::Cross(-diff2, -diff3).Normalize();
            }
        }
        void Geometry3D::Clear()
        {
            _indices.Clear();
            Vertices.Clear();
        }
        void Geometry3D::Tessellate(uint n)
        {

            if (n > 1)
                Geometry3D::Tessellate(n - 1);

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
        Geometry3D Geometry3D::Cube(bool isIndexed)
        {
            Geometry3D geometry;

            if (isIndexed)
            {
                geometry._indices =
                {
                     0,  1,  2,  2,  1,  3,
                     4,  5,  6,  6,  5,  7,
                     8,  9, 10, 10,  9, 11,
                    12, 13, 14, 14, 13, 15,
                    16, 17, 18, 18, 17, 19,
                    20, 21, 22, 22, 21, 23,
                };

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
        Geometry3D Geometry3D::Icosahedron(bool isIndexed)
        {
            Geometry3D geometry;

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
        Geometry3D Geometry3D::Line()
        {
            Geometry3D geometry;
            geometry.Topology(VertexTopologies::Lines);
            geometry.Append({ -0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            geometry.Append({  0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            return geometry;
        }
        Geometry3D Geometry3D::Point()
        {
            Geometry3D geometry;
            geometry.Topology(VertexTopologies::Points);
            geometry.Append({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            return geometry;
        }
        Geometry3D Geometry3D::Quad(bool isIndexed)
        {
            Geometry3D geometry;

            if (isIndexed)
            {
                geometry._indices =
                {
                    0, 1, 2,
                    2, 1, 3,
                };

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
        Geometry3D Geometry3D::Sphere(uint n)
        {
            Geometry3D geometry = Geometry3D::Icosahedron();
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
        Geometry3D Geometry3D::Triangle()
        {
            Geometry3D geometry;
            geometry.Append({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
            geometry.Append({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
            geometry.Append({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
            return geometry;
        }

    }
}
