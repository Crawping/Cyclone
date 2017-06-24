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
        class Geometry3D:
            public virtual IGeometric
        {
            public:

                /** GEOMETRIC PROPERTIES **/
                /// <summary> A rectangular prism that defines the bounding volume of the entity in 3D space. </summary>
                const Volume& Bounds()                  const override { return _data.Bounds; }
                /// <summary> Gets the number of points that are used to define the 3D geometric shape. </summary>
                uint Count()                            const override { return IsIndexed() ? _indices.Count() : _vertices.Count(); }
                /// <summary> Gets a structure containing all of the data needed to render the 3D geometric shape. </summary>
                const GeometryData& Data()              const override { return _data; }

                uint IndexCount()                       const override { return _indices.Count(); }
                /// <summary> Gets an array of indices that specify the order in which geometric points are rendered. </summary>
                Vector<uint> Indices()                  const override { return _indices.ToVector(); }
                /// <summary> Gets whether the list of geometric points is indexed. </summary>
                bool IsIndexed()                        const { return !_indices.IsEmpty(); }
                /// <summary> Gets an array of values that map each geometric point onto some other resource. </summary>
                Vector<Vector3> Mapping()               const override { return _vertices.Gather(Field<Vector3, Vertex>(&Vertex::UVW)); }
                /// <summary> Gets an array of normal vectors associated with each point of the geometry. </summary>
                Vector<Vector3> Normals()               const override { return _vertices.Gather(Field<Vector3, Vertex>(&Vertex::Normal)); }

                uint PointCount()                       const override { return _vertices.Count(); }
                /// <summary> Gets an array of points that define the prototypical shape of some geometry in 3D space. </summary>
                Vector<Vector3> Points()                const override { return _vertices.Gather(Field<Vector3, Vertex>(&Vertex::Position)); }
                /// <summary> Gets the type of primitive that the points in the vertex array construct. </summary>
                PointTopologies Topology()              const override { return _data.Topology; }

                Vector<Vertex> Vertices()               const override { return _vertices.ToVector(); }

                virtual WindingOrders Winding()         const { return _winding; }


                OpenGLAPI virtual Geometry3D& Indices(const ICollection<uint>& value);
                OpenGLAPI virtual Geometry3D& Mapping(const ICollection<Vector3>& value);
                OpenGLAPI virtual Geometry3D& Normals(const ICollection<Vector3>& value);
                OpenGLAPI virtual Geometry3D& Points(const ICollection<Vector3>& value);

                /// <summary> Sets the bounding volume of the entity in 3D space. </summary>
                OpenGLAPI virtual Geometry3D& Bounds(const Volume& value);
                /// <summary> Summarily sets all of the data needed to render the 3D geometric shape. </summary>
                OpenGLAPI virtual Geometry3D& Data(const GeometryData& value);
                /// <summary> Sets the type of primitive that the points of the geometry construct. </summary>
                OpenGLAPI virtual Geometry3D& Topology(PointTopologies value);

                OpenGLAPI virtual Geometry3D& Vertices(const ICollection<Vertex>& value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new empty 3D geometric object. </summary>
                Geometry3D() { }
                /// <summary> Constructs a new 3D geometric object that is initialized with externally defined data. </summary>
                OpenGLAPI Geometry3D(const GeometryData& data);



                /** UTILITIES **/
                OpenGLAPI Geometry3D* CreateView() const;
                OpenGLAPI bool Intersects(const LineSegment3D& line) const;

            protected:

                OpenGLAPI virtual void Append(uint index);
                OpenGLAPI virtual void Append(const Vertex& vertex);
                OpenGLAPI virtual void Append(const ICollection<uint>& indices);
                OpenGLAPI virtual void Append(const ICollection<Vertex>& vertices);
                OpenGLAPI virtual void Append(const Vector3& position, const Vector3& normal, const Vector3& mapping);

            private:

                /** PROPERTY DATA **/
                GeometryData        _data;
                ArrayList<uint>     _indices;
                ArrayList<Vertex>   _vertices;
                WindingOrders       _winding;

        };
    }
}
