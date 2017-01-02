#include "Geometry/Rectangle2D.h"
#include "Geometry/Geometry2D.h"



namespace Cyclone
{
    namespace SVG
    {
        Rectangle2D& Rectangle2D::Offset(const Vector3& value)
        {
            //BoundaryPosition(value);
            //ControlPoint2D rect = ControlPoints(0);
            //rect.Coordinates(0) = value.X;
            //rect.Coordinates(1) = value.Y;
            //ControlPoints.Set(0, rect);
            return *this;
        }


        Rectangle2D& Rectangle2D::CornerRadius(float value)
        {
            //ControlPoint2D rect = ControlPoints(0);
            //rect.Coordinates(4) = value;
            //ControlPoints.Set(0, rect);
            return *this;
        }
        Rectangle2D& Rectangle2D::Size(const Vector3& value)
        {
            //BoundarySize(value);
            //ControlPoint2D rect = ControlPoints(0);
            //rect.Coordinates(2) = value.X;
            //rect.Coordinates(3) = value.Y;
            //ControlPoints.Set(0, rect);
            return *this;
        }


        Rectangle2D::Rectangle2D(float cornerRadius) : 
            Path2D(Geometry2D::RoundedRectangle())
        {
            //Path2D::Add(Geometry2D::RoundedRectangle());
            //CornerRadius(cornerRadius);
        }
    }
}