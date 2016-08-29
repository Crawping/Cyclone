/* CHANGELOG
 * Written by Josh Grooms on 20151004
 */

#pragma once
#include "Geometry/Vertices.h"
#include "GL/OpenGLAPI.h"
#include "Math/Array.h"



namespace Cyclone
{
    namespace OpenGL
    {
        namespace Geometry
        {

            /** PRIMITIVES **/
            /// <summary> A cube with unit dimensions spanning the coordinates (0, 0, 0) to (1, 1, 1). </summary>
            /// <remarks> The vertices of this cube are not shared and are wound counter-clockwise. </remarks>
            OpenGLAPI Array<Vertex::Standard> Cube();
            /// <summary> A cube with unit dimensions spanning the coordinates (0, 0, 0) to (1, 1, 1). </summary>
            /// <param name="indices"> 
            ///     A reference to an array of 36 unsigned integers representing the order in which vertices will be rendered.
            ///     <para> </para>
            ///     This array must contain space for 36 elements, all of which will be overwritten during a call to this function.
            /// </param>
            /// <remarks> The vertices of this cube are shared according </remarks>
            OpenGLAPI Array<Vertex::Standard> Cube(Array<uint>& indices);
            /// <summary> A regular icosahedron with a unit radius centered on the origin (0, 0, 0). </summary>
            /// <remarks> The vertices of this icosahedron are not shared and are wound counter-clockwise. </remarks>
            OpenGLAPI Array<Vertex::Standard> Icosahedron();
            /// <summary> A single point in three dimensional space at the coordinates (0, 0, 0). </summary>
            OpenGLAPI Array<Vertex::Standard> Point();
	        /// <summary> A unit quad in the XY plane spanning the coordinates (0, 0, 0) to (1, 1, 0). </summary>
	        /// <remarks> The vertices of this quad are not shared and are wound counter-clockwise. </remarks>
            OpenGLAPI Array<Vertex::Standard> Quad();
            /// <summary> A right-triangle in the XY plane whose hypotenuse spans the coordinates (1, 0, 0) to (0, 1, 0). </summary>
            /// <remarks> The vertices of this triangle are wound counter-clockwise. </remarks>
            OpenGLAPI Array<Vertex::Standard> Triangle();

        }
    }
}
