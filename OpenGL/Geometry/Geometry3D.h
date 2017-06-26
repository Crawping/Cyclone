/* CHANGELOG
 * Written by Josh Grooms on 20161031
 */

#pragma once
#include "Collections/ArrayList.h"
#include "GL/OpenGLAPI.h"
#include "Geometry/Vertex.h"
#include "Interfaces/IGeometric.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A class that holds and manages data related to 3D geometric shapes. </summary>
        class Geometry3D: public virtual IGeometric
        {
            public:

                /** GEOMETRIC PROPERTIES **/
                /// <summary> A rectangular prism that defines the bounding volume of the entity in 3D space. </summary>
                const Volume& Bounds()                  const override { Update(); return _bounds; }
                /// <summary> Gets the total number of points that are used to define the 3D geometric shape. </summary>
                /// <returns> The number of indices, if the geometry is indexed, or the number of points otherwise. </returns>
                uint Count()                            const override { return IsIndexed() ? IndexCount() : PointCount(); }
                /// <summary> Gets the number of indices used to specify vertex ordering. </summary>
                uint IndexCount()                       const override { return _indices.Count(); }
                /// <summary> Gets an array of indices that specify the order in which geometric points are rendered. </summary>
                Vector<uint> Indices()                  const override { return _indices.ToVector(); }
                /// <summary> Gets whether the list of geometric points is indexed. </summary>
                bool IsIndexed()                        const { return !_indices.IsEmpty(); }
                /// <summary> Gets an array of values that map each geometric point onto some other resource. </summary>
                Vector<Vector3> Mapping()               const override { return _vertices.Gather(Field<Vector3, Vertex>(&Vertex::UVW)); }
                /// <summary> Gets an array of normal vectors associated with each point of the geometry. </summary>
                Vector<Vector3> Normals()               const override { return _vertices.Gather(Field<Vector3, Vertex>(&Vertex::Normal)); }
                /// <summary> Gets the number of stored vertices. </summary>
                uint PointCount()                       const override { return _vertices.Count(); }
                /// <summary> Gets an array of points that define the prototypical shape of some geometry in 3D space. </summary>
                Vector<Vector3> Points()                const override { return _vertices.Gather(Field<Vector3, Vertex>(&Vertex::Position)); }
                /// <summary> Gets the type of primitive that the points in the vertex array construct. </summary>
                PointTopologies Topology()              const override { return _topology; }
                /// <summary> Gets the array of vertices that define the geometric shape in 3D space. </summary>
                Vector<Vertex> Vertices()               const override { return _vertices.ToVector(); }
                /// <summary> Gets the winding order of the stored vertex data.</summary>
                virtual WindingOrders Winding()         const { return _winding; }

                /// <summary> Sets the array of indices that specify the order in which geometric points are rendered. </summary>
                OpenGLAPI virtual Geometry3D& Indices(const ICollection<uint>& value);
                /// <summary> Sets the array of values that map each geometric point onto some other resource. </summary>
                OpenGLAPI virtual Geometry3D& Mapping(const ICollection<Vector3>& value);
                /// <summary> Sets the normal vector associated with each stored vertex. </summary>
                OpenGLAPI virtual Geometry3D& Normals(const ICollection<Vector3>& value);
                /// <summary> Sets the 3D spatial coordinates associated with each stored vertex. </summary>
                OpenGLAPI virtual Geometry3D& Points(const ICollection<Vector3>& value);
                /// <summary> Sets the type of primitive that the points of the geometry construct. </summary>
                OpenGLAPI virtual Geometry3D& Topology(PointTopologies value);
                /// <summary> Sets the array of vertices that define the geometric shape in 3D space. </summary>
                OpenGLAPI virtual Geometry3D& Vertices(const ICollection<Vertex>& value);
                /// <summary> Sets the winding order of the stored vertex data. </summary>
                OpenGLAPI virtual Geometry3D& Winding(WindingOrders value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new empty 3D geometric object. </summary>
                OpenGLAPI Geometry3D();



                /** UTILITIES **/
                /// <summary> Determines whether the geometric shape is intersected by a particular line segment. </summary>
                /// <returns> A Boolean <c>true</c> if the line intersects the shape, or <c>false</c> otherwise. </returns>
                /// <param name="line"> The line segment to test for intersection with the geometry. </param>
                OpenGLAPI bool Intersects(const LineSegment3D& line) const;

            protected:

                /** PROPERTIES **/
                OpenGLAPI Geometry3D& Bounds(const Volume& value);



                /** UTILITIES **/
                /// <summary> Inserts a new vertex index at the end of the geometric data. </summary>
                /// <param name="index"> A linear array index that refers to a stored vertex. </param>
                OpenGLAPI virtual void Append(uint index);
                /// <summary> Inserts a new vertex at the end of the geometric data. </summary>
                /// <param name="vertex"> A vertex data structure to be copied and inserted. </param>
                OpenGLAPI virtual void Append(const Vertex& vertex);
                /// <summary> Inserts multiple vertex indices at the end of the geometric data. </summary>
                /// <param name="indices"> A generic collection of vertex indices to be copied and inserted. </param>
                OpenGLAPI virtual void Append(const ICollection<uint>& indices);
                /// <summary> Inserts multiple vertices at the end of the geometric data. </summary>
                /// <param name="vertices"> A generic collection of vertices to be copie and inserted. </param>
                OpenGLAPI virtual void Append(const ICollection<Vertex>& vertices);
                /// <summary> Inserts a new vertex at the end of the geometric data. </summary>
                /// <param name="position"> The (x, y, z) spatial coordinates of the new vertex. </param>
                /// <param name="normal"> The (x, y, z) vector that is perpendicular to the surface surrounding the vertex. </param>
                /// <param name="mapping"> The (u, v, w) resource coordinates associated with the vertex. </param>
                OpenGLAPI virtual void Append(const Vector3& position, const Vector3& normal, const Vector3& mapping);

                OpenGLAPI virtual void Update() const;

            private:

                /** PROPERTY DATA **/
                mutable Volume      _bounds;
                ArrayList<uint>     _indices;
                mutable bool        _needsUpdate;
                ArrayList<Vertex>   _vertices;
                WindingOrders       _winding;
                PointTopologies     _topology;

        };
    }
}
