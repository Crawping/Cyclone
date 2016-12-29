/* CHANGELOG 
 * Written by Josh Grooms on 20161031
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/IGeometric.h"
#include "Spatial/Transform.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {

        struct GeometryData
        {
            Volume              Bounds;
            Vector<uint>        Indices;
            Vector<Vector3>     Mapping;
            Vector<Vector3>     Normals;
            Vector<Vector3>     Points;
            VertexTopologies    Topology;
        };



        /// <summary> A class that holds and manages data related to 3D geometric shapes. </summary>
        class Geometry3D : public virtual IGeometric
        {
            public:

                /** GEOMETRIC PROPERTIES **/
                /// <summary> A rectangular prism that defines the bounding volume of the entity in 3D space. </summary>
                virtual const Volume& Bounds()      const override { return _data.Bounds; }
                /// <summary> Gets an array of indices that specify the order in which geometric points are rendered. </summary>
                virtual Vector<uint> Indices()      const override { return _data.Indices; }
                /// <summary> Gets an array of values that map each geometric point onto some other resource. </summary>
                virtual Vector<Vector3> Mapping()   const override { return _data.Mapping; }
                /// <summary> Gets an array of normal vectors associated with each point of the geometry. </summary>
                virtual Vector<Vector3> Normals()   const override { return _data.Normals; }
                /// <summary> Gets an array of points that define the prototypical shape of some geometry in 3D space. </summary>
                virtual Vector<Vector3> Points()    const override { return _data.Points; }
                /// <summary> Gets the type of primitive that the points in the vertex array construct. </summary>
                virtual VertexTopologies Topology() const override { return _data.Topology; }

                /// <summary> Sets the array of indices that specify the order in which points of the geometric shape are to be rendered. </summary>
                virtual Geometry3D& Indices(const Vector<uint>& value)
                {
                    _data.Indices = value;
                    return *this;
                }
                /// <summary> Sets the array of values that map each point of the geometric shape onto some other external resource. </summary>
                virtual Geometry3D& Mapping(const Vector<Vector3>& value)
                {
                    _data.Mapping = value;
                    return *this;
                }
                /// <summary> Sets the array of normal vectors associated with each point of the geometry. </summary>
                virtual Geometry3D& Normals(const Vector<Vector3>& value)
                {
                    _data.Normals = value;
                    return *this;
                }
                /// <summary> Sets the array of points that define the prototypical shape of some geometry. </summary>
                virtual Geometry3D& Points(const Vector<Vector3>& value)
                {
                    _data.Points = value;
                    return *this;
                }
                /// <summary> Sets the type of primitive that the points of the geometry construct. </summary>
                virtual Geometry3D& Topology(VertexTopologies value)
                {
                    _data.Topology = value;
                    return *this;
                }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new empty 3D geometric object. </summary>
                Geometry3D() { }

                Geometry3D(const GeometryData& data) :
                    _data(data)
                {

                }
                /// <summary> Destroys any specially allocated resources held by the entity. </summary>
                virtual ~Geometry3D() { }



                /** STATIC CONSTRUCTORS **/
                /// <summary> A cube with unit dimensions spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
                /// <returns> An array of standard vertices that define a cube in 3D space. </returns>
                /// <remarks> The vertices of this cube are not shared and are wound counter-clockwise. </remarks>
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
                /// <summary> A line with unit length spanning the coordinates (-0.5, 0, 0) to (0.5, 0, 0). </summary>
                OpenGLAPI static Geometry3D Line();
                /// <summary> A single point in three dimensional space at the coordinates (0, 0, 0). </summary>
                OpenGLAPI static Geometry3D Point();
                /// <summary> A unit quad in the XY plane spanning the coordinates (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). </summary>
                /// <remarks> The vertices of this quad are not shared and are wound counter-clockwise. </remarks>
                OpenGLAPI static Geometry3D Quad(bool isIndexed = false);
                /// <summary> A sphere with unit radius centered on the origin (0, 0, 0). </summary>
                /// <returns> An array of standard vertices that define a sphere in 3D space. </returns>
                /// <param name="n"> 
                ///     The number of times the vertices of a regular icosahedron are tessellated to approximate the sphere.
                /// </param>
                OpenGLAPI static Geometry3D Sphere(uint n);
                /// <summary> A right-triangle in the XY plane whose hypotenuse spans the coordinates (1, 0, 0) to (0, 1, 0). </summary>
                /// <returns> An array of standard vertices that define a triangle in 3D space. </returns>
                /// <remarks> The vertices of this triangle are wound counter-clockwise. </remarks>
                OpenGLAPI static Geometry3D Triangle();



                /** UTILITIES **/
                /// <summary> Estimates the normal vectors for a list of non-indexed triangles in model space. </summary>
                OpenGLAPI void CalculateNormals();

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

                virtual void Add(const Vector3& position, const Vector3& normal = 0, const Vector3& mapping = 0)
                {
                    _data.Points.Append(position);
                    _data.Normals.Append(normal);
                    _data.Mapping.Append(mapping);
                }

            protected:
                
                /** PROPERTIES **/
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
                /// <summary> Sets the bounding volume of the entity in 3D space. </summary>
                virtual Geometry3D& Bounds(const Volume& value) 
                { 
                    _data.Bounds = value; 
                    return *this; 
                }

            private:

                /** PROPERTY DATA **/
                GeometryData        _data;

        };
    }
}
