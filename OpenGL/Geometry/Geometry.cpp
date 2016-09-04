#include "Constants.h"
#include "Utilities.h"
#include "Geometry/Geometry.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    using namespace Utilities;



    namespace OpenGL
    {

        /** PRIMITIVE GENERATORS **/
        Array<Vertex::Standard> Geometry::Cube()
        {
            return
            {
                // Front
                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),

                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),

                // Top
                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),

                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),

                // Bottom
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),

                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),

                // Left
                Vertex::Standard(0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),

                Vertex::Standard(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),

                // Right
                Vertex::Standard(1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),

                Vertex::Standard(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),

                // Back
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),

                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
            };
        }
        Array<Vertex::Standard> Geometry::Cube(Array<uint>& indices)
        {
            indices =
            {
				0,	 1,	 2,	 2,	 1,	 3,
				4,	 5,	 6,	 6,	 5,	 7,
				8,	 9, 10, 10,  9, 11,
				12, 13, 14, 14, 13, 15,
				16, 17, 18, 18, 17, 19,
				20, 21, 22, 22, 21, 23,
            };

            return
            {
                // Front
                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),

                // Top
                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),

                // Bottom
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),

                // Left
                Vertex::Standard(0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),

                // Right
                Vertex::Standard(1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),

                // Back
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
            };
        }
        Array<Vertex::Standard> Geometry::Cylinder(uint nfaces)
        {
            Array<Vertex::Standard> vertices = Array<Vertex::Standard>(6 * nfaces);
            float angleStep = Constants::TwoPi / nfaces;
            //float angleStep = 360.0f / nfaces;
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

                float nx = cosf(hAngle);
                float nz = sinf(hAngle);

                vertices(a * 6)     = Vertex::Standard(x1, 0.0f, z1, nx, 0.0f, nz, 0.0f, 0.0f);
                vertices(a * 6 + 1) = Vertex::Standard(x2, 0.0f, z2, nx, 0.0f, nz, 0.0f, 0.0f);
                vertices(a * 6 + 2) = Vertex::Standard(x1, 1.0f, z1, nx, 0.0f, nz, 0.0f, 0.0f);
                vertices(a * 6 + 3) = Vertex::Standard(x1, 1.0f, z1, nx, 0.0f, nz, 0.0f, 0.0f);
                vertices(a * 6 + 4) = Vertex::Standard(x2, 0.0f, z2, nx, 0.0f, nz, 0.0f, 0.0f);
                vertices(a * 6 + 5) = Vertex::Standard(x2, 1.0f, z2, nx, 0.0f, nz, 0.0f, 0.0f);
            }

            return vertices;
        }
        Array<Vertex::Standard> Geometry::Icosahedron()
        {
            Array<Vertex::Standard> icosahedron =
            {
				Vertex::Standard( 0.525731f,			0,  0.850651f), // 1
				Vertex::Standard(			0,  0.850651f,  0.525731f), // 4
				Vertex::Standard(-0.525731f,			0,  0.850651f), // 0

				Vertex::Standard(			0,  0.850651f,  0.525731f), // 4
				Vertex::Standard(-0.850651f,  0.525731f,			0), // 9
				Vertex::Standard(-0.525731f,			0,  0.850651f),	// 0

				Vertex::Standard(			0,  0.850651f,  0.525731f), // 4
				Vertex::Standard(			0,  0.850651f, -0.525731f), // 5
				Vertex::Standard(-0.850651f,  0.525731f,			0), // 9

				Vertex::Standard( 0.850651f,  0.525731f,			0), // 8
				Vertex::Standard(			0,  0.850651f, -0.525731f), // 5
				Vertex::Standard(			0,  0.850651f,  0.525731f), // 4

				Vertex::Standard( 0.525731f,			0,  0.850651f), // 1
				Vertex::Standard( 0.850651f,  0.525731f,			0), // 8
				Vertex::Standard(			0,  0.850651f,  0.525731f), // 4

				Vertex::Standard( 0.525731f,			0,  0.850651f), // 1
				Vertex::Standard( 0.850651f, -0.525731f,			0), // 10
				Vertex::Standard( 0.850651f,  0.525731f,			0), // 8

				Vertex::Standard( 0.850651f, -0.525731f,			0), // 10
				Vertex::Standard( 0.525731f,			0, -0.850651f), // 3
				Vertex::Standard( 0.850651f,  0.525731f,			0), // 8

				Vertex::Standard( 0.850651f,  0.525731f,			0), // 8
				Vertex::Standard( 0.525731f,			0, -0.850651f), // 3
				Vertex::Standard(			0,  0.850651f, -0.525731f), // 5

				Vertex::Standard( 0.525731f,			0, -0.850651f), // 3
				Vertex::Standard(-0.525731f,			0, -0.850651f), // 2
				Vertex::Standard(			0,  0.850651f, -0.525731f), // 5

				Vertex::Standard( 0.525731f,			0, -0.850651f), // 3
				Vertex::Standard(			0, -0.850651f, -0.525731f), // 7
				Vertex::Standard(-0.525731f,			0, -0.850651f), // 2

				Vertex::Standard( 0.525731f,			0, -0.850651f), // 3
				Vertex::Standard( 0.850651f, -0.525731f,			0), // 10
				Vertex::Standard(			0, -0.850651f, -0.525731f), // 7

				Vertex::Standard( 0.850651f, -0.525731f,			0), // 10
				Vertex::Standard(			0, -0.850651f,  0.525731f), // 6
				Vertex::Standard(			0, -0.850651f, -0.525731f), // 7

				Vertex::Standard(			0, -0.850651f,  0.525731f), // 6
				Vertex::Standard(-0.850651f, -0.525731f,			0), // 11
				Vertex::Standard(			0, -0.850651f, -0.525731f), // 7

				Vertex::Standard(			0, -0.850651f,  0.525731f), // 6
				Vertex::Standard(-0.525731f,			0,  0.850651f),	// 0
				Vertex::Standard(-0.850651f, -0.525731f,			0), // 11

				Vertex::Standard(			0, -0.850651f,  0.525731f), // 6
				Vertex::Standard( 0.525731f,			0,  0.850651f), // 1
				Vertex::Standard(-0.525731f,			0,  0.850651f),	// 0

				Vertex::Standard( 0.850651f, -0.525731f,			0), // 10
				Vertex::Standard( 0.525731f,			0,  0.850651f), // 1
				Vertex::Standard(			0, -0.850651f,  0.525731f), // 6

				Vertex::Standard(-0.850651f, -0.525731f,			0), // 11
				Vertex::Standard(-0.525731f,			0,  0.850651f),	// 0
				Vertex::Standard(-0.850651f,  0.525731f,			0), // 9

				Vertex::Standard(-0.525731f,			0, -0.850651f), // 2
				Vertex::Standard(-0.850651f, -0.525731f,			0), // 11
				Vertex::Standard(-0.850651f,  0.525731f,			0), // 9

				Vertex::Standard(			0,  0.850651f, -0.525731f), // 5
				Vertex::Standard(-0.525731f,			0, -0.850651f), // 2
				Vertex::Standard(-0.850651f,  0.525731f,			0), // 9

				Vertex::Standard(-0.850651f, -0.525731f,			0), // 11
				Vertex::Standard(-0.525731f,			0, -0.850651f), // 2
				Vertex::Standard(			0, -0.850651f, -0.525731f), // 7
            };

            Geometry::CalculateNormals(icosahedron);
            return icosahedron;
        }
        Array<Vertex::Standard> Geometry::Line()
        {
            return
            {
                Vertex::Standard(0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f),
            };
        }
        Array<Vertex::Standard> Geometry::Point()
        {
            return { Vertex::Standard(0.0f, 0.0f, 0.0f) };
        }
        Array<Vertex::Standard> Geometry::Quad()
        {
            return
            {
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
            };
        }
        Array<Vertex::Standard> Geometry::Sphere(uint n)
        {
            Array<Vertex::Standard> sphere = Geometry::Tessellate(Geometry::Icosahedron(), n);
            for (uint a = 0; a < sphere.Count(); a++)
                sphere(a).Position.Normalize();

            Geometry::CalculateNormals(sphere);
            return sphere;
        }
        Array<Vertex::Standard> Geometry::Triangle()
        {
            return
            {
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            };
        }



        /** VERTEX UTILITIES **/
        void Geometry::CalculateNormals(Array<Vertex::Standard>& vertices)
        {
            for (uint a = 0; a < vertices.Count(); a += 3)
            {
                Vector3 diff1 = vertices(a + 1).Position - vertices(a).Position;
                Vector3 diff2 = vertices(a + 2).Position - vertices(a).Position;
                Vector3 diff3 = vertices(a + 2).Position - vertices(a + 1).Position;

                vertices(a).Normal      = Math::Cross(diff1, diff2).Normalize();
                vertices(a + 1).Normal  = Math::Cross(diff3, -diff1).Normalize();
                vertices(a + 2).Normal  = Math::Cross(-diff2, -diff3).Normalize();
            }
        }
        void Geometry::Rotate(Array<Vertex::Standard>& vertices, const Vector3& rotation)
        {
            Transform r = Transform::Rotation(rotation);
            for (uint a = 0; a < vertices.Count(); a++)
                vertices(a).Position = Vector3(r * Vector4(vertices(a).Position, 1.0f));
        }
        void Geometry::Scale(Array<Vertex::Standard>& vertices, const Vector3& scaling)
        {
            for (uint a = 0; a < vertices.Count(); a++)
                vertices(a).Position *= scaling;
        }
        Array<Vertex::Standard> Geometry::Tessellate(Array<Vertex::Standard> vertices, uint n)
        {
            if (n > 1)
            vertices = Geometry::Tessellate(vertices, n - 1);

            uint nvertices = vertices.Count() * 12;
            Array<Vertex::Standard> result = Array<Vertex::Standard>(nvertices);

            uint idx = 0;
            for (uint a = 0; a < vertices.Count(); a += 3)
            {
                Vector3 midpt1 = vertices(a).Position + ((vertices(a + 1).Position - vertices(a).Position) * 0.5f);
                Vector3 midpt2 = vertices(a).Position + ((vertices(a + 2).Position - vertices(a).Position) * 0.5f);
                Vector3 midpt3 = vertices(a + 1).Position + ((vertices(a + 2).Position - vertices(a + 1).Position) * 0.5f);

                result(idx++) = vertices(a);
                result(idx++) = Vertex::Standard(midpt1, Vector3::Zero, Vector2::Zero);
                result(idx++) = Vertex::Standard(midpt2, Vector3::Zero, Vector2::Zero);

                result(idx++) = Vertex::Standard(midpt1, Vector3::Zero, Vector2::Zero);
                result(idx++) = vertices(a + 1);
                result(idx++) = Vertex::Standard(midpt3, Vector3::Zero, Vector2::Zero);

                result(idx++) = Vertex::Standard(midpt2, Vector3::Zero, Vector2::Zero);
                result(idx++) = Vertex::Standard(midpt1, Vector3::Zero, Vector2::Zero);
                result(idx++) = Vertex::Standard(midpt3, Vector3::Zero, Vector2::Zero);

                result(idx++) = Vertex::Standard(midpt2, Vector3::Zero, Vector2::Zero);
                result(idx++) = Vertex::Standard(midpt3, Vector3::Zero, Vector2::Zero);
                result(idx++) = vertices(a + 2);
            }

            return result;
        }
        void Geometry::Translate(Array<Vertex::Standard>& vertices, const Vector3& translation)
        {
            for (uint a = 0; a < vertices.Count(); a++)
                vertices(a).Position += translation;
        }

    }
}
