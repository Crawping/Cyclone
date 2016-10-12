#include "Geometry/DrawingPath.h"
#include "Geometry/Rectangle2D.h"



namespace Cyclone
{
    namespace SVG
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        DrawingPath::DrawingPath() : 
            _pointColor(Color4::Black),
            _pointSize(2 * Path2D::StrokeWidth())
        {
        
        }
        DrawingPath::~DrawingPath()
        {
            for (uint a = 0; a < Points.Count(); a++)
                delete Points(a);
        }



        /** UTILITIES **/
        DrawingPath& DrawingPath::Add(const ControlPoint2D& point)
        {
            Path2D::Add(point);
            Vector3 ptCoords(point.Coordinates(0), point.Coordinates(1), 0.0f);
            Rectangle2D* pt = new Rectangle2D(PointSize().X / 4.0f);

            pt->JoinStyle(JoinStyles::Round)
                .StrokeColor(_pointColor)
                .StrokeWidth(StrokeWidth() * 1.5f)
                .Position(ptCoords);

            Points.Append(pt);
            return *this;
        }

        void DrawingPath::Clear()
        {
            Path2D::Clear();
            for (uint a = 0; a < Points.Count(); a++)
                delete Points(a);
        }

        void DrawingPath::Render() const
        {
            Path2D::Render();
            for (uint a = 0; a < Points.Count(); a++)
                Points(a)->Render();
        }

    }
}