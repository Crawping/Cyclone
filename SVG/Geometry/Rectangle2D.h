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
                            
                /** PROPERTIES **/
                float CornerRadius() const { return Coordinates(4); }

                SVGAPI Rectangle2D& CornerRadius(float value);

                SVGAPI Rectangle2D& Offset(const Vector3& value) override;

                SVGAPI Rectangle2D& Size(const Vector3& value) override;



                /** CONSTRUCTOR **/
                SVGAPI Rectangle2D(float cornerRadius = 0.0f);               

        };
    }
}