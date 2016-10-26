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
        class Point2D : public Path2D
        {
            public:

                /** PROPERTIES **/
                SVGAPI Vector2 Offset() const;
                SVGAPI Vector2 Size() const;


                SVGAPI Point2D& Offset(const Vector2& value);
                SVGAPI Point2D& Size(const Vector2& value);


                SVGAPI Point2D();

        };
    }
}
