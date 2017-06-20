#include "Spatial/LineSegment.h"



namespace Cyclone
{
    namespace Utilities
    {
        LineSegment3D operator *(const ISpatialTransform& x, const LineSegment3D& y)
        {
            const auto& xform = x.ToMatrix4x4();
            return LineSegment3D
            {
                (Vector3)(xform * Vector4(y.A, 1.0f)),
                (Vector3)(xform * Vector4(y.B, 1.0f))
            };
        }
    }
}