/* CHANGELOG
 * Written by Josh Grooms on 20160921
 */

#pragma once
#include "Geometry/Path2D.h"



namespace Cyclone
{
    namespace SVG
    {
        class Rectangle2D : public Path2D
        {
            public:
                            
                float CornerRadius() const { return _cornerRadius; }

                SVGAPI Rectangle2D& CornerRadius(float value);

                SVGAPI Rectangle2D(float cornerRadius = 0.25f);

            private:

                float _cornerRadius;
                

        };
    }
}