#include "Geometry/Point2D.h"



namespace Cyclone
{
    namespace SVG
    {
        Point2D& Point2D::Offset(const Vector2& value)
        {
            Coordinates(0) = value.X + Coordinates(2);
            Coordinates(1) = value.Y;

            Coordinates(7) = Coordinates(0) - (2.0f * Coordinates(2));
            Coordinates(8) = value.Y;

            Coordinates(14) = Coordinates(0);
            Coordinates(15) = value.Y;

            Path2D::Offset(value);

            PathNeedsUpdate(true);
            return *this;
        }
        Point2D& Point2D::Size(const Vector2& value)
        {
            Vector2 offset = Vector2(Coordinates(0) - Coordinates(2), Coordinates(1));

            Coordinates(0) = offset.X + value.X;

            Coordinates(2) = value.X;
            Coordinates(3) = value.Y;
            Coordinates(7) = offset.X - value.X;

            Coordinates(9) = value.X;
            Coordinates(10) = value.Y;
            Coordinates(14) = Coordinates(0);

            Path2D::Size(value);

            PathNeedsUpdate(true);
            return *this;
        }


        Point2D::Point2D()
        {
            Path2D::Add(Geometry2D::Point());
        }
    }
}
