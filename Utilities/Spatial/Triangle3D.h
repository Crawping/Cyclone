/* CHANGELOG
 * Written by Josh Grooms on 20170616
 */

#pragma once
#include "Collections/Array.h"
#include "Math/Vector3.h"
#include "Spatial/LineSegment.h"



namespace Cyclone
{
    namespace Utilities
    {
        template<typename T> struct Triangle3D
        {

            /** DATA **/
            Array<T, 3> A;
            Array<T, 3> B;
            Array<T, 3> C;



            /** PROPERTIES **/
            constexpr T Area()                                      const
            {
                Vector3 AB = Vector3(B(0) - A(0), B(1) - A(1), B(2) - A(2));
                Vector3 AC = Vector3(C(0) - A(0), C(1) - A(1), C(2) - A(2));
                return T(0.5 * AB.Cross(AC).Norm());
            }
            constexpr bool IsDegenerate()                           const 
            {
                return A == B || A == C || B == C;
            }



            /** UTILITIES **/
            constexpr bool Intersects(const LineSegment& other)     const { return false; }



            /** OPERATORS **/
            constexpr bool operator ==(const Triangle3D& other)     const
            {
                return A == other.A && B == other.B && C == other.C;
            }
            constexpr bool operator !=(const Triangle3D& other)     const { return !operator ==(other); }

        };

    }
}
