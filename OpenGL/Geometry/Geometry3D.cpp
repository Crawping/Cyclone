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
            _bounds = value;
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
            for (uint a = 0; a < Math::Max(Count(), value.Count()); a++)
                _vertices(a).UVW = value(a);
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
            _needsUpdate = true;
            return *this;
        }
        Geometry3D& Geometry3D::Topology(PointTopologies value)
        {
            _topology = value;
            return *this;
        }
        Geometry3D& Geometry3D::Vertices(const ICollection<Vertex>& value)
        {
            _vertices.Clear();
            _vertices.Append(value);
            _needsUpdate = true;
            return *this;
        }
        Geometry3D& Geometry3D::Winding(WindingOrders value)
        {
            _winding = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        Geometry3D::Geometry3D():
            _bounds(Volume::Empty),
            _needsUpdate(false)
        {

        }



        /** PUBLIC UTILITIES **/
        bool Geometry3D::Intersects(const LineSegment3D& line)      const
        {
            return false;
        }



        /** PROTECTED UTILITIES **/
        void Geometry3D::Append(uint index)
        {
            _indices.Append(index);
            _needsUpdate = true;
        }
        void Geometry3D::Append(const Vertex& vertex)
        {
            _vertices.Append(vertex);
            _needsUpdate = true;
        }
        void Geometry3D::Append(const ICollection<uint>& indices)
        {
            _indices.Append(indices);
            _needsUpdate = true;
        }
        void Geometry3D::Append(const ICollection<Vertex>& vertices)
        {
            _vertices.Append(vertices);
            _needsUpdate = true;
        }
        void Geometry3D::Append(const Vector3& position, const Vector3& normal, const Vector3& mapping)
        {
            return Append(Vertex(position, normal, mapping));
        }
        void Geometry3D::Update() const
        {
            if (!_needsUpdate) { return; }

            for (uint a = 0; a < PointCount(); a++)
                _bounds = _bounds.Union(_vertices(a).Position);

            _needsUpdate = false;
        }

    }
}
