#include "Utilities.h"
#include "Geometry/Geometry3D.h"
#include "Math/Constants.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        //const GeometryData& Geometry3D::Data()             const
        //{
        //    GeometryData data =
        //    {
        //        _bounds,
        //        _indices.ToVector(),
        //        _mapping.ToVector(),
        //        _normals.ToVector(),
        //        _points.ToVector(),
        //        _topology,
        //    };

        //    return data;
        //}

        Geometry3D& Geometry3D::Bounds(const Volume& value)
        {
            _data.Bounds = value;
            return *this;
        }
        Geometry3D& Geometry3D::Data(const GeometryData& value)
        {
            return 
                 Bounds(value.Bounds)
                .Indices(value.Indices)
                .Mapping(value.Mapping)
                .Normals(value.Normals)
                .Points(value.Points)
                .Topology(value.Topology)
        }
        
        Geometry3D& Geometry3D::Indices(const ICollection<uint>& value)
        {
            _data.Indices = Vector<uint>(value, 0, value.Count());
            return *this;
        }
        Geometry3D& Geometry3D::Mapping(const ICollection<Vector3>& value)
        {
            _data.Mapping = Vector<Vector3>(value, 0, value.Count());
            return *this;
        }
        Geometry3D& Geometry3D::Normals(const ICollection<Vector3>& value)
        {
            _data.Normals = Vector<Vector3>(value, 0, value.Count());
            return *this;
        }
        Geometry3D& Geometry3D::Points(const ICollection<Vector3>& value)
        {
            _data.Points = Vector<Vector3>(value, 0, value.Count());
            return *this;
        }
        Geometry3D& Geometry3D::Topology(PointTopologies value)
        {
            _data.Topology = value;
            return *this;
        }


        /** CONSTRUCTOR **/
        Geometry3D::Geometry3D(const GeometryData& data)
        {
            Data(data);
        }



        /** PUBLIC UTILITIES **/
        Geometry3D* Geometry3D::CreateView() const
        {
            return new Geometry3D(*this);
        }



        /** PROTECTED UTILITIES **/
        //void Geometry3D::Append(uint index)
        //{
        //    Insert(_data.Indices.Count(), index);
        //}
        //void Geometry3D::Append(const Vertex& vertex)
        //{
        //    Append(vertex.Position, vertex.Normal, vertex.UV);
        //}
        //void Geometry3D::Append(const ICollection<uint>& indices)
        //{
        //    for (uint a = 0; a < indices.Count(); a++)
        //        Append(indices(a));
        //}
        //void Geometry3D::Append(const ICollection<Vertex>& vertices)
        //{
        //    for (uint a = 0; a < vertices.Count(); a++)
        //        Append(vertices(a));
        //}
        //void Geometry3D::Append(const Vector3& position, const Vector3& normal, const Vector3& mapping)
        //{
        //    Insert(_data.Points.Count(), position, normal, mapping);
        //}
        //void Geometry3D::Clear()
        //{
        //    _data.Indices.Clear();
        //    _data.Mapping.Clear();
        //    _data.Normals.Clear();
        //    _data.Points.Clear();
        //}


        //void Geometry3D::Insert(uint index, uint pointIndex)
        //{
        //    _data.Indices.Insert(index, pointIndex);
        //}
        //void Geometry3D::Insert(uint index, const Vector3& position, const Vector3& normal, const Vector3& mapping)
        //{
        //    _points.Insert(index, position);
        //    _normals.Insert(index, normal);
        //    _mapping.Insert(index, mapping);
        //}
        //void Geometry3D::Prepend(uint pointIndex)
        //{
        //    Insert(0, pointIndex);
        //}
        //void Geometry3D::Prepend(const Vector3& position, const Vector3& normal, const Vector3& mapping)
        //{
        //    Insert(0, position, normal, mapping);
        //}
        //void Geometry3D::Remove(uint index)
        //{

        //}

        //void Geometry3D::Set(uint index, const Vector3& point, const Vector3& normal, const Vector3& mapping)
        //{
        //    SetMapping(index, mapping);
        //    SetNormal(index, normal);
        //    SetPoint(index, point);
        //}
        //void Geometry3D::SetIndex(uint index, uint pointIndex)
        //{
        //    _indices.Set(index, pointIndex);
        //}
        //void Geometry3D::SetNormal(uint index, const Vector3& normal)
        //{
        //    _normals.Set(index, normal);
        //}
        //void Geometry3D::SetPoint(uint index, const Vector3& point)
        //{
        //    _points.Set(index, point);
        //}
        //void Geometry3D::SetMapping(uint index, const Vector3& mapping)
        //{
        //    _mapping.Set(index, mapping);
        //}

    }
}
