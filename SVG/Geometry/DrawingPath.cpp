#include "NVPR.h"
#include "Geometry/Point2D.h"



namespace Cyclone
{
    namespace SVG
    {

        ///** CONSTRUCTOR & DESTRUCTOR **/
        //DrawingPath::DrawingPath() : 
        //    _pointColor(Color4::Black),
        //    _pointSize(2 * Path2D::StrokeWidth())
        //{
        //
        //}
        //DrawingPath::~DrawingPath()
        //{
        //    //for (uint a = 0; a < _components.Count(); a++)
        //    //    delete _components(a);
        //}



        ///** UTILITIES **/
        //DrawingPath& DrawingPath::Add(const ControlPoint2D& point)
        //{
        //    Path2D::Add(point);
        //    Vector2 ptCoords(point.Coordinates(0), point.Coordinates(1));
        //    Point2D* pt = new Point2D();

        //    pt->Offset(ptCoords)
        //        .Size(PointSize())

        //        .JoinStyle(JoinStyles::Round)
        //        .StrokeWidth(0)
        //        .PrimaryColor(_pointColor);

        //    //_components.Append(pt);
        //    return *this;
        //}

        //void DrawingPath::Clear()
        //{
        //    Path2D::Clear();
        //    //for (uint a = 0; a < _components.Count(); a++)
        //    //    delete _components(a);
        //    //_components.Clear();
        //}

        //DrawingPath& DrawingPath::Translate(const Vector3& t)
        //{
        //    //for (uint a = 0; a < _components.Count(); a++)
        //    //    _components(a)->Translate(t);

        //    Path2D::Translate(t);
        //    return *this;
        //}

    }
}