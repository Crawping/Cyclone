#include "Geometry/Rectangle2D.h"



namespace Cyclone
{
    namespace SVG
    {

        Rectangle2D& Rectangle2D::CornerRadius(float value)
        {
            _cornerRadius = value;
            return *this;
        }

        Rectangle2D::Rectangle2D(float cornerRadius) : 
            _cornerRadius(cornerRadius)
        {
            Vector<ControlPoint2D> rect = 
            {
                { PathCommands::RoundedRectangle, { -0.5, -0.5, 1, 1, CornerRadius() } },
                { PathCommands::Close,            { } },
            };
            Path2D::Add(rect);
        }
    }
}