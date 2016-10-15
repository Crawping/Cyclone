/* CHANGELOG
 * Written by Josh Grooms on 20161008
 */

#pragma once
#include "Geometry/Path2D.h"



namespace Cyclone
{
    namespace SVG
    {
        class Rectangle2D;

        class DrawingPath : public Path2D
        {
            public:

                /** PROPERTIES **/
                const Vector2& PointSize() const  { return _pointSize; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI DrawingPath();
                SVGAPI ~DrawingPath();



                /** UTILITIES **/
                SVGAPI DrawingPath& Add(const ControlPoint2D& point)            override;
                SVGAPI void Clear()                                             override;

                SVGAPI void Fill() const override;
                SVGAPI void Stroke() const override;
                SVGAPI void Update() const override;

            private:

                /** PROPERTY DATA **/
                Vector2             _pointSize;
                Color4              _pointColor;

                List<Rectangle2D*>  Points;

        };
    }
}
