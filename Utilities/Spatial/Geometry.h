/* CHANGELOG
 * Written by Josh Grooms on 20151004
 */

#pragma once
#include "UtilitiesAPI.h"
#include "Math/Array.h"
#include "Spatial/Vertex.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Geometry
        {
            const Array<Vertex> Cube =
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
            /// <summary> A single point in three dimensional space at the coordinates (0, 0, 0). </summary>
	        const Array<Vertex> Point = { Vertex() };
            /// <summary> A right-triangle in the XY plane whose hypotenuse spans the coordinates (1, 0, 0) to (0, 1, 0). </summary>
            /// <remarks> The vertices of this triangle are wound counter-clockwise. </remarks>
            const Array<Vertex> Triangle =
            {
                Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
                Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            };
	        /// <summary> A unit quad in the XY plane spanning the coordinates (0, 0, 0) to (1, 1, 0). </summary>
	        /// <remarks> The vertices of this quad are not shared and are wound counter-clockwise. </remarks>
	        const Array<Vertex> Quad =
	        {
		        Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		        Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		        Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		        Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		        Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		        Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	        };
        }
    }
}
