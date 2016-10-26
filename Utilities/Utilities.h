/* CHANGELOG
 * Written by Josh Grooms on 20150906
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



namespace Cyclone
{
    namespace Utilities
    {
		struct Vector3;

        /** ARRAY UTILITIES **/
        /// <summary> Converts 2D matrix subscripts into an equivalent 1D linear index for column-major arrays. </summary>
        UtilitiesAPI int sub2ind(int nrows, int ncols, int a, int b);
        /// <summary> Finds the next number greater than <see cref="x"/> that is also an integer power of two. </summary>
        UtilitiesAPI uint nextpow2(uint x);

        
        /** MATH UTILITIES **/
        namespace Math
        {
			UtilitiesAPI constexpr Vector3 Cross(const Vector3& x, const Vector3& y);

            /// <summary> Returns the maximum of two values. </summary>
            UtilitiesAPI constexpr float Max(float x, float y);
            /// <summary> Returns the maximum of three values. </summary>
            UtilitiesAPI constexpr float Max(float x, float y, float z);
            /// <summary> Returns the maximum of four values. </summary>
            UtilitiesAPI constexpr float Max(float x, float y, float z, float w);

            /// <summary> Returns the minimum of two values. </summary>
            UtilitiesAPI constexpr float Min(float x, float y);
            /// <summary> Returns the minimum of three values. </summary>
            UtilitiesAPI constexpr float Min(float x, float y, float z);
            /// <summary> Returns the minimum of four values. </summary>
            UtilitiesAPI constexpr float Min(float x, float y, float z, float w);

        }



        /** TEMPLATED UTILITIES **/
        /// <summary> Constrains numeric or comparable data to a range of values between some inputted minimum and maximum. </summary>
        /// <param name="x"> The data point to be constrained. </param>
        /// <param name="min"> The minimum value that <paramref name="x"/> is allowed to take. </param>
        /// <param name="max"> The maximum value that <paramref name="x"/> is allowed to take. </param>
        /// <returns> 
        ///     The same value of <paramref name="x"/> if it lies between <paramref name="min"/> and <paramref name="max"/>, 
        ///     inclusively. Otherwise, the closer of <paramref name="min"/> or <paramref name="max"/> is returned.
        /// </returns>
        template<typename T> constexpr T clamp(T x, T min, T max)
        {
            return (x < min) ? min :
                (x > max) ? max : x;
        }

        template<typename T> T wrap(T x, T min, T max)
        {
            float notUsed;
            T range = max - min;
            return
                (x < min) ?
                    max - (modf((min - x) / range, &notUsed) * range) :
                (x > max) ?
                    min + (modf((x - max) / range, &notUsed) * range) : x;
        }

        /// <summary> Converts any number into an equivalent string representation. </summary>
        template<typename T> string num2str(T number)
        {
            return std::to_string(number);
        }



        /** FILE UTILITIES **/
        /// <summary> Reads all text found within a file and returns it as a single string. </summary>
        UtilitiesAPI string readfile(const string& filename);
    }
}
