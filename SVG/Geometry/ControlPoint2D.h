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

            bool operator ==(const ControlPoint2D& other) const
            {
                if ( (Command != other.Command) || (Coordinates.Count() != other.Coordinates.Count()) )
                    return false;
                
                for (uint a = 0; a < Coordinates.Count(); a++)
                    if (Coordinates(a) != other.Coordinates(a))
                        return false;

                return true;
            }
            bool operator !=(const ControlPoint2D& other) const { return !operator ==(other); }
        };
    }
}