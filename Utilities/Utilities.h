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
        /** ARRAY UTILITIES **/
        /// <summary> Converts 2D matrix subscripts into an equivalent 1D linear index for column-major arrays. </summary>
        UtilitiesAPI int sub2ind(int nrows, int ncols, int a, int b);



        /** MATH UTILITIES **/
        namespace Math
        {

            /// <summary> Returns the maximum of three values. </summary>
            UtilitiesAPI float Max(float x, float y, float z);
            /// <summary> Returns the maximum of four values. </summary>
            UtilitiesAPI float Max(float x, float y, float z, float w);
            /// <summary> Returns the minimum of three values. </summary>
            UtilitiesAPI float Min(float x, float y, float z);
            /// <summary> Returns the minimum of four values. </summary>
            UtilitiesAPI float Min(float x, float y, float z, float w);

        }

        /// <summary> Converts any number into an equivalent string representation. </summary>
        template<typename T> string num2str(T number)
        {
            return std::to_string(number);
        }

        /// <summary> Reads all text found within a file and returns it as a single string. </summary>
        UtilitiesAPI string readfile(const string& filename);
    }
}