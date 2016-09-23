/* CHANGELOG
 * Written by Josh Grooms on 20151004
 */

#pragma once
#include "Geometry/Vertex.h"
#include "GL/OpenGLAPI.h"
#include "Collections/Vector.h"
#include "Math/Array.h"



namespace Cyclone
{
    namespace OpenGL
    {
        namespace Geometry3D
        {

            /** PRIMITIVE GENERATORS **/
            /// <summary> A cube with unit dimensions spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
            /// <returns> An array of standard vertices that define a cube in 3D space. </returns>
            /// <remarks> The vertices of this cube are not shared and are wound counter-clockwise. </remarks>
            OpenGLAPI Vector<Vertex::Standard> Cube();
            /// <summary> A cube with unit dimensions spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
            /// <returns> An array of standard vertices and indices that define a cube in 3D space. </returns>
            /// <param name="indices">
            ///     A reference to an array of 36 unsigned integers representing the order in which vertices will be rendered.
            ///     <para> </para>
            ///     This array must contain space for 36 elements, all of which will be overwritten during a call to this function.
            /// </param>
            /// <remarks> The vertices of this cube are shared according </remarks>
            OpenGLAPI Vector<Vertex::Standard> Cube(Vector<uint>& indices);
            /// <summary> A cylinder with unit radius and height centered on the origin (0, 0, 0). </summary>
            /// <returns> An array of standard vertices that define a cylinder in 3D space. </returns>
            /// <param name="nfaces"> 
            ///     The desired number of quad faces that make up the cylinder.
            ///     <para> </para>
            ///     This number cannot be less than 3, as the cylinder would then be degenerate.
            /// <param>
            /// <remarks> The vertices of this cylinder are not shared and are wound counter-clockwise. </remarks>
            OpenGLAPI Vector<Vertex::Standard> Cylinder(uint nfaces);
            /// <summary> A regular icosahedron with a unit radius centered on the origin (0, 0, 0). </summary>
            /// <returns> An array of standard vertices that define a regular icosahedron in 3D space. </returns>
            /// <remarks> The vertices of this icosahedron are not shared and are wound counter-clockwise. </remarks>
            OpenGLAPI Vector<Vertex::Standard> Icosahedron();
            /// <summary> A line with unit length spanning the coordinates (-0.5, 0, 0) to (0.5, 0, 0). </summary>
            OpenGLAPI Vector<Vertex::Standard> Line();
            /// <summary> A single point in three dimensional space at the coordinates (0, 0, 0). </summary>
            OpenGLAPI Vector<Vertex::Standard> Point();
	        /// <summary> A unit quad in the XY plane spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
	        /// <remarks> The vertices of this quad are not shared and are wound counter-clockwise. </remarks>
            OpenGLAPI Vector<Vertex::Standard> Quad();
            /// <summary> A sphere with unit radius centered on the origin (0, 0, 0). </summary>
            /// <returns> An array of standard vertices that define a sphere in 3D space. </returns>
            /// <param name="ntessellations"> 
            ///     The number of times the vertices of a regular icosahedron are tessellated to approximate the sphere.
            /// </param>
            OpenGLAPI Vector<Vertex::Standard> Sphere(uint ntessellations);
            /// <summary> A right-triangle in the XY plane whose hypotenuse spans the coordinates (1, 0, 0) to (0, 1, 0). </summary>
            /// <returns> An array of standard vertices that define a triangle in 3D space. </returns>
            /// <remarks> The vertices of this triangle are wound counter-clockwise. </remarks>
            OpenGLAPI Vector<Vertex::Standard> Triangle();



            /** VERTEX UTILITIES **/
            /// <summary> Estimates the normal vectors for a list of non-indexed triangles in model space. </summary>
            OpenGLAPI void CalculateNormals(Vector<Vertex::Standard>& vertices);
            /// <summary> Rotates vertex positions and normal vectors by a specified amount. </summary>
            OpenGLAPI void Rotate(Vector<Vertex::Standard>& vertices, const Vector3& rotation);
            /// <summary> Scales vertex positions to make geometry appear larger in model space. </summary>
            OpenGLAPI void Scale(Vector<Vertex::Standard>& vertices, const Vector3& scaling);
            /// <summary> Divides inputted triangles into smaller ones with unshared vertices. </summary>
            /// <returns> 
            ///     An array of standard vertices defining the same geometry as the input, but with an increased triangle count. 
            /// </returns>
            /// <param name="vertices"> An array of unshared vertices that define the triangles to be tessellated. </param>
            /// <param name="n"> 
            ///     The number of times tessellation will be recursively performed on the inputted gometry.
            ///     <para> </para>
            ///     Note that each tessellation step returns 12 times the number of inputted vertices.
            /// </param>
            OpenGLAPI Vector<Vertex::Standard> Tessellate(Vector<Vertex::Standard> vertices, uint n);
            /// <summary> Translates vertex positions to move geometry in model space. </summary>
            OpenGLAPI void Translate(Vector<Vertex::Standard>& vertices, const Vector3& translation);

        }
    }
}
