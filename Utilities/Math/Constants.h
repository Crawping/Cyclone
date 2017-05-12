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
            /// <summary> The mathematical constant e. </summary>
            /// <typeparam name="T"> The desired numeric type of the constant. </typeparam>
            /// <remarks> The constant e is also sometimes referred to as Euler's number. </remarks>
            template<typename T> constexpr T E              = T(2.71828182845904523536);
            /// <summary> The mathematical constant pi. </summary>
            /// <typeparam name="T"> The desired numeric type of the constant. </typeparam>
            /// <remarks> When considered as an angle in radians, pi is equivalent to 180 degrees. </remarks>
            template<typename T> constexpr T Pi             = T(3.141592653589793238462643383);


            /// <summary> The mathematical constant pi / 2.0. </summary>
            /// <typeparam name="T"> The desired numeric type of the constant. </typeparam>
            /// <remarks> When considered as an angle in radians, pi/2 is equivalent to 90 degrees. </remarks>
            template<typename T> constexpr T HalfPi         = T(Pi<double> / 2.0);
            /// <summary> The mathematical constant pi / 4.0. </summary>
            /// <typeparam name="T"> The desired numeric type of the constant. </typeparam>
            /// <remarks> When considered as an angle in radians, pi/4 is equivalent to 45 degrees. </remarks>
            template<typename T> constexpr T QuarterPi      = T(Pi<double> / 4.0);
            /// <summary> The mathematical constant pi / 3.0. </summary>
            /// <typeparam name="T"> The desired numeric type of the constant. </typeparam>
            /// <remarks> When considered as an angle in radians, pi/3 is equivalent to 60 degrees. </remarks>
            template<typename T> constexpr T ThirdPi        = T(Pi<double> / 3.0);
            /// <summary> The mathematical constant pi * 2.0. </summary>
            /// <typeparam name="T"> The desired numeric type of the constant. </typeparam>
            /// <remarks> When considered as an angle in radians, 2*pi is equivalent to 360 degrees. </remarks>
            template<typename T> constexpr T TwoPi          = T(Pi<double> * 2.0);
        }
    }
}