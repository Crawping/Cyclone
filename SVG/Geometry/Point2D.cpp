#include "Geometry/Point2D.h"



namespace Cyclone
{
    namespace SVG
    {
        Point2D& Point2D::Offset(const Vector2& value)
        {
            ControlPoint2D move = ControlPoints(0);
            ControlPoint2D top = ControlPoints(1);
            ControlPoint2D bottom = ControlPoints(2);
            float radius = top.Coordinates(0);

            Vector2 newStart(value.X + radius, value.Y);

            move.Coordinates(0) = newStart.X;
            move.Coordinates(1) = newStart.Y;
            ControlPoints.Set(0, move);

            top.Coordinates(5) = newStart.X - (2.0f * radius);
            top.Coordinates(6) = newStart.Y;
            ControlPoints.Set(1, top);

            bottom.Coordinates(5) = newStart.X;
            bottom.Coordinates(6) = newStart.Y;
            ControlPoints.Set(2, bottom);

            Path2D::Offset(value);
            return *this;
        }
        Point2D& Point2D::Size(const Vector2& value)
        {
            ControlPoint2D move = ControlPoints(0);
            ControlPoint2D top = ControlPoints(1);
            ControlPoint2D bottom = ControlPoints(2);
            
            Vector2 center(move.Coordinates(0) - top.Coordinates(0), move.Coordinates(1));
            Vector2 newStart(center.X + value.X, center.Y);

            move.Coordinates(0) = newStart.X;
            ControlPoints.Set(0, move);

            top.Coordinates(0) = value.X;
            top.Coordinates(1) = value.X;
            top.Coordinates(5) = center.X - value.X;
            ControlPoints.Set(1, top);

            bottom.Coordinates(0) = value.X;
            bottom.Coordinates(1) = value.X;
            bottom.Coordinates(5) = newStart.X;
            ControlPoints.Set(2, bottom);

            Path2D::Size(value);
            return *this;
        }


        Point2D::Point2D()
        {
            Path2D::Add(Geometry2D::Point());
        }
    }
}
