/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "Collections/Vector.h"
#include "Geometry/ControlPoint2D.h"
#include "SVGAPI.h"




namespace Cyclone
{
    namespace SVG
    {
        namespace Geometry2D
        {

            //SVGAPI Vector<ControlPoint2D> Circle();

            SVGAPI Vector<ControlPoint2D> Line();

            SVGAPI Vector<ControlPoint2D> Point();

            SVGAPI Vector<ControlPoint2D> Rectangle();

            SVGAPI Vector<ControlPoint2D> RoundedRectangle();
            
            SVGAPI Vector<ControlPoint2D> Star();

            SVGAPI Vector<ControlPoint2D> Triangle();

        }
    }
}
