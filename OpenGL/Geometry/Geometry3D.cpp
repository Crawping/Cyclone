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
                .Topology(value.Topology);
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
        Geometry3D* Geometry3D::CreateView()                    const
        {
            return nullptr;
        }
        bool Geometry3D::Intersects(const LineSegment& line)    const
        {
            return false;
        }

    }
}
