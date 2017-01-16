/* CHANGELOG
 * Written by Josh Grooms on 20161008
 */

#pragma once
#include "Geometry/Geometry2D.h"
#include "Geometry/Path2D.h"


namespace Cyclone
{
    namespace SVG
    {
        class Circle2D : public Path2D
        {
            public:

                /** PROPERTIES **/
                SVGAPI Circle2D& Offset(const Vector2& value);
                SVGAPI Circle2D& Size(const Vector2& value);


                SVGAPI Circle2D();

        };
    }
}
