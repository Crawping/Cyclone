#include "NVPR.h"
#include "Geometry/Point2D.h"
#include "Geometry/DrawingPath.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        List<const IRenderable&> DrawingPath::Components() const
        {
            List<const IRenderable&> components;
            for (auto& p : Points)
                components.Append(*p);

            return components;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        DrawingPath::DrawingPath() : 
            _pointColor(Color4::Black),
            _pointSize(2 * StrokeWidth()),
            _needsUpdate(false)
        {
        
        }
        DrawingPath::~DrawingPath()
        {
            for (Path2D* p : Points)
                delete p;
        }



        /** UTILITIES **/
        DrawingPath& DrawingPath::Append(const ControlPoint2D& point)
        {
            _geometry.Append(point);
            if (point.Coordinates.IsEmpty()) { return *this; }

            Vector2 ptCoords(point.Coordinates(0), point.Coordinates(1));
            Path2D* pt = new Path2D(Geometry2D::Point());

            pt->
                 Offset(ptCoords)
                .Size(PointSize())

                .JoinStyle(JoinStyles::Round)
                .StrokeWidth(0)
                .PrimaryColor(_pointColor)
                .Z(Z() + 0.01f);

            Points.Append(pt);
            _needsUpdate = true;
            return *this;
        }
        void DrawingPath::Clear()
        {
            _geometry.Clear();
            for (auto* p : Points) { delete p; }
            Points.Clear();
        }
        void DrawingPath::Update() const
        {
            for (auto* p : Points) { p->Update(); }
            if (_needsUpdate && !Path2D::NeedsUpdate())
                UpdateGeometry();

            Path2D::Update();
        }

    }
}