#include "Geometry/Rectangle2D.h"
#include "Geometry/Geometry2D.h"



namespace Cyclone
{
    namespace SVG
    {
        Rectangle2D& Rectangle2D::Offset(const Vector3& value)
        {
            BoundaryPosition(value);
            Coordinates(0) = value.X;
            Coordinates(1) = value.Y;
            PathNeedsUpdate(true);
            return *this;
        }


        Rectangle2D& Rectangle2D::CornerRadius(float value)
        {
            if (value == CornerRadius()) { return *this; }
            Coordinates(4) = value;
            PathNeedsUpdate(true);
            return *this;
        }
        Rectangle2D& Rectangle2D::Size(const Vector3& value)
        {
            BoundarySize(value);
            Coordinates(2) = value.X;
            Coordinates(3) = value.Y;
            PathNeedsUpdate(true);
            return *this;
        }


        Rectangle2D::Rectangle2D(float cornerRadius)
        {
            Path2D::Add(Geometry2D::RoundedRectangle());
            CornerRadius(cornerRadius);
        }
    }
}