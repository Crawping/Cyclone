/* CHANGELOG
 * Written by Josh Grooms on 20160921
 */

#pragma once
#include "EnumerationsSVG.h"
#include "SVGAPI.h"
#include "Collections/Vector.h"
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace SVG
    {
        using namespace Utilities;

        struct ControlPoint2D
        {
            PathCommands    Command;
            Vector<float>   Coordinates;
        };
    }
}