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

        /** GENERAL UTILITIES **/
        /// <summary> Generates an unsigned 32-bit integer hash code for a given string. </summary>
        UtilitiesAPI uint hash(const string& string);
        /// <summary> Converts 2D matrix subscripts into an equivalent 1D linear index for column-major arrays. </summary>
        UtilitiesAPI int sub2ind(int nrows, int ncols, int a, int b);



        /** TEMPLATED UTILITIES **/
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
