
#include "Spatial/Geometry.h"


namespace Cyclone
{
    namespace Utilities
    {
        
        Array<Vertex> Geometry::Cube()
        {
            return
            {
                // Front
                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),

                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f),

                // Top
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),

                Vertex(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f),

                // Bottom
                Vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f),

                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                Vertex(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 1.0f),

                // Left
                Vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex(0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),

                Vertex(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex(0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 0.0f, 1.0f, 1.0f),

                // Right
                Vertex(1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 0.0f, 0.0f, 1.0f),

                Vertex(1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f),

                // Back
                Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex(0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

                Vertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex(0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            };
        }

        Array<Vertex> Geometry::Icosahedron()
        {
            return
            {
				Vertex( 0.525731f,			0,  0.850651f), // 1
				Vertex(-0.525731f,			0,  0.850651f), // 0
				Vertex(			0,  0.850651f,  0.525731f), // 4
			
				Vertex(			0,  0.850651f,  0.525731f), // 4
				Vertex(-0.525731f,			0,  0.850651f),	// 0
				Vertex(-0.850651f,  0.525731f,			0), // 9

				Vertex(			0,  0.850651f,  0.525731f), // 4
				Vertex(-0.850651f,  0.525731f,			0), // 9
				Vertex(			0,  0.850651f, -0.525731f), // 5

				Vertex( 0.850651f,  0.525731f,			0), // 8
				Vertex(			0,  0.850651f,  0.525731f), // 4
				Vertex(			0,  0.850651f, -0.525731f), // 5

				Vertex( 0.525731f,			0,  0.850651f), // 1				
				Vertex(			0,  0.850651f,  0.525731f), // 4
				Vertex( 0.850651f,  0.525731f,			0), // 8

				Vertex( 0.525731f,			0,  0.850651f), // 1
				Vertex( 0.850651f,  0.525731f,			0), // 8
				Vertex( 0.850651f, -0.525731f,			0), // 10

				Vertex( 0.850651f, -0.525731f,			0), // 10
				Vertex( 0.850651f,  0.525731f,			0), // 8
				Vertex( 0.525731f,			0, -0.850651f), // 3

				Vertex( 0.850651f,  0.525731f,			0), // 8
				Vertex(			0,  0.850651f, -0.525731f), // 5
				Vertex( 0.525731f,			0, -0.850651f), // 3

				Vertex( 0.525731f,			0, -0.850651f), // 3
				Vertex(			0,  0.850651f, -0.525731f), // 5
				Vertex(-0.525731f,			0, -0.850651f), // 2

				Vertex( 0.525731f,			0, -0.850651f), // 3
				Vertex(-0.525731f,			0, -0.850651f), // 2
				Vertex(			0, -0.850651f, -0.525731f), // 7

				Vertex( 0.525731f,			0, -0.850651f), // 3
				Vertex(			0, -0.850651f, -0.525731f), // 7
				Vertex( 0.850651f, -0.525731f,			0), // 10

				Vertex( 0.850651f, -0.525731f,			0), // 10
				Vertex(			0, -0.850651f, -0.525731f), // 7
				Vertex(			0, -0.850651f,  0.525731f), // 6

				Vertex(			0, -0.850651f,  0.525731f), // 6
				Vertex(			0, -0.850651f, -0.525731f), // 7
				Vertex(-0.850651f, -0.525731f,			0), // 11

				Vertex(			0, -0.850651f,  0.525731f), // 6
				Vertex(-0.850651f, -0.525731f,			0), // 11
				Vertex(-0.525731f,			0,  0.850651f),	// 0

				Vertex(			0, -0.850651f,  0.525731f), // 6
				Vertex(-0.525731f,			0,  0.850651f),	// 0
				Vertex( 0.525731f,			0,  0.850651f), // 1

				Vertex( 0.850651f, -0.525731f,			0), // 10
				Vertex(			0, -0.850651f,  0.525731f), // 6
				Vertex( 0.525731f,			0,  0.850651f), // 1

				Vertex(-0.850651f, -0.525731f,			0), // 11
				Vertex(-0.850651f,  0.525731f,			0), // 9
				Vertex(-0.525731f,			0,  0.850651f),	// 0

				Vertex(-0.525731f,			0, -0.850651f), // 2
				Vertex(-0.850651f,  0.525731f,			0), // 9
				Vertex(-0.850651f, -0.525731f,			0), // 11

				Vertex(			0,  0.850651f, -0.525731f), // 5
				Vertex(-0.850651f,  0.525731f,			0), // 9
				Vertex(-0.525731f,			0, -0.850651f), // 2

				Vertex(-0.850651f, -0.525731f,			0), // 11
				Vertex(			0, -0.850651f, -0.525731f), // 7
				Vertex(-0.525731f,			0, -0.850651f), // 2
            };
        }

        Array<Vertex> Geometry::Point()
        {
            return { Vertex() };
        }

        Array<Vertex> Geometry::Quad()
        {
            return
            {
                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
            };
        }
        Array<Vertex> Geometry::Triangle()
        {
            return
            {
                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            };
        }

    }
}