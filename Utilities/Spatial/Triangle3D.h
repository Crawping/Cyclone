/* CHANGELOG
 * Written by Josh Grooms on 20170616
 */

#pragma once
#include "Collections/Array.h"



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
                return T(0.25) * (B - C) * (B + C)
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
