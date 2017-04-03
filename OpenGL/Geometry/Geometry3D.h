/* CHANGELOG
 * Written by Josh Grooms on 20161031
 */

#pragma once
#include "Collections/List.h"
#include "Collections/ListVector.h"
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
                virtual uint Count()                            const override { return _indices.IsEmpty() ? _points.Count() : _indices.Count(); }
                /// <summary> Gets a structure containing all of the data needed to render the 3D geometric shape. </summary>
                OpenGLAPI virtual GeometryData Data()           const override;
                /// <summary> Gets an array of indices that specify the order in which geometric points are rendered. </summary>
                virtual Vector<uint> Indices()                  const override { return _indices.ToVector(); }
                /// <summary> Gets an array of values that map each geometric point onto some other resource. </summary>
                virtual Vector<Vector3> Mapping()               const override { return _mapping.ToVector(); }
                /// <summary> Gets an array of normal vectors associated with each point of the geometry. </summary>
                virtual Vector<Vector3> Normals()               const override { return _normals.ToVector(); }
                /// <summary> Gets an array of points that define the prototypical shape of some geometry in 3D space. </summary>
                virtual Vector<Vector3> Points()                const override { return _points.ToVector(); }
                /// <summary> Gets the type of primitive that the points in the vertex array construct. </summary>
                virtual PointTopologies Topology()              const override { return _topology; }

                virtual WindingOrders Winding()                 const { return _winding; }

                /// <summary> Sets the bounding volume of the entity in 3D space. </summary>
                OpenGLAPI virtual Geometry3D& Bounds(const Volume& value);
                /// <summary> Summarily sets all of the data needed to render the 3D geometric shape. </summary>
                OpenGLAPI virtual Geometry3D& Data(const GeometryData& value);
                /// <summary> Sets the type of primitive that the points of the geometry construct. </summary>
                OpenGLAPI virtual Geometry3D& Topology(PointTopologies value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new empty 3D geometric object. </summary>
                Geometry3D() { }
                /// <summary> Constructs a new 3D geometric object that is initialized with externally defined data. </summary>
                Geometry3D(const GeometryData& data)
                {
                    Data(data);
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



                /** UTILITIES **/
                OpenGLAPI virtual void Append(uint pointIndex);
                /// <summary> Inserts a new vertex at the end of the list of data that defines the 3D geometric shape. </summary>
                /// <param name="vertex"></param>
                OpenGLAPI virtual void Append(const Vertex& vertex);
                /// <summary> Inserts a collection of vertices at the end of the list of data that defines the 3D geometric shape. </summary>
                /// <param name="vertices"></param>
                OpenGLAPI virtual void Append(const ICollection<Vertex>& vertices);

                OpenGLAPI virtual void Append(const ICollection<uint>& indices);

                OpenGLAPI virtual void Append(const Vector3& position, const Vector3& normal, const Vector3& mapping);
                /// <summary> Removes all of the data used to define the 3D geometric shape. </summary>
                OpenGLAPI virtual void Clear();

                OpenGLAPI virtual void Insert(uint index, uint pointIndex);
                OpenGLAPI virtual void Insert(uint index, const Vector3& position, const Vector3& normal, const Vector3& mapping);

                OpenGLAPI virtual void Prepend(uint index);
                OpenGLAPI virtual void Prepend(const Vector3& position, const Vector3& normal, const Vector3& mapping);

                OpenGLAPI virtual void Remove(uint index);

                //OpenGLAPI virtual void Set(uint index, uint pointIndex);
                OpenGLAPI virtual void Set(uint index, const Vector3& point, const Vector3& normal, const Vector3& mapping);

                OpenGLAPI virtual void SetIndex(uint index, uint pointIndex);
                OpenGLAPI virtual void SetNormal(uint index, const Vector3& normal);
                OpenGLAPI virtual void SetPoint(uint index, const Vector3& point);
                OpenGLAPI virtual void SetMapping(uint index, const Vector3& mapping);


            private:

                /** PROPERTY DATA **/
                Volume              _bounds;
                ListVector<uint>    _indices;
                ListVector<Vector3> _mapping;
                ListVector<Vector3> _normals;
                ListVector<Vector3> _points;
                PointTopologies     _topology;
                WindingOrders       _winding;

        };
    }
}
