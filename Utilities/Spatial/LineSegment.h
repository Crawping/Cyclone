/* CHANGELOG
 * Written by Josh Grooms on 20170602
 */


#pragma once
#include "Interfaces/ISpatialTransform.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct LineSegment3D
        {

            /** DATA **/
            Vector3 A;
            Vector3 B;



            /** PROPERTIES **/
            /*constexpr*/ float Length()    const { return (B - A).Norm(); };
            /*constexpr*/ Vector3 Vector()  const { return (B - A).Normalize(); }



            /** UTILITIES **/
            constexpr Vector3 Intersection(const LineSegment3D& other) const
            {
                return Vector3();
            }
            constexpr bool Intersects(const LineSegment3D& other) const
            {
                return false;
            }
            constexpr bool IsParallel(const LineSegment3D& other) const
            {
                return false;
            }
            constexpr bool IsPerpendicular(const LineSegment3D& other) const
            {
                return false;
            }

            

            /** OPERATORS **/
            constexpr bool operator ==(const LineSegment3D& other) const { return (A == other.A) && (B == other.B); }

        };

        UtilitiesAPI LineSegment3D operator *(const ISpatialTransform& x, const LineSegment3D& y);

    }
}