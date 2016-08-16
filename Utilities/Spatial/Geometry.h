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

            /** PRIMITIVES **/
            /// <summary> A cube with unit dimensions spanning the coordinates (0, 0, 0) to (1, 1, 1). </summary>
            /// <remarks> The vertices of this cube are not shared and are wound counter-clockwise. </remarks>
            UtilitiesAPI Array<Vertex> Cube();
            /// <summary> A cube with unit dimensions spanning the coordinates (0, 0, 0) to (1, 1, 1). </summary>
            /// <param name="indices"> 
            ///     A reference to an array of 36 unsigned integers representing the order in which vertices will be rendered.
            ///     <para> </para>
            ///     This array must contain space for 36 elements, all of which will be overwritten during a call to this function.
            /// </param>
            /// <remarks> The vertices of this cube are shared according </remarks>
            UtilitiesAPI Array<Vertex> Cube(Array<uint>& indices);
            /// <summary> A regular icosahedron with a unit radius centered on the origin (0, 0, 0). </summary>
            /// <remarks> The vertices of this icosahedron are not shared and are wound counter-clockwise. </remarks>
            UtilitiesAPI Array<Vertex> Icosahedron();
            /// <summary> A single point in three dimensional space at the coordinates (0, 0, 0). </summary>
            UtilitiesAPI Array<Vertex> Point();
	        /// <summary> A unit quad in the XY plane spanning the coordinates (0, 0, 0) to (1, 1, 0). </summary>
	        /// <remarks> The vertices of this quad are not shared and are wound counter-clockwise. </remarks>
            UtilitiesAPI Array<Vertex> Quad();
            /// <summary> A right-triangle in the XY plane whose hypotenuse spans the coordinates (1, 0, 0) to (0, 1, 0). </summary>
            /// <remarks> The vertices of this triangle are wound counter-clockwise. </remarks>
            UtilitiesAPI Array<Vertex> Triangle();

        }
    }
}
