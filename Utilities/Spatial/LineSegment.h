/* CHANGELOG
 * Written by Josh Grooms on 20170602
 */


#pragma once
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct LineSegment
        {

            /** DATA **/
            Vector3 A;
            Vector3 B;



            /** PROPERTIES **/
            constexpr float Length()    const { return (B - A).Norm(); };
            constexpr Vector3 Vector()  const { return (B - A).Normalize(); }



            /** UTILITIES **/
            constexpr Vector3 Intersection(const LineSegment& other) const
            {
                if (!Intersects(other)) return Vector3(0);
            }
            constexpr bool Intersects(const LineSegment& other) const
            {
                return false;
            }
            constexpr bool IsParallel(const LineSegment& other) const
            {
                return false;
            }
            constexpr bool IsPerpendicular(const LineSegment& other) const
            {
                return false;
            }
            

            /** OPERATORS **/
            constexpr bool operator ==(const LineSegment& other) const { return (A == other.A) && (B == other.B); }


        };
    }
}