/* CHANGELOG
 * Written by Josh Grooms on 20161031
 */

#pragma once
#include "Collections/List.h"
#include "Geometry/Vertex.h"
#include "Interfaces/IGeometric.h"
#include "Spatial/Transform.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {


        /// <summary> A class that holds and manages data related to 3D geometric shapes. </summary>
        class Geometry3D : public virtual IGeometric
        {
            public:

                /** GEOMETRIC PROPERTIES **/
                /// <summary> A rectangular prism that defines the bounding volume of the entity in 3D space. </summary>
                virtual const Volume& Bounds()                  const override { return _bounds; }
                /// <summary> Gets the number of points that are used to define the 3D geometric shape. </summary>
                virtual uint Count()                            const override { return Vertices.Count(); }
                /// <summary> Gets a structure containing all of the data needed to render the 3D geometric shape. </summary>
                OpenGLAPI virtual GeometryData Data()           const override;
                /// <summary> Gets an array of indices that specify the order in which geometric points are rendered. </summary>
                OpenGLAPI virtual Vector<uint> Indices()        const override;
                /// <summary> Gets an array of values that map each geometric point onto some other resource. </summary>
                OpenGLAPI virtual Vector<Vector3> Mapping()     const override;
                /// <summary> Gets an array of normal vectors associated with each point of the geometry. </summary>
                OpenGLAPI virtual Vector<Vector3> Normals()     const override;
                /// <summary> Gets an array of points that define the prototypical shape of some geometry in 3D space. </summary>
                OpenGLAPI virtual Vector<Vector3> Points()      const override;
                /// <summary> Gets the type of primitive that the points in the vertex array construct. </summary>
                virtual VertexTopologies Topology()             const override { return _topology; }

                virtual WindingOrders Winding()                 const { return _winding; }

                /// <summary> Sets the bounding volume of the entity in 3D space. </summary>
                OpenGLAPI virtual Geometry3D& Bounds(const Volume& value);
                /// <summary> Summarily sets all of the data needed to render the 3D geometric shape. </summary>
                OpenGLAPI virtual Geometry3D& Data(const GeometryData& value);
                /// <summary> Sets the array of indices that specify the order in which geometric points are rendered. </summary>
                OpenGLAPI virtual Geometry3D& Indices(const Vector<uint>& value);
                /// <summary> Sets the type of primitive that the points of the geometry construct. </summary>
                OpenGLAPI virtual Geometry3D& Topology(VertexTopologies value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new empty 3D geometric object. </summary>
                Geometry3D() { }
                /// <summary> Constructs a new 3D geometric object that is initialized with externally defined data. </summary>
                Geometry3D(const GeometryData& data)
                {
                    Data(data);
                }



                /** STATIC CONSTRUCTORS **/
                /// <summary> Constructs a cube with unit dimensions spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
                /// <param name="isIndexed"> Indicates whether the vertices of the cube should be indexed or shared. </param>
                /// <remarks> The vertices of this cube are wound counter-clockwise and are shared only if indexed. </remarks>
                OpenGLAPI static Geometry3D Cube(bool isIndexed = false);
                /// <summary> A cylinder with unit radius and height centered on the origin (0, 0, 0). </summary>
                /// <returns> An array of standard vertices that define a cylinder in 3D space. </returns>
                /// <param name="nfaces">
                ///     The desired number of quad faces that make up the cylinder.
                ///     <para> </para>
                ///     This number cannot be less than 3, as the cylinder would then be degenerate.
                /// </param>
                /// <remarks> The vertices of this cylinder are not shared and are wound counter-clockwise. </remarks>
                OpenGLAPI static Geometry3D Cylinder(uint nfaces, bool isIndexed = false);
                /// <summary> A regular icosahedron with a unit radius centered on the origin (0, 0, 0). </summary>
                /// <returns> An array of standard vertices that define a regular icosahedron in 3D space. </returns>
                /// <remarks> The vertices of this icosahedron are not shared and are wound counter-clockwise. </remarks>
                OpenGLAPI static Geometry3D Icosahedron(bool isIndexed = false);
                /// <summary> Constructs a line with unit length spanning the coordinates (-0.5, 0, 0) to (0.5, 0, 0). </summary>
                OpenGLAPI static Geometry3D Line();
                /// <summary> Constructs a single point in three dimensional space at the coordinates (0, 0, 0). </summary>
                OpenGLAPI static Geometry3D Point();
                /// <summary> Constructs a unit quad in the XY plane spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
                /// <remarks> The vertices of this quad are wound counter-clockwise and are shared only if indexed. </remarks>
                /// <param name="isIndexed"> Indicates whether the vertices of the quad should be indexed or shared. </param>
                OpenGLAPI static Geometry3D Quad(bool isIndexed = false);
                /// <summary> A sphere with unit radius centered on the origin (0, 0, 0). </summary>
                /// <returns> An array of standard vertices that define a sphere in 3D space. </returns>
                /// <param name="n">
                ///     The number of times the vertices of a regular icosahedron are tessellated to approximate the sphere.
                /// </param>
                OpenGLAPI static Geometry3D Sphere(uint n);
                /// <summary> Constructs a right-triangle in the xy-plane whose hypotenuse spans the coordinates (1, 0, 0) to (0, 1, 0). </summary>
                /// <remarks> The vertices of this triangle are wound counter-clockwise. </remarks>
                OpenGLAPI static Geometry3D Triangle();



                /** UTILITIES **/
                /// <summary> Inserts a new vertex at the end of the list of data that defines the 3D geometric shape. </summary>
                /// <param name="vertex"></param>
                OpenGLAPI void Append(const Vertex& vertex);
                /// <summary> Inserts a collection of vertices at the end of the list of data that defines the 3D geometric shape. </summary>
                /// <param name="vertices"></param>
                OpenGLAPI void Append(const ICollection<Vertex>& vertices);
                /// <summary> Estimates the normal vectors for a list of non-indexed triangles in model space. </summary>
                OpenGLAPI void CalculateNormals();
                /// <summary> Removes all of the data used to define the 3D geometric shape. </summary>
                OpenGLAPI void Clear();
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

                virtual void Append(const Vector3& position, const Vector3& normal, const Vector3& mapping)
                {
                    Append(Vertex(position, normal, (Vector2)mapping));
                }

            protected:

                /// <summary> Sets the (x, y, z) position of the back-lower-left bounding box corner in 3D space. </summary>
                virtual Geometry3D& BoundaryPosition(const Vector3& value)
                {
                    return Bounds(Volume(value, Bounds().Size()));
                }
                /// <summary> Sets the (width, height, depth) size of the bounding volume in 3D space. </summary>
                virtual Geometry3D& BoundarySize(const Vector3& value)
                {
                    return Bounds(Volume(Bounds().Position(), value));
                }

            private:

                /** PROPERTY DATA **/
                Volume              _bounds;
                Vector<uint>        _indices;
                VertexTopologies    _topology;
                WindingOrders       _winding;

                Vector<Vertex>      Vertices;

        };
    }
}
