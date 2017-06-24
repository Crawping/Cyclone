/* CHANGELOG
 * Written by Josh Grooms on 20170402
 */

#pragma once
#include "Collections/ArrayList.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/Vertex.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Mesh3D: public Geometry3D
        {
            public:

                /** STATIC CONSTRUCTORS **/
                /// <summary> Constructs a cube with unit dimensions spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
                /// <param name="isIndexed"> Indicates whether the vertices of the cube should be indexed or shared. </param>
                /// <remarks> The vertices of this cube are wound counter-clockwise and are shared only if indexed. </remarks>
                OpenGLAPI static Mesh3D Cube(bool isIndexed = false);
                /// <summary> Constructs a cylinder with unit radius and height centered on the origin (0, 0, 0). </summary>
                /// <returns> A triangle mesh that forms a cylinder in 3D space. </returns>
                /// <param name="nfaces">
                ///     The desired number of quad faces that make up the cylinder.
                ///     <para> </para>
                ///     This number cannot be less than 3, as the cylinder would then be degenerate.
                /// </param>
                /// <remarks> The vertices of this cylinder are not shared and are wound counter-clockwise. </remarks>
                OpenGLAPI static Mesh3D Cylinder(uint nfaces, bool isIndexed = false);
                /// <summary> Constructs a regular icosahedron with a unit radius centered on the origin (0, 0, 0). </summary>
                /// <returns> A triangle mesh that forms a regular icosahedron in 3D space. </returns>
                /// <remarks> The vertices of this icosahedron are not shared and are wound counter-clockwise. </remarks>
                OpenGLAPI static Mesh3D Icosahedron(bool isIndexed = false);
                /// <summary> Constructs a line with unit length spanning the coordinates (-0.5, 0, 0) to (0.5, 0, 0). </summary>
                OpenGLAPI static Mesh3D Line();
                /// <summary> Constructs a single point in three dimensional space at the coordinates (0, 0, 0). </summary>
                OpenGLAPI static Mesh3D Point();
                /// <summary> Constructs a unit quad in the XY plane spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
                /// <remarks> The vertices of this quad are wound counter-clockwise and are shared only if indexed. </remarks>
                /// <param name="isIndexed"> Indicates whether the vertices of the quad should be indexed or shared. </param>
                OpenGLAPI static Mesh3D Quad(bool isIndexed = false);
                /// <summary> Constructs a sphere with unit radius centered on the origin (0, 0, 0). </summary>
                /// <returns> A triangle mesh that forms a sphere in 3D space. </returns>
                /// <param name="n">
                ///     The number of times the vertices of a regular icosahedron are tessellated to approximate the sphere.
                /// </param>
                OpenGLAPI static Mesh3D Sphere(uint n, bool isIndexed = true);
                /// <summary> Constructs a right-triangle in the xy-plane whose hypotenuse spans the coordinates (1, 0, 0) to (0, 1, 0). </summary>
                /// <remarks> The vertices of this triangle are wound counter-clockwise. </remarks>
                OpenGLAPI static Mesh3D Triangle();



                /** UTILITIES **/
                /// <summary> Estimates the normal vectors for a list of non-indexed triangles in model space. </summary>
                OpenGLAPI void CalculateNormals();

                OpenGLAPI bool Intersects(const LineSegment3D& line) const override;
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
                OpenGLAPI void Tessellate(uint n);
                /// <summary> Reconstructs the full set of mapping, normal, and point data for an indexed mesh. </summary>
                /// <remarks>
                ///     When called on any indexed mesh geometry, this method permanently removes the use indices and 
                ///     decompresses all internal data stores.
                /// </remarks>
                OpenGLAPI void Unindex();

            private:

                mutable bool        _needsUpdate;
                ArrayList<Vertex>   _vertices;

        };
    }
}
