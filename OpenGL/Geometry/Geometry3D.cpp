#include "Utilities.h"
#include "Geometry/Geometry3D.h"
#include "Math/Constants.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
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
                .Topology(value.Topology);
        }
        Geometry3D& Geometry3D::Indices(const ICollection<uint>& value)
        {
            _indices.Clear();
            _indices.Append(value);
            return *this;
        }
        Geometry3D& Geometry3D::Mapping(const ICollection<Vector3>& value)
        {
            
            for (uint a = 0; a < Math::Max(Count(), value.Count()); a++)
                _vertices(a).UV = value(a);
            return *this;
        }
        Geometry3D& Geometry3D::Normals(const ICollection<Vector3>& value)
        {
            for (uint a = 0; a < Math::Max(Count(), value.Count()); a++)
                _vertices(a).Normal = value(a);
            return *this;
        }
        Geometry3D& Geometry3D::Points(const ICollection<Vector3>& value)
        {
            for (uint a = 0; a < Math::Max(Count(), value.Count()); a++)
                _vertices(a).Position = value(a);
            return *this;
        }
        Geometry3D& Geometry3D::Topology(PointTopologies value)
        {
            _data.Topology = value;
            return *this;
        }
        Geometry3D& Geometry3D::Vertices(const ICollection<Vertex>& value)
        {
            _vertices.Clear();
            _vertices.Append(value);
            return *this;
        }



        /** CONSTRUCTOR **/
        Geometry3D::Geometry3D(const GeometryData& data)
        {
            Data(data);
        }



        /** PUBLIC UTILITIES **/
        Geometry3D* Geometry3D::CreateView()                    const
        {
            return nullptr;
        }
        bool Geometry3D::Intersects(const LineSegment3D& line)    const
        {
            return false;
        }



        /** PROTECTED UTILITIES **/
        void Geometry3D::Append(uint index)
        {
            _indices.Append(index);
        }
        void Geometry3D::Append(const Vertex& vertex)
        {
            _vertices.Append(vertex);
        }
        void Geometry3D::Append(const ICollection<uint>& indices)
        {
            _indices.Append(indices);
        }
        void Geometry3D::Append(const ICollection<Vertex>& vertices)
        {
            _vertices.Append(vertices);
        }
        void Geometry3D::Append(const Vector3& position, const Vector3& normal, const Vector3& mapping)
        {
            _vertices.Append(Vertex(position, normal, mapping));
        }

    }
}
