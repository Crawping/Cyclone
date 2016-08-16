
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

        Array<Vertex> Geometry::Cube(Array<uint>& indices)
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
                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f),

                // Top
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f),

                // Bottom
                Vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 1.0f),

                // Left
                Vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex(0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex(0.0f, 1.0f, 0.0f, 1.0f, 1.0f),

                // Right
                Vertex(1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f),

                // Back
                Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex(0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
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