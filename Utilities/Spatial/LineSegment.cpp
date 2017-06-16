#include "Spatial/LineSegment.h"



namespace Cyclone
{
    namespace Utilities
    {
        LineSegment operator *(const ISpatialTransform& x, const LineSegment& y)
        {
            const auto& xform = x.ToMatrix4x4();
            return LineSegment
            {
                (Vector3)(xform * Vector4(y.A, 1.0f)),
                (Vector3)(xform * Vector4(y.B, 1.0f))
            };
        }
    }
}