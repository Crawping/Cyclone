#include "Geometry/Geometry.h"


namespace Cyclone
{
    namespace OpenGL
    {
        
        Array<Vertex::Standard> Geometry::Cube()
        {
            return
            {
                // Front
                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),

                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),

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
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),

                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
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
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 1.0f, 1.0f),

                // Top
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                      
                // Bottom
                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
                      
                // Left
                Vertex::Standard(0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
                      
                // Right
                Vertex::Standard(1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                      
                // Back
                Vertex::Standard(1.0f, 0.0f, 1.0f, 0.0f, 0.0f),
                Vertex::Standard(0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            };
        }

        Array<Vertex::Standard> Geometry::Icosahedron()
        {
            return
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
        }

        Array<Vertex::Standard> Geometry::Point()
        {
            return { Vertex::Standard() };
        }

        Array<Vertex::Standard> Geometry::Quad()
        {
            return
            {
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
            };
        }

        Array<Vertex::Standard> Geometry::Triangle()
        {
            return
            {
                Vertex::Standard(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex::Standard(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex::Standard(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            };
        }

    }
}