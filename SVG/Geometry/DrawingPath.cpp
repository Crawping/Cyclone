#include "NVPR.h"
#include "Geometry/DrawingPath.h"
#include "Geometry/Point2D.h"
//#include "Geometry/Rectangle2D.h"



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
            for (uint a = 0; a < _components.Count(); a++)
                delete _components(a);
        }



        /** UTILITIES **/
        DrawingPath& DrawingPath::Add(const ControlPoint2D& point)
        {
            Path2D::Add(point);
            Vector3 ptCoords(point.Coordinates(0), point.Coordinates(1), 0.0f);
            Point2D* pt = new Point2D();

            pt->JoinStyle(JoinStyles::Round)
                .StrokeWidth(0)
                .Color(_pointColor)
                .Position(ptCoords)
                .Scale(PointSize());

            _components.Append(pt);
            return *this;
        }

        void DrawingPath::Clear()
        {
            Path2D::Clear();
            for (uint a = 0; a < _components.Count(); a++)
                delete _components(a);
            _components.Clear();
        }

        DrawingPath& DrawingPath::Translate(const Vector3& t)
        {
            for (uint a = 0; a < _components.Count(); a++)
                _components(a)->Translate(t);

            Path2D::Translate(t);
            return *this;
        }

    }
}