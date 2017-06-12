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
                //using Path2D::Offset;
                //using Path2D::Size;

                /// <summary> Gets the radius of the curvature applied to the rectangle's corners in pixels. </summary>
                float CornerRadius()            const { return _geometry(0).Coordinates.Last(); }

                /// <summary> Sets the radius of curvature applied to the rectangle's corners in pixels. </summary>
                SVGAPI Rectangle2D& CornerRadius(float value);
                //SVGAPI Rectangle2D& Offset(const Vector3& value)    override;
                //SVGAPI Rectangle2D& Size(const Vector3& value)      override;



                /** CONSTRUCTOR **/
                SVGAPI Rectangle2D();



                /** UTILITIES **/
                SVGAPI void Update() const override;

            protected:

                /** UTILITIES **/
                SVGAPI void UpdateGeometry() const override;

            private:

                mutable bool    NeedsUpdate;

        };
    }
}