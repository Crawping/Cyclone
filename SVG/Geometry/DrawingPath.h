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
                using Path2D::Translate;


                /** PROPERTIES **/
                SVGAPI List<const IRenderable&> Components()  const;
                bool NeedsUpdate()                      const override { return _needsUpdate || Path2D::NeedsUpdate(); }
                const Color4& PointColor()              const { return _pointColor; }
                const Vector2& PointSize()              const { return _pointSize; }

                DrawingPath& PointColor(const Color4& value) { _pointColor = value; return *this; }
                DrawingPath& PointSize(const Vector2& value) { _pointSize = value; return *this; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI DrawingPath();
                SVGAPI ~DrawingPath();



                /** UTILITIES **/
                SVGAPI void Append(const ControlPoint2D& point);
                SVGAPI void Clear();
                SVGAPI void Update() const override;

            private:

                /** PROPERTY DATA **/
                mutable bool        _needsUpdate;
                Vector2             _pointSize;
                Color4              _pointColor;

                List<Path2D*>       Points;

        };
    }
}
