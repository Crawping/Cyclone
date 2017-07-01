#include "Collections/Array.h"
#include "Geometry/Geometry2D.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Vector<PathCommands> Geometry2D::Commands()     const
        {
            Vector<PathCommands> cmds = Vector<PathCommands>(ControlPoints.Count());
            for (uint a = 0; a < ControlPoints.Count(); a++)
                cmds(a) = ControlPoints(a).Command;
            return cmds;
        }
        const GeometryData& Geometry2D::Data()          const
        {
            GeometryData data =
            {
                _bounds,
                Vector<uint>(),
                Vector<Vector3>(Count()),
                Vector<Vector3>(Count()),
                Vector<Vector3>(Count()),
                _topology,
            };
            
            return data;
        }
        Vector<uint> Geometry2D::Indices()              const { return Vector<uint>(); }
        bool Geometry2D::IsClosed() const
        {
            return !IsEmpty() && ControlPoints.Last().Command == PathCommands::Close;
        }
        bool Geometry2D::IsEmpty()                      const { return ControlPoints.IsEmpty(); }
        Vector<Vector3> Geometry2D::Mapping()           const { return Vector<Vector3>(); }
        Vector<Vector3> Geometry2D::Normals()           const { return Vector<Vector3>(); }
        Vector<Vector3> Geometry2D::Points()            const { return Vector<Vector3>(); }
        Vector<float> Geometry2D::Parameters()          const
        {
            Vector<float> params;
            for (uint a = 0; a < ControlPoints.Count(); a++)
                params.Concatenate(ControlPoints(a).Coordinates);
            return params;
        }

        Geometry2D& Geometry2D::Bounds(const Volume& value)
        {
            _bounds = value;
            return *this;
        }
        Geometry2D& Geometry2D::Topology(PointTopologies value)
        {
            _topology = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        Geometry2D::Geometry2D()
        {
            Topology(PointTopologies::Path);
        }



        /** UTILITIES **/
        void Geometry2D::Append(const ControlPoint2D& point)                    { ControlPoints.Concatenate(point); }
        void Geometry2D::Append(const ICollection<ControlPoint2D>& points)      { ControlPoints.Concatenate(points); }
        //void Geometry2D::Insert(uint index, const ControlPoint2D& point)
        //{
        //    ControlPoints
        //}
        void Geometry2D::Set(uint index, const ControlPoint2D& point)
        {
            ControlPoints(index) = point;
        }
        void Geometry2D::Remove(uint index)
        {

        }
        void Geometry2D::Clear()
        {
            ControlPoints.Clear();
        }
        bool Geometry2D::Intersects(const LineSegment3D& line) const
        {
            return false;
        }



        /** GEOMETRY GENERATING FUNCTIONS **/
        Geometry2D Geometry2D::Circle()
        {
            Geometry2D geometry;
            geometry.ControlPoints =
            {
                { PathCommands::Move,   { 0.5f, 0.0f } },
                { PathCommands::Arc,    { 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.0f } },
                { PathCommands::Arc,    { 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  0.5f, 0.0f } },
                { PathCommands::Close,  { } },
            };

            return geometry;
        }
        Geometry2D Geometry2D::Line()
        {
            Geometry2D geometry;
            geometry.ControlPoints =
            {
                { PathCommands::Move,   { -0.5f, 0.0f } },
                { PathCommands::Line,   {  0.5f, 0.0f } },
                { PathCommands::Close,  { } },
            };

            return geometry;
        }
        Geometry2D Geometry2D::Rectangle()
        {
            Geometry2D geometry;
            geometry.ControlPoints =
            {
                { PathCommands::Rectangle,  { -0.5f, -0.5f, 1.0f, 1.0f } },
                { PathCommands::Close,      { } },
            };

            return geometry;
        }
        Geometry2D Geometry2D::RoundedRectangle(const Vector2& position, const Vector2& size, float cornerRadius)
        {
            Geometry2D geometry;
            geometry.Bounds(Volume(position, size));
            geometry.ControlPoints =
            {
                { PathCommands::RoundedRectangle, { position.X, position.Y, size.X, size.Y, cornerRadius } },
                { PathCommands::Close, { } },
            };

            return geometry;
        }
        Geometry2D Geometry2D::Star()
        {
            Geometry2D geometry;
            geometry.ControlPoints =
            {
                { PathCommands::Move,   {  40,  10 } },
                { PathCommands::Line,   { 100, 180 } },
                { PathCommands::Line,   { 160,  10 } },
                { PathCommands::Line,   {  10, 120 } },
                { PathCommands::Line,   { 190, 120 } },
                { PathCommands::Close,  { } },
            };

            return geometry;
        }
        Geometry2D Geometry2D::Triangle()
        {
            Geometry2D geometry;
            geometry.ControlPoints =
            {
                { PathCommands::Line,   { 0.0f, 1.0f } },
                { PathCommands::Line,   { 1.0f, 0.0f } },
                { PathCommands::Close,  { } },
            };

            return geometry;
        }

    }
}
