#include "Utilities.h"
#include "Geometry/Geometry3D.h"
#include "Math/Constants.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        GeometryData Geometry3D::Data()             const
        {
            GeometryData data =
            {
                _bounds,
                _indices.ToVector(),
                _mapping.ToVector(),
                _normals.ToVector(),
                _points.ToVector(),
                _topology,
            };

            return data;
        }

        Geometry3D& Geometry3D::Bounds(const Volume& value)
        {
            _bounds = value;
            return *this;
        }
        Geometry3D& Geometry3D::Data(const GeometryData& value)
        {
            _bounds = value.Bounds;
            _indices = value.Indices;
            _mapping = value.Mapping;
            _normals = value.Normals;
            _points = value.Points;
            _topology = value.Topology;
            return *this;
        }
        
        Geometry3D& Geometry3D::Indices(const ICollection<uint>& value)
        {
            _indices.Clear();
            _indices.Append(value);
            return *this;
        }
        Geometry3D& Geometry3D::Mapping(const ICollection<Vector3>& value)
        {
            _mapping.Clear();
            _mapping.Append(value);
            return *this;
        }
        Geometry3D& Geometry3D::Normals(const ICollection<Vector3>& value)
        {
            _normals.Clear();
            _normals.Append(value);
            return *this;
        }
        Geometry3D& Geometry3D::Points(const ICollection<Vector3>& value)
        {
            _points.Clear();
            _points.Append(value);
            return *this;
        }
        Geometry3D& Geometry3D::Topology(PointTopologies value)
        {
            _topology = value;
            return *this;
        }



        /** PROTECTED UTILITIES **/
        void Geometry3D::Append(uint index)
        {
            Insert(_indices.Count(), index);
        }
        void Geometry3D::Append(const Vertex& vertex)
        {
            Append(vertex.Position, vertex.Normal, vertex.UV);
        }
        void Geometry3D::Append(const ICollection<uint>& indices)
        {
            for (uint a = 0; a < indices.Count(); a++)
                Append(indices(a));
        }
        void Geometry3D::Append(const ICollection<Vertex>& vertices)
        {
            for (uint a = 0; a < vertices.Count(); a++)
                Append(vertices(a));
        }
        void Geometry3D::Append(const Vector3& position, const Vector3& normal, const Vector3& mapping)
        {
            Insert(_points.Count(), position, normal, mapping);
        }
        void Geometry3D::Clear()
        {
            _indices.Clear();
            _mapping.Clear();
            _normals.Clear();
            _points.Clear();
        }


        void Geometry3D::Insert(uint index, uint pointIndex)
        {
            _indices.Insert(index, pointIndex);
        }
        void Geometry3D::Insert(uint index, const Vector3& position, const Vector3& normal, const Vector3& mapping)
        {
            _points.Insert(index, position);
            _normals.Insert(index, normal);
            _mapping.Insert(index, mapping);
        }
        void Geometry3D::Prepend(uint pointIndex)
        {
            Insert(0, pointIndex);
        }
        void Geometry3D::Prepend(const Vector3& position, const Vector3& normal, const Vector3& mapping)
        {
            Insert(0, position, normal, mapping);
        }
        void Geometry3D::Remove(uint index)
        {

        }

        void Geometry3D::Set(uint index, const Vector3& point, const Vector3& normal, const Vector3& mapping)
        {
            SetMapping(index, mapping);
            SetNormal(index, normal);
            SetPoint(index, point);
        }
        void Geometry3D::SetIndex(uint index, uint pointIndex)
        {
            _indices.Set(index, pointIndex);
        }
        void Geometry3D::SetNormal(uint index, const Vector3& normal)
        {
            _normals.Set(index, normal);
        }
        void Geometry3D::SetPoint(uint index, const Vector3& point)
        {
            _points.Set(index, point);
        }
        void Geometry3D::SetMapping(uint index, const Vector3& mapping)
        {
            _mapping.Set(index, mapping);
        }

    }
}
