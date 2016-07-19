/* CHANGELOG 
 * Written by Josh Grooms on 20160708
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A list of commonly used constant numeric values. </summary>
        namespace Constants
        {
            /// <summary> The double-precision mathematical constant e. </summary>
            /// <remarks> The constant e is also sometimes referred to as Euler's number. </remarks>
            const double E          = 2.71828182845904523536;
            /// <summary> The double-precision mathematical constant pi. </summary>
            /// <remarks> When considered as an angle in radians, pi is equivalent to 180 degrees. </remarks>
            const double Pi         = 3.14159265358979323846;


            /// <summary> The double-precision mathematical constant pi / 2.0. </summary>
            /// <remarks> When considered as an angle in radians, pi/2 is equivalent to 90 degrees. </remarks>
            const double HalfPi     = Pi / 2.0;
            /// <summary> The double-precision mathematical constant pi / 4.0. </summary>
            /// <remarks> When considered as an angle in radians, pi/4 is equivalent to 45 degrees. </remarks>
            const double QuarterPi  = Pi / 4.0;
            /// <summary> The double-precision mathematical constant pi / 3.0. </summary>
            /// <remarks> When considered as an angle in radians, pi/3 is equivalent to 60 degrees. </remarks>
            const double ThirdPi    = Pi / 3.0;
            /// <summary> The double-precision mathematical constant pi * 2.0. </summary>
            /// <remarks> When considered as an angle in radians, 2*pi is equivalent to 360 degrees. </remarks>
            const double TwoPi      = 2 * Pi;
        }
    }
}