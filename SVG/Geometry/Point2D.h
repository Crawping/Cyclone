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

                SVGAPI Point2D(const Vector3& point = Vector3::Zero) 
                { 
                    Position(point); 
                    Path2D::Add(Geometry2D::Point());
                }



                Point2D& Add(const ControlPoint2D& point)   override { return *this; }
                void Clear()                                override { }
                

        };
    }
}
