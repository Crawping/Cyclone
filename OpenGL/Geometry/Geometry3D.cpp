#include "Constants.h"
#include "Utilities.h"
#include "Geometry/Geometry3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    using namespace Utilities;



    namespace OpenGL
    {

        /** PRIMITIVE GENERATORS **/
        Vector<Vertex::Standard> Geometry3D::Cube()
        {
            return
            {
                // Front
                Vertex::Standard(-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f),

                Vertex::Standard(-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f),

                // Top
                Vertex::Standard(-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f),

                Vertex::Standard(-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f),

                // Bottom
                Vertex::Standard(-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f),

                Vertex::Standard(-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f),

                // Left
                Vertex::Standard(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard(-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f),

                Vertex::Standard(-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard(-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f),

                // Right
                Vertex::Standard( 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f),

                Vertex::Standard( 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f),

                // Back
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f),
                Vertex::Standard(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f),

                Vertex::Standard( 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f),
                Vertex::Standard(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f),
            };
        }
        Vector<Vertex::Standard> Geometry3D::Cube(Vector<uint>& indices)
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
                Vertex::Standard(-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f),

                // Top
                Vertex::Standard(-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f),

                // Bottom
                Vertex::Standard(-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f),

                // Left
                Vertex::Standard(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard(-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard(-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f),

                // Right
                Vertex::Standard( 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f),

                // Back
                Vertex::Standard( 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f),
                Vertex::Standard(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f),
                Vertex::Standard(-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f),
            };
        }
        Vector<Vertex::Standard> Geometry3D::Cylinder(uint nfaces)
        {
            nfaces = max(3, nfaces);

            Vector<Vertex::Standard> vertices = Vector<Vertex::Standard>(6 * nfaces);
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

                vertices(a * 6)     = Vertex::Standard(x1, -0.5f, z1, x1, 0.0f, z1, 0.0f, 0.0f);
                vertices(a * 6 + 1) = Vertex::Standard(x2, -0.5f, z2, x2, 0.0f, z2, 0.0f, 0.0f);
                vertices(a * 6 + 2) = Vertex::Standard(x1,  0.5f, z1, x1, 0.0f, z1, 0.0f, 0.0f);
                vertices(a * 6 + 3) = Vertex::Standard(x1,  0.5f, z1, x1, 0.0f, z1, 0.0f, 0.0f);
                vertices(a * 6 + 4) = Vertex::Standard(x2, -0.5f, z2, x2, 0.0f, z2, 0.0f, 0.0f);
                vertices(a * 6 + 5) = Vertex::Standard(x2,  0.5f, z2, x2, 0.0f, z2, 0.0f, 0.0f);
            }

            return vertices;
        }
        Vector<Vertex::Standard> Geometry3D::Icosahedron()
        {
            Vector<Vertex::Standard> icosahedron =
            {
				Vertex::Standard( 0.525731f,			0,  0.850651f), // 1
				Vertex::Standard(			0,  0.850651f,  0.525731f), // 4
				Vertex::Standard(-0.525731f,			0,  0.850651f), // 0

				Vertex::Standard(		  0,  0.850651f,  0.525731f), // 4
				Vertex::Standard(-0.850651f,  0.525731f,	      0), // 9
				Vertex::Standard(-0.525731f,	      0,  0.850651f),	// 0

				Vertex::Standard(		  0,  0.850651f,  0.525731f), // 4
				Vertex::Standard(         0,  0.850651f, -0.525731f), // 5
				Vertex::Standard(-0.850651f,  0.525731f,			0), // 9

				Vertex::Standard( 0.850651f,    0.525731f,			0), // 8
				Vertex::Standard(         0,    0.850651f, -0.525731f), // 5
				Vertex::Standard(         0,    0.850651f,  0.525731f), // 4

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

            Geometry3D::CalculateNormals(icosahedron);
            return icosahedron;
        }
        Vector<Vertex::Standard> Geometry3D::Line()
        {
            return
            {
                Vertex::Standard(-0.5f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, 0.0f, 0.0f),
            };
        }
        Vector<Vertex::Standard> Geometry3D::Point()
        {
            return { Vertex::Standard(0.0f, 0.0f, 0.0f) };
        }
        Vector<Vertex::Standard> Geometry3D::Quad()
        {
            return
            {
                Vertex::Standard(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard( 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard( 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard( 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            };
        }
        Vector<Vertex::Standard> Geometry3D::Sphere(uint n)
        {
            Vector<Vertex::Standard> sphere = Geometry3D::Tessellate(Geometry3D::Icosahedron(), n);
            for (uint a = 0; a < sphere.Count(); a++)
            {
                sphere(a).Position.Normalize();
                sphere(a).Normal = sphere(a).Position;
            }
            return sphere;
        }
        Vector<Vertex::Standard> Geometry3D::Triangle()
        {
            return
            {
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            };
        }



        /** VERTEX UTILITIES **/
        void Geometry3D::CalculateNormals(Vector<Vertex::Standard>& vertices)
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
        void Geometry3D::Rotate(Vector<Vertex::Standard>& vertices, const Vector3& rotation)
        {
            Transform r = Transform::Rotation(rotation);
            for (uint a = 0; a < vertices.Count(); a++)
                vertices(a).Position = Vector3(r * Vector4(vertices(a).Position, 1.0f));
        }
        void Geometry3D::Scale(Vector<Vertex::Standard>& vertices, const Vector3& scaling)
        {
            for (uint a = 0; a < vertices.Count(); a++)
                vertices(a).Position *= scaling;
        }
        Vector<Vertex::Standard> Geometry3D::Tessellate(Vector<Vertex::Standard> vertices, uint n)
        {
            if (n > 1)
            vertices = Geometry3D::Tessellate(vertices, n - 1);

            uint nvertices = vertices.Count() * 12;
            Vector<Vertex::Standard> result = Vector<Vertex::Standard>(nvertices);

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
        void Geometry3D::Translate(Vector<Vertex::Standard>& vertices, const Vector3& translation)
        {
            for (uint a = 0; a < vertices.Count(); a++)
                vertices(a).Position += translation;
        }

    }
}
